#pragma once

#include "ObservableDeviceInformationCollection.h"

namespace PeteBrown
{
    namespace Devices
    {
        namespace Midi
        {
            ref class MidiDeviceWatcher;
            
			// Web host hidden due to types used in the observable collection implementation
			[Windows::Foundation::Metadata::WebHostHidden]
			public delegate void MidiDeviceEnumerationEventHandler(MidiDeviceWatcher^ sender);

			// Web host hidden due to types used in the observable collection implementation
			[Windows::Foundation::Metadata::WebHostHidden]
			
			/// <summary>
            /// Class to assist in enumeration of MIDI devices, and handling hot plugging/unplugging.
            /// </summary>
			public ref class MidiDeviceWatcher sealed
            {
            private:

                // magic string to identify the wavetable synth
                const wchar_t* WAVETABLE_SYNTH_ID_STRING = L"MicrosoftGSWavetableSynth\0";

                ObservableDeviceInformationCollection^ _outputPortDescriptors;
				ObservableDeviceInformationCollection^ _inputPortDescriptors;

                Windows::Devices::Enumeration::DeviceWatcher^ _inputWatcher;
                Windows::Devices::Enumeration::DeviceWatcher^ _outputWatcher;

                void OnInputDeviceAdded(Windows::Devices::Enumeration::DeviceWatcher^ sender, Windows::Devices::Enumeration::DeviceInformation^ args);
                void OnInputDeviceRemoved(Windows::Devices::Enumeration::DeviceWatcher^ sender, Windows::Devices::Enumeration::DeviceInformationUpdate^ args);
                void OnInputDeviceUpdated(Windows::Devices::Enumeration::DeviceWatcher^ sender, Windows::Devices::Enumeration::DeviceInformationUpdate^ args);
                void OnInputDeviceEnumerationCompleted(Windows::Devices::Enumeration::DeviceWatcher^ sender, Platform::Object^ args);

                void OnOutputDeviceAdded(Windows::Devices::Enumeration::DeviceWatcher^ sender, Windows::Devices::Enumeration::DeviceInformation^ args);
                void OnOutputDeviceRemoved(Windows::Devices::Enumeration::DeviceWatcher^ sender, Windows::Devices::Enumeration::DeviceInformationUpdate^ args);
                void OnOutputDeviceUpdated(Windows::Devices::Enumeration::DeviceWatcher^ sender, Windows::Devices::Enumeration::DeviceInformationUpdate^ args);
                void OnOutputDeviceEnumerationCompleted(Windows::Devices::Enumeration::DeviceWatcher^ sender, Platform::Object^ args);

				bool _ignoreBuiltInWavetableSynth = true;


				// TEMP
				Windows::UI::Core::CoreDispatcher^ _dispatcher;

            public:
                MidiDeviceWatcher();

                /// <summary>
                /// Event fired when MIDI Output port enumeration has been completed. 
                /// </summary>
                event MidiDeviceEnumerationEventHandler^ OutputPortsEnumerated;

                /// <summary>
                /// Event fired when MIDI Input port enumeration has been completed. 
                /// </summary>
                event MidiDeviceEnumerationEventHandler^ InputPortsEnumerated;

                /// <summary>
                /// All enumerated MIDI Output port DeviceInformation objects. Uses this information to open the MIDI ports.
                /// ** NOTE: This collection type is likely to change to a more C#-friendly type. **
                /// </summary>
                property ObservableDeviceInformationCollection^ OutputPortDescriptors
                {
					ObservableDeviceInformationCollection^ get() { return _outputPortDescriptors; }
                }
	

                /// <summary>
                /// All enumerated MIDI Input port DeviceInformation objects. Uses this information to open the MIDI ports.
                /// 
                /// </summary>
                property ObservableDeviceInformationCollection^ InputPortDescriptors
                {
					ObservableDeviceInformationCollection^ get() { return _inputPortDescriptors; }
                }

                /// <summary>
                /// True if enumeration should ignore the built-in Wavetable synth. This synth requires an additional page for store apps.
                /// </summary>
                property bool IgnoreBuiltInWavetableSynth
                {
                    bool get();
                    void set(bool);
                }


                /// <summary>
                /// Begin enumerating MIDI Input ports. Fires off the InputPortsEnumerated event when complete. Does not open any ports.
                /// </summary>
                void EnumerateInputPorts();

                /// <summary>
                /// Begin enumerating MIDI Output ports. Fires off the InputPortsEnumerated event when complete. Does not open any ports.
                /// </summary>
                void EnumerateOutputPorts();

            };
        };
    };
};

