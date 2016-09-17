#include "pch.h"
#include "MidiNrpnParameterValueChangeMessage.h"


using namespace PeteBrown::Devices::Midi;


MidiNrpnParameterValueChangeMessage::MidiNrpnParameterValueChangeMessage()
{
	_rawData = ref new Windows::Storage::Streams::Buffer(TOTAL_BYTES_IN_MESSAGE);
	_rawData->Length = TOTAL_BYTES_IN_MESSAGE;

	_rawBytes = MidiMessageHelper::GetRawDataBytesFromBuffer(_rawData);

//	_type = Windows::Devices::Midi::MidiMessageType::None;
	_type = Windows::Devices::Midi::MidiMessageType::ControlChange;


	BuildBaseMessages();
}


//
//unsigned short MidiNrpnParameterValueChangeMessage::ParameterNumber::get()
//{
//
//}
//
//void MidiNrpnParameterValueChangeMessage::ParameterNumber::set(unsigned short value)
//{
//	// TODO: Set msb and lsb as well as backing store
//}
//
//
//
//unsigned short MidiNrpnParameterValueChangeMessage::Value::get()
//{
//
//}
//
//void MidiNrpnParameterValueChangeMessage::Value::set(unsigned short value)
//{
//	// TODO: Set msb and lsb as well as backing store
//}


