#pragma once


namespace PeteBrown
{
    namespace Devices
    {
        namespace Midi
        {

            /// <summary>
            /// Class for stand-alone MIDI clock generation. This is not for use in a larger sequencer, but rather for apps which need to send well-timed MIDI clock as an added function.
            /// </summary>
            public ref class MidiClockGenerator sealed
            {
            private:
                bool _isRunning;
                float _tempoBpm;

                LARGE_INTEGER _performanceCounterFrequency;			// ticks per second of the performance counter
                LONGLONG _tickInterval;
                double _tickTruncationError;						// diff between ideal interval and _tickInterval

                Windows::Foundation::Collections::IVector<Windows::Devices::Midi::IMidiOutPort^> ^_outputPorts;

                void ThreadWorker(Windows::Foundation::IAsyncAction^ operation);

                bool _sendMidiStartMessage = true;
                bool _sendMidiStopMessage = true;

                inline void BroadcastMessage(Windows::Devices::Midi::IMidiMessage^ message)
                {
                    for (auto&& port : _outputPorts)
                    {
                        port->SendMessage(message);
                    }
                }

            public:
                MidiClockGenerator();

                /// <summary>
                /// Start MIDI clock transmission. Optionally send a MIDI start message. Add output ports and set the tempo before calling this method.
                /// </summary>
                void Start();

                /// <summary>
                /// Stop the MIDI clock. Optionally send a MIDI stop message.
                /// </summary>
                void Stop();

                /// <summary>
                /// Set the tempo in Beats Per Minute. For example, 120.
                /// </summary>
                void SetTempo(float bpm);

                /// <summary>
                /// Collection of MidiOutPorts to send the clock to. Add valid ports to this collection before starting the clock.
                /// </summary>
                property Windows::Foundation::Collections::IVector<Windows::Devices::Midi::IMidiOutPort^>^ OutputPorts
                {
                    Windows::Foundation::Collections::IVector<Windows::Devices::Midi::IMidiOutPort^>^ get();
                }

                
                /// <summary>
                /// True if you want to automatically send a MIDI Start message when the clock is started. This is required for most sequencers and drum machines to start together.
                /// </summary>
                property bool SendMidiStartMessage
                {
                    bool get();
                    void set(bool);
                }

                /// <summary>
                /// True if you want to automatically send a MIDI stop message when the clock is stopped.
                /// </summary>
                property bool SendMidiStopMessage
                {
                    bool get();
                    void set(bool);
                }

            };
        };
    };
};
