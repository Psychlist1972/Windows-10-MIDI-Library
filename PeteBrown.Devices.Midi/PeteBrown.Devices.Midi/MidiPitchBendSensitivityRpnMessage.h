#pragma once


namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{
			public ref class MidiPitchBendSensitivityRpnMessage sealed
			{
			private:

				// MIDI message numbers for RPN
				static const byte RPN_PARAMETER_MSB = 101;
				static const byte RPN_PARAMETER_LSB = 100;
				static const byte RPN_VALUE_MSB = 6;
				static const byte RPN_VALUE_LSB = 38;
				static const byte RPN_PARAMETER_NUMBER_NULL = 127;		// value to be sent as parameter number after done


			public:
				MidiPitchBendSensitivityRpnMessage();

			};
		};
	};
};
