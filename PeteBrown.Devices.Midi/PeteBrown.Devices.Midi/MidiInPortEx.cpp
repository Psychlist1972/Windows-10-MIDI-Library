#include <ppltasks.h>

#include "pch.h"
#include "MidiInPortEx.h"

using namespace Windows::Foundation;
using namespace Windows::Devices::Midi;
using namespace PeteBrown::Devices::Midi;


IAsyncOperation<MidiInPortEx^>^ MidiInPortEx::FromIdAsync(Platform::String^ deviceId)
{
	auto t = concurrency::create_async([=]() -> MidiInPortEx^
	{
		auto portTask = concurrency::create_task(MidiInPort::FromIdAsync(deviceId));

		portTask.wait();

		return ref new MidiInPortEx(portTask.get());

	});

	return t;
}

Platform::String^ MidiInPortEx::GetDeviceSelector()
{
	return MidiInPort::GetDeviceSelector();
}

