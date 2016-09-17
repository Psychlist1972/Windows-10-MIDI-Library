# Windows-10-MIDI-Library
Library for C# and other apps to use Windows 10 Anniversary Edition native MIDI (USB, bluetooth, etc.)

Want to use a read-to-go version? The NuGet package, once I add in RPN/NRPN will be updated with everything in the library. Right now, it has some basics. I'll update here once the NuGet package is updated.
https://www.nuget.org/packages/PeteBrown.Devices.Midi/

# Requirements
- Visual Studio 2015 (or higher)
- Windows 10 Anniversary Edition SDK (or higher)

## Working and usable features
- Beat Clock generator for stand-alone beat clock usage (not for sequencers or similar apps)
- Device enumeration and watcher
- Bindable collection of Input and Output ports
- 
## Experimental or incomplete features
- RPN and NRPN message formatting
- MidiInPortEx for help with processing incoming logical (RPN, NRPN etc.) messages- 

## Investigating
- MPE. People who want this know what it is. :)

## Questions or concerns?
- Issues and discussion here on GitHub or, Twitter: @pete_brown
- Pull requests encouraged. :)


# Usage

To see how to use specific features, just look at the C# TestMidiApp. This is a basic UWP app which shows each of the major features in use. You can use it to enumerate MIDI ports, use the beat clock, test message send/receive, etc.

## MIDI Beat Clock

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

### Status
[x] Check clock timing with external device
[x] Send start / stop messages
[x] Send MIDI beat clock

## MIDI Device Watcher

A best practice when using MIDI devices (or any devices for that matter) is to allow hot plugging and unplugging. Rather than just enumerate all devices at start and restrict the user to those, you want the app to respond to the user adding or removing devices after start. 

UWP makes it easy with the DeviceWatcher class, but the results are not easily bindable in any XAML UI. Additionally, most apps do not want to enumerate the built-in MIDI synthesizer as one of the output ports, so I have included an option to filter that out from the results.

The best way to see this is to look in the MainViewModel in the TestMidiApp project. The UI consists of two lists (input and output) in the main XAML page.

### Status
[x] Observable collection updated on device add/remove
[x] Raise event when enumeration complete
[ ] Raise additional events on device add/remove

TODO: I need to surface the add/remove events through this class rather than just use the collection. This will enable an app to respond in non-UI ways as well.

## RPN and NRPN

(coming soon. Incomplete/experimental at the moment. The intent here is for you to be able to use RPN and NRPN aggregate messages in a way very similar to standard messages. This also requires an input processor, so you'll see a MidiInPortEx in addition to the message types.)

Example code for sending an NRPN message:
```c#
    var message = new MidiNrpnParameterValueChangeMessage();

    // parameter number and value are 14 bit values
    // and will be split into LSB and MSB across
    // two separate MIDI messages
    message.ParameterNumber = parameterNumber;
    message.ParameterValue = parameterValue;
    message.Channel = channel;

    outputPort.SendMessage(message);
```

### Status
[x] Send NRPN Value and Parameter Change message
[ ] Send NRPN Value Change message
[ ] Send NRPN Parameter Null message

[ ] Send RPN Value and Parameter Change message
[ ] Send RPN Value Change message
[ ] Send RPN Parameter Null message

[ ] Parse / aggregate NRPN messages on receive
[ ] Parse / aggregate RPN messages on receive

# Samples

These are samples, not production-ready applications.

## Main Sample App

This app shows how to use the majority of the features of the MIDI API. You can see input and output ports, send clock messages, etc. It uses a ViewModel-based approach for binding to the UI.

## Roland V-1HD Sample app

This app shows how to use the library to simply switch between screens on the Roland V-1HD switcher. Requires that the switcher have MIDI input Rx turned on, and currently assumes A/B mode and changes only the selection from the A bank. Very simple to modify to your own needs.

This app uses a flat approach (no ViewModel) for binding to the UI.

![Roland V-1HD](/doc/img/v1hd_front_main_gal.jpg)


# Notes about the ObservableDeviceEnumerationCollection

This is the moral equivalent to C# ObservableCollection&lt;DeviceInformation&gt;. That collection is not available in C# CX without taking a dependency on the .NET framework, which I didn't want to do. Additionally, Vector gets projected as just a plain old List, so that is not observable in C#.

If you're curious about what it takes to make something bindable and observable in C++, take a look. You can also see how to implement multiple interfaces while resolving naming conflicts. Much of the design of this class was shamelessly pulled from the collections.h implementation of Vector&lt;T&gt;

Binding in C# is enabled through the Windows::UI::Xaml::Interop::IBindableObservableVector interface.

```C++
    namespace WF =        ::Windows::Foundation;
    namespace WFC =       ::Windows::Foundation::Collections;
    namespace WUXI =      ::Windows::UI::Xaml::Interop;
    namespace WDE =       ::Windows::Devices::Enumeration;
    namespace Details =   ::Platform::Collections::Details;

    namespace PeteBrown
    {
	    namespace Devices
	    {
		    namespace Midi
		    {
			    [Windows::Foundation::Metadata::WebHostHidden]
			    public ref class ObservableDeviceInformationCollection sealed :
				    IObservableDeviceInformationCollection,
				    public WFC::IObservableVector<CollectionItemType^>,
				    WUXI::IBindableObservableVector
			    {
			        ...
			    };
			};
	    };
	};
```
There are likely ways to simplify the class or otherwise improve it. Happy to take pull requests. :)
