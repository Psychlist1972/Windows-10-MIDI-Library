#include "pch.h"
#include "MidiDeviceWatcher.h"

using namespace Windows::Devices::Enumeration;
using namespace Windows::Devices::Midi;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;


using namespace PeteBrown::Devices::Midi;


MidiDeviceWatcher::MidiDeviceWatcher()
{
	_inputPortDescriptors = ref new Platform::Collections::Vector<DeviceInformation^>();
	_outputPortDescriptors = ref new Platform::Collections::Vector<DeviceInformation^>();
}



// list of output ports
IObservableVector<DeviceInformation^>^ MidiDeviceWatcher::OutputPortDescriptors::get()
{
	return _outputPortDescriptors;
}

// list of input ports
IObservableVector<DeviceInformation^>^ MidiDeviceWatcher::InputPortDescriptors::get()
{
	return _inputPortDescriptors;
}



bool MidiDeviceWatcher::IgnoreBuiltInWavetableSynth::get()
{
	return _ignoreBuiltInWavetableSynth;
}

void MidiDeviceWatcher::IgnoreBuiltInWavetableSynth::set(bool value)
{
	_ignoreBuiltInWavetableSynth = value;
}






void MidiDeviceWatcher::EnumerateInputPorts()
{
	// create the watcher
	_inputWatcher = DeviceInformation::CreateWatcher(MidiInPort::GetDeviceSelector());

	// wire up event handler
	_inputWatcher->Added += ref new TypedEventHandler<DeviceWatcher ^, DeviceInformation ^>(this, &MidiDeviceWatcher::OnInputDeviceAdded);
	_inputWatcher->Removed += ref new TypedEventHandler<DeviceWatcher ^, DeviceInformationUpdate ^>(this, &MidiDeviceWatcher::OnInputDeviceRemoved);
	_inputWatcher->Updated += ref new TypedEventHandler<DeviceWatcher ^, DeviceInformationUpdate ^>(this, &MidiDeviceWatcher::OnInputDeviceUpdated);

	_inputWatcher->EnumerationCompleted += ref new Windows::Foundation::TypedEventHandler<DeviceWatcher ^, Platform::Object ^>(this, &MidiDeviceWatcher::OnInputDeviceEnumerationCompleted);

	// start enumeration
	_inputWatcher->Start();

}

void MidiDeviceWatcher::EnumerateOutputPorts()
{
	// create the watcher

	_outputWatcher = DeviceInformation::CreateWatcher(MidiOutPort::GetDeviceSelector());

	// wire up event handler
	_outputWatcher->Added += ref new TypedEventHandler<DeviceWatcher ^, DeviceInformation ^>(this, &MidiDeviceWatcher::OnOutputDeviceAdded);
	_outputWatcher->Removed += ref new TypedEventHandler<DeviceWatcher ^, DeviceInformationUpdate ^>(this, &MidiDeviceWatcher::OnOutputDeviceRemoved);
	_outputWatcher->Updated += ref new TypedEventHandler<DeviceWatcher ^, DeviceInformationUpdate ^>(this, &MidiDeviceWatcher::OnOutputDeviceUpdated);


	_outputWatcher->EnumerationCompleted += ref new Windows::Foundation::TypedEventHandler<DeviceWatcher ^, Platform::Object ^>(this, &MidiDeviceWatcher::OnOutputDeviceEnumerationCompleted);

	// start enumeration
	_outputWatcher->Start();
}



void MidiDeviceWatcher::OnInputDeviceAdded(DeviceWatcher^ sender, DeviceInformation^ args)
{
	_inputPortDescriptors->Append(args);
}

void MidiDeviceWatcher::OnInputDeviceRemoved(DeviceWatcher^ sender, DeviceInformationUpdate^ args)
{
	// TODO: is there a more efficient way to search a vector in C++?
	for (unsigned int i = 0; i < _inputPortDescriptors->Size; i++)
	{
		if (_inputPortDescriptors->GetAt(i)->Id == args->Id)
		{
			_inputPortDescriptors->RemoveAt(i);
			break;
		}
	}
}

void MidiDeviceWatcher::OnInputDeviceUpdated(DeviceWatcher^ sender, DeviceInformationUpdate^ args)
{
	// nothing to do here for now; MIDI devices don't really update at this point
}

void MidiDeviceWatcher::OnInputDeviceEnumerationCompleted(DeviceWatcher^ sender, Platform::Object^ args)
{
	// signal that enumeration has completed
	InputPortsEnumerated(this);
}



void MidiDeviceWatcher::OnOutputDeviceAdded(DeviceWatcher^ sender, DeviceInformation^ args)
{
	OutputDebugString(L" >>> output enumerated> ");
	OutputDebugString(args->Id->Data());
	OutputDebugString(L"\n");


	if (_ignoreBuiltInWavetableSynth)
	{
		std::wstring id(args->Id->Data());

		if (id.find(WAVETABLE_SYNTH_ID_STRING) != std::string::npos)
		{
			OutputDebugString(L" >>> output port was wavetable synth\n");
			return;
		}
	}

	// add to collection
	_outputPortDescriptors->Append(args);
	OutputDebugString(L" >>> output port added to vector\n");

}

void MidiDeviceWatcher::OnOutputDeviceRemoved(DeviceWatcher^ sender, DeviceInformationUpdate^ args)
{
	// TODO: is there a more efficient way to search a vector in C++?
	for (unsigned int i = 0; i < _outputPortDescriptors->Size; i++)
	{
		if (_outputPortDescriptors->GetAt(i)->Id == args->Id)
		{
			_outputPortDescriptors->RemoveAt(i);
			break;
		}
	}
}

void MidiDeviceWatcher::OnOutputDeviceUpdated(DeviceWatcher^ sender, DeviceInformationUpdate^ args)
{
	// nothing to do here for now; MIDI devices don't really update at this point
}

void MidiDeviceWatcher::OnOutputDeviceEnumerationCompleted(DeviceWatcher^ sender, Platform::Object^ args)
{
	// signal that enumeration has completed
	OutputPortsEnumerated(this);
}