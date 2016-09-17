#include "pch.h"
#include "MidiNrpnValueChangeMessage.h"



using namespace PeteBrown::Devices::Midi;


MidiNrpnValueChangeMessage::MidiNrpnValueChangeMessage()
{
	_rawData = ref new Windows::Storage::Streams::Buffer(TOTAL_BYTES_IN_MESSAGE);
	_rawData->Length = TOTAL_BYTES_IN_MESSAGE;

	_rawBytes = MidiMessageHelper::GetRawDataBytesFromBuffer(_rawData);

	_type = Windows::Devices::Midi::MidiMessageType::None;

	BuildBaseMessages();

}

