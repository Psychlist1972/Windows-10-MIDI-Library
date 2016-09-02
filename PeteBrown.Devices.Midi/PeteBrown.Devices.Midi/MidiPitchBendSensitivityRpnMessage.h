#pragma once

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{
			ref class MidiPitchBendSensitivityRpnMessage sealed :
				public Windows::Devices::Midi::IMidiMessage
			{
			public:
				MidiPitchBendSensitivityRpnMessage();

				// Inherited via IMidiMessage
				virtual property Windows::Storage::Streams::IBuffer ^ RawData;
				virtual property Windows::Foundation::TimeSpan Timestamp;
				virtual property Windows::Devices::Midi::MidiMessageType Type;
			};
		};
	};
};
