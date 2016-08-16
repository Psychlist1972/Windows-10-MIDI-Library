# Windows-10-MIDI-Library
Library for C# and other apps to use Windows 10 Anniversary Update native MIDI (USB, bluetooth, etc.)

Want to use a read-to-go version? The NuGet package is usually pretty up to date.
https://www.nuget.org/packages/PeteBrown.Devices.Midi/

Currently built using the Windows 10 Anniversary Update SDK. This is pre-release, and not yet ready for production use. However, you are free to use it as you want, take the code and target a down-level SDK, etc. The MIDI API itself was released with Windows 10 RTM, so targeting that release, or the 1511 release will work fine if you update the project files, or copy into a new project.

Features
- Beat Clock generator for stand-alone beat clock usage (not for sequencers or similar apps)
- Device enumeration and watcher
- RPN and NRPN message formatting helper
- C#-friendly observable collection (only partially implemented so far)

Updated NuGet package pending finished observable collection and testing.

Questions or concerns?
Issues and discussion here on GitHub or, Twitter: @pete_brown
Pull requests encouraged. :)

