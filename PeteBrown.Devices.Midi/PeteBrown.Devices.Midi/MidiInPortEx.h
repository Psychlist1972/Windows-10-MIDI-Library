#pragma once

#include <ppltasks.h>
#include <wrl.h>

using namespace Windows::Devices::Midi;

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{
			ref class MidiInPortEx;

			public ref class MidiNrpnMessageReceivedEventArgs sealed
			{
			public:
				property int foo;
			};

			public ref class MidiRpnMessageReceivedEventArgs sealed
			{
			public:
				property int foo;
			};

			public ref class MidiMpeMessageReceivedEventArgs sealed
			{
			public:
				property int foo;
			};


			public delegate void MidiNrpnMessageReceivedEventHandler(MidiInPortEx^ sender, MidiNrpnMessageReceivedEventArgs^ args);
			public delegate void MidiRpnMessageReceivedEventHandler(MidiInPortEx^ sender, MidiRpnMessageReceivedEventArgs^ args);
			public delegate void MidiMpeMessageReceivedEventHandler(MidiInPortEx^ sender, MidiMpeMessageReceivedEventArgs^ args);



			//[Windows::Foundation::Metadata::WebHostHidden]
			public ref class MidiInPortEx sealed 
			{
			private:
				MidiInPort^ _inPort;

			public:
				MidiInPortEx(MidiInPort^ inPort) { _inPort = inPort; }

				event MidiNrpnMessageReceivedEventHandler^ NrpnMessageReceived;
				event MidiRpnMessageReceivedEventHandler^ RpnMessageReceived;
				event MidiMpeMessageReceivedEventHandler^ MpeMessageReceived;


				static Platform::String^ GetDeviceSelector();

				Windows::Foundation::IAsyncOperation<MidiInPortEx^>^ FromIdAsync(Platform::String^ deviceId);



				/// <summary>
				/// True if you want input handling to inspect each message looking for MPE, and then cache/hold those messages until a complete MPE message
				/// can be built and event raised.
				/// </summary>
				property bool ProcessMpeMessages;

				/// <summary>
				/// True if you want input handling to inspect each message looking for NRPN, and then cache/hold those messages until a complete NRPN message
				/// can be built and event raised.
				/// </summary>
				property bool ProcessNrpnMessages;


				/// <summary>
				/// True if you want input handling to inspect each message looking for RPN, and then cache/hold those messages until a complete RPN message 
				/// can be built and event raised.
				/// </summary>
				property bool ProcessRpnMessages;

				/// <summary>
				/// A Note On message with a zero velocity is logically identical to a Note Off message. Set this to true if you want Note On 
				/// with zero velocity to be translated to a Note Off message. Makes client code slightly simpler.
				/// </summary>

				property bool TranslateZeroVelocityNoteOnMessageToNoteOff;


			};
		};
	};
};

