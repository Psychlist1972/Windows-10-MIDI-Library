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

void MidiMessageHelper::SendNrpnMessage(MidiOutPort^ outputPort, byte channelZeroBased, unsigned short parameterNumber, unsigned short parameterValue)
{
	// TODO

	// IBuffer
	// http://stackoverflow.com/questions/10520335/how-to-wrap-a-char-buffer-in-a-winrt-ibuffer-in-c
	// https://msdn.microsoft.com/en-us/library/windows/apps/windows.storage.streams.buffer.aspx?f=255&MSPPError=-2147217396

//	outputPort->SendBuffer();

}


void MidiMessageHelper::SendRpnMessage(MidiOutPort^ outputPort, byte channelZeroBased, unsigned short parameterNumber, unsigned short parameterValue)
{
	// TODO
}