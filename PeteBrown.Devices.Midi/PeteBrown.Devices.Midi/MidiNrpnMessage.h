#pragma once

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{

			ref class MidiNrpnMessage sealed :
				public Windows::Devices::Midi::IMidiMessage
			{
			public:
				MidiNrpnMessage();

				// Inherited via IMidiMessage
				virtual property Windows::Storage::Streams::IBuffer ^ RawData;
				virtual property Windows::Foundation::TimeSpan Timestamp;
				virtual property Windows::Devices::Midi::MidiMessageType Type;

				//property MidiMessageTypeEx ExtendedType ;

				property unsigned short ControllerNumber;
				property unsigned short Value;


			};
		};
	};
};