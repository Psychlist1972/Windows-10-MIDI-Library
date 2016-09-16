#include "pch.h"
#include "MidiMessageHelper.h"

using namespace Windows::Devices::Midi;
using namespace Windows::Storage::Streams;

using namespace PeteBrown::Devices::Midi;

MidiMessageHelper::MidiMessageHelper()
{
}


// References
// http://www.philrees.co.uk/nrpnq.htm
// http://sequence15.blogspot.com/2009/01/exploring-fizmo-nrpn-set.html
// http://www.yar2050.com/2012/02/msb-and-lsb-with-midi-nrpn.html


//void MidiMessageHelper::SendNrpnMessage(MidiOutPort^ outputPort, byte channel, unsigned short parameterNumber, unsigned short parameterValue, bool sendNullClosing)
//{
//	// Originally was going to use an IBuffer, but to do that required about as many UWP ref objects as 
//	// doing it with strongly-typed messages
//
//	// caching these messages (other than using IBuffer) doesn't work as they are immutable after construction
//	auto nrpnMessageParameterNumberMsb = ref new MidiControlChangeMessage(channel, NRPN_PARAMETER_MSB, msb(parameterNumber));
//	auto nrpnMessageParameterNumberLsb = ref new MidiControlChangeMessage(channel, NRPN_PARAMETER_LSB, lsb(parameterNumber));
//	auto nrpnMessageParameterValueMsb = ref new MidiControlChangeMessage(channel, NRPN_VALUE_MSB, msb(parameterValue));
//	auto nrpnMessageParameterValueLsb = ref new MidiControlChangeMessage(channel, NRPN_VALUE_LSB, lsb(parameterValue));
//	auto nrpnMessageParameterNull1 = ref new MidiControlChangeMessage(channel, NRPN_PARAMETER_MSB, NRPN_PARAMETER_NUMBER_NULL);
//	auto nrpnMessageParameterNull2 = ref new MidiControlChangeMessage(channel, NRPN_PARAMETER_LSB, NRPN_PARAMETER_NUMBER_NULL);
//
//	// send the messages out in the correct order
//	outputPort->SendMessage(nrpnMessageParameterNumberMsb);
//	outputPort->SendMessage(nrpnMessageParameterNumberLsb);
//	outputPort->SendMessage(nrpnMessageParameterValueMsb);
//	outputPort->SendMessage(nrpnMessageParameterValueLsb);
//
//	if (sendNullClosing)
//	{
//		// null out the parameter (don't leave it open)
//		outputPort->SendMessage(nrpnMessageParameterNull1);
//		outputPort->SendMessage(nrpnMessageParameterNull2);
//	}
//}
//
//
//void MidiMessageHelper::SendRpnMessage(MidiOutPort^ outputPort, byte channel, unsigned short parameterNumber, unsigned short parameterValue, bool sendNullClosing)
//{
//	// Originally was going to use an IBuffer, but to do that required about as many UWP ref objects as 
//	// doing it with strongly-typed messages
//
//
//	auto rpnMessageParameterNumberMsb = ref new MidiControlChangeMessage(channel, RPN_PARAMETER_MSB, msb(parameterNumber));
//	auto rpnMessageParameterNumberLsb = ref new MidiControlChangeMessage(channel, RPN_PARAMETER_LSB, lsb(parameterNumber));
//	auto rpnMessageParameterValueMsb = ref new MidiControlChangeMessage(channel, RPN_VALUE_MSB, msb(parameterValue));
//	auto rpnMessageParameterValueLsb = ref new MidiControlChangeMessage(channel, RPN_VALUE_LSB, lsb(parameterValue));
//	auto rpnMessageParameterNull1 = ref new MidiControlChangeMessage(channel, RPN_PARAMETER_MSB, RPN_PARAMETER_NUMBER_NULL);
//	auto rpnMessageParameterNull2 = ref new MidiControlChangeMessage(channel, RPN_PARAMETER_LSB, RPN_PARAMETER_NUMBER_NULL);
//
//	// send the messages out in the correct order
//	outputPort->SendMessage(rpnMessageParameterNumberMsb);
//	outputPort->SendMessage(rpnMessageParameterNumberLsb);
//	outputPort->SendMessage(rpnMessageParameterValueMsb);
//	outputPort->SendMessage(rpnMessageParameterValueLsb);
//
//	if (sendNullClosing)
//	{
//		// null out the parameter (don't leave it open)
//		outputPort->SendMessage(rpnMessageParameterNull1);
//		outputPort->SendMessage(rpnMessageParameterNull2);
//	}
//}