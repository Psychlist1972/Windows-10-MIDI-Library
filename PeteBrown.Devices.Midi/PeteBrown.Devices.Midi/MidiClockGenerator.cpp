#include "pch.h"
#include "MidiClockGenerator.h"

#include <Windows.h>
#include <tchar.h>
#include <collection.h>


using namespace PeteBrown::Devices::Midi;
using namespace Platform;
using namespace Platform::Collections;

using namespace Windows::Devices::Midi;
using namespace Windows::Foundation::Collections;
using namespace Windows::System::Threading;

//using namespace std;

// https://msdn.microsoft.com/en-us/library/windows/desktop/dd743612%28v=vs.85%29.aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/dn553408%28v=vs.85%29.aspx?


//
// TODO: 
// 
// Option to send start/stop messages from inside this code, to make it tighter
// 
// Option to have multiple MidiOutPort interfaces passed in in a collection
//

MidiClockGenerator::MidiClockGenerator()
{
	_isRunning = false;
	_outputPorts = ref new Vector<IMidiOutPort^>();

	QueryPerformanceFrequency(&_performanceCounterFrequency);

	OutputDebugString(_T(" MidiClock: Query Performance Frequency returned\n"));
}



bool MidiClockGenerator::SendMidiStartMessage::get()
{
	return _sendMidiStartMessage;
}

void MidiClockGenerator::SendMidiStartMessage::set(bool value)
{
	_sendMidiStartMessage = value;
}


bool MidiClockGenerator::SendMidiStopMessage::get()
{
	return _sendMidiStopMessage;
}

void MidiClockGenerator::SendMidiStopMessage::set(bool value)
{
	_sendMidiStopMessage = value;
}


Windows::Foundation::Collections::IVector<IMidiOutPort^>^ MidiClockGenerator::OutputPorts::get()
{
	return _outputPorts;
}


//
// Important examples
// At 120bpm, 24ppqn, we need 48 clock messages per second (120/60 * 24) : one every 20.83333 ms
// At 320bpm, 24ppqn, we need 128 clock messages per second (320/60 * 24) : one every 7.8125 ms.
// That helps give minimum resolutions for this loop.

void MidiClockGenerator::ThreadWorker(Windows::Foundation::IAsyncAction^ operation)
{
	LARGE_INTEGER lastTime;
	LONGLONG nextTime;
	LARGE_INTEGER currentTime;

	currentTime.QuadPart = 0;

	double errorAccumulator = 0.0;

	// Send the MIDI stop message to start the sequencer
	if (_sendMidiStartMessage)
		BroadcastMessage(ref new MidiStartMessage());


	//byte clockMessage = 0xF8;
	// We'll reuse this one clockMessage for every time we want to send out a pulse
	MidiTimingClockMessage^ clockMessage = ref new MidiTimingClockMessage();


	// Note that it also swallows most of a CPU logical core :)
	// this is a number you can play with to balance CPU usage and resolution

	while (_isRunning)
	{
		QueryPerformanceCounter(&lastTime);

		// send the message
		// ideally, this would include the timestamp and just be scheduled. We don't have that yet, though.
		BroadcastMessage(clockMessage);

		nextTime = lastTime.QuadPart + _tickInterval;

		if (errorAccumulator >= 1.0)
		{
			// get the whole number part of the error and then remove it from
			// the accumulator (which is a double)
			nextTime += (long)(std::trunc(errorAccumulator));
			errorAccumulator -= (long)(std::trunc(errorAccumulator));
		}

		// spin until this cycle is done
		// This is the one part I really dislike here.
		// sleeping the thread is no good due to durations required
		while (currentTime.QuadPart < nextTime)
			QueryPerformanceCounter(&currentTime);

		// accumulate some error :)
		errorAccumulator += _tickTruncationError;
	}

	// Send the MIDI stop message to stop the sequencer
	if (_sendMidiStopMessage)
		BroadcastMessage(ref new MidiStopMessage());

	OutputDebugString(_T(" MidiClock: Stopped Running (in background thread)\n"));
}


void MidiClockGenerator::Start()
{
	if (_outputPorts && _outputPorts->Size > 0)
	{
		_isRunning = true;

		ThreadPool::RunAsync(
			ref new WorkItemHandler(this, &MidiClockGenerator::ThreadWorker));

		OutputDebugString(_T(" MidiClock: Started.\n"));
	}
	else
	{
		OutputDebugString(_T(" MidiClock: No output ports specified.\n"));
	}
}

void MidiClockGenerator::Stop()
{
	_isRunning = false;

	OutputDebugString(_T(" MidiClock: Stop request received.\n"));
}

void MidiClockGenerator::SetTempo(float bpm)
{
	const int ppqn = 24;

	_tempoBpm = bpm;

	// this is going to have rounding errors
	// need to do this at a higher resolution or something
	// and account for drift over time
	_tickInterval = (LONGLONG)(std::trunc(((double)_performanceCounterFrequency.QuadPart / (bpm / 60.0F)) / ppqn));

	_tickTruncationError = (double)(((double)_performanceCounterFrequency.QuadPart / (bpm / 60.0F)) / ppqn) - _tickInterval;

	OutputDebugString(_T(" MidiClock: Tempo set.\n"));
}
