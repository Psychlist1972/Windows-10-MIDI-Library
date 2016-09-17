#include "pch.h"
#include "MidiNrpnParameterNullMessage.h"

using namespace Windows::Devices::Midi;
using namespace PeteBrown::Devices::Midi;


MidiNrpnParameterNullMessage::MidiNrpnParameterNullMessage()
{
	_rawData = ref new Windows::Storage::Streams::Buffer(TOTAL_BYTES_IN_MESSAGE);
	_rawData->Length = TOTAL_BYTES_IN_MESSAGE;

	_rawBytes = MidiMessageHelper::GetRawDataBytesFromBuffer(_rawData);

	_type = Windows::Devices::Midi::MidiMessageType::None;

	BuildBaseMessages();

}
