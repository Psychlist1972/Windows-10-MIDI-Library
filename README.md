# Windows-10-MIDI-Library
Library for C# and other apps to use Windows 10 Anniversary Edition native MIDI (USB, bluetooth, etc.)

Want to use a read-to-go version? The NuGet package is usually pretty up to date.
https://www.nuget.org/packages/PeteBrown.Devices.Midi/

# Requirements
- Visual Studio 2015
- Windows 10 Anniversary Edition SDK

## Working and usable features
- Beat Clock generator for stand-alone beat clock usage (not for sequencers or similar apps)
- Device enumeration and watcher
- Bindable collection of Input and Output ports
- 
## Experimental or incomplete features
- RPN and NRPN message formatting
- MidiInPortEx for help with processing incoming logical (RPN, NRPN etc.) messages

## Questions or concerns?
- Issues and discussion here on GitHub or, Twitter: @pete_brown
- Pull requests encouraged. :)


# Usage

To see how to use specific features, just look at the C# TestMidiApp. This is a basic UWP app which shows each of the major features in use. You can use it to enumerate MIDI ports, use the beat clock, test message send/receive, etc.

# MIDI Beat Clock

The MIDI beat clock is an implementation of a tempo-driven and pretty accurate beat clock. In a sequencer type app, the loop could contain more logic than just a beat clock, so this is solely for the utility of sending a clock without any other clock-driven events. You can use this to drive external sequencers and other devices from your PC.

Optionally, the clock can send MIDI Start and Stop messages. These are the messages that sequencers and drum machines listen for to start or stop their playback.

```C#
    MidiClockGenerator clock = new MidiClockGenerator();

    // set tempo in BPM
    clock.Tempo = 120.0;

    // yes, we want to send start and stop messages
    clock.SendMidiStartMessage = true;
    clock.SendMidiStopMessage = true;    
    
    // start the clock
    clock.Start();

    // do some other stuff
    
    // stop the clock
    clock.Stop();
```

The clock runs in a tight loop, which will pretty much tie up an entire core on your PC or device. This is necessary to maintain tight timings. Feel free to look at the C++ code and adapt it to your own needs should you want to do more than just send out clock messages.

Note also that I do not recommend sending clock messages from C#. You'll find that garbage collections and the other things which make C# so great to use can cause jitter and drift in the clock. You may be able to get it to work reasonably well for some window of BPM, but in my experience, C++ is a better tool for this job.

