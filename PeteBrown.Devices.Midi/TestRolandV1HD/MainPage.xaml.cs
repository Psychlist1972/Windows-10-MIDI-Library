using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;


using PeteBrown.Devices.Midi;

using Windows.Devices.Enumeration;
using Windows.Devices.Midi;
using System.ComponentModel;
using System.Runtime.CompilerServices;


//
// NOTE
//
// For this to work with your Roland V-1HD, you must have MIDI receive set to on 
// on USB (if connected that way). It's off by default.
//
// Both of these are done through the on-screen menu displayed on the preview
// monitor when you hold the (TAP)BPM button down for more than two seconds.
// Navigate the menu using the up and down keys on the unit. Change values
// using the slide / throw.
//
// To sync to the MIDI clock on the PC, the MIDI Tempo RX must be set to On
// as well. This is in the same menu.
//


namespace TestRolandV1HD
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page,
        INotifyPropertyChanged
    {
        private MidiDeviceWatcher _watcher;
        private MidiClockGenerator _clock;

        private IMidiOutPort _port;

        public MainPage()
        {
            this.InitializeComponent();

            _watcher = new MidiDeviceWatcher();
            _clock = new MidiClockGenerator();

            Loaded += MainPage_Loaded;
        }

        private void MainPage_Loaded(object sender, RoutedEventArgs e)
        {
            _watcher.IgnoreBuiltInWavetableSynth = true;

            _watcher.EnumerateOutputPorts();
        }



        // for binding without bothering with a viewmodel or similar
        public ObservableDeviceInformationCollection OutputPortDescriptors
        {
            get { return _watcher.OutputPortDescriptors; }
        }

        public double ClockTempo
        {
            get { return _clock.Tempo; }
            set { _clock.Tempo = value; NotifyPropertyChanged(); }
        }






        private const byte BankSelectMsbControllerNumber = 0;
        private const byte BankSelectLsbControllerNumber = 32;



        private void Pad1_Click(object sender, RoutedEventArgs e)
        {
            if (ValidateMidiPort() && ValidateMidiChannel())
            {
                _port.SendMessage(new MidiControlChangeMessage(GetMidiChannel(), BankSelectMsbControllerNumber, 0));
                _port.SendMessage(new MidiControlChangeMessage(GetMidiChannel(), BankSelectLsbControllerNumber, 0));
                _port.SendMessage(new MidiProgramChangeMessage(GetMidiChannel(), 0));

                //_port.SendMessage(new MidiNoteOnMessage(GetMidiChannel(), 0x24, 0));
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("Invalid channel entry and/or MIDI output port not selected.");
            }
        }

        private void Pad2_Click(object sender, RoutedEventArgs e)
        {
            if (ValidateMidiPort() && ValidateMidiChannel())
            {
                _port.SendMessage(new MidiControlChangeMessage(GetMidiChannel(), BankSelectMsbControllerNumber, 0));
                _port.SendMessage(new MidiControlChangeMessage(GetMidiChannel(), BankSelectLsbControllerNumber, 0));
                _port.SendMessage(new MidiProgramChangeMessage(GetMidiChannel(), 1));

                //_port.SendMessage(new MidiNoteOnMessage(GetMidiChannel(), 0x26, 0));
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("Invalid channel entry and/or MIDI output port not selected.");
            }
        }

        private void Pad3_Click(object sender, RoutedEventArgs e)
        {
            if (ValidateMidiPort() && ValidateMidiChannel())
            {
                _port.SendMessage(new MidiControlChangeMessage(GetMidiChannel(), BankSelectMsbControllerNumber, 0));
                _port.SendMessage(new MidiControlChangeMessage(GetMidiChannel(), BankSelectLsbControllerNumber, 0));
                _port.SendMessage(new MidiProgramChangeMessage(GetMidiChannel(), 2));

                //_port.SendMessage(new MidiNoteOnMessage(GetMidiChannel(), 0x28, 0));
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("Invalid channel entry and/or MIDI output port not selected.");
            }
        }

        private void Pad4_Click(object sender, RoutedEventArgs e)
        {
            if (ValidateMidiPort() && ValidateMidiChannel())
            {
                _port.SendMessage(new MidiControlChangeMessage(GetMidiChannel(), BankSelectMsbControllerNumber, 0));
                _port.SendMessage(new MidiControlChangeMessage(GetMidiChannel(), BankSelectLsbControllerNumber, 0));
                _port.SendMessage(new MidiProgramChangeMessage(GetMidiChannel(), 3));

                //_port.SendMessage(new MidiNoteOnMessage(GetMidiChannel(), 0x29, 0));
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("Invalid channel entry and/or MIDI output port not selected.");
            }
        }


        private bool ValidateMidiPort()
        {
            return _port != null;
        }

        private bool ValidateMidiChannel()
        {
            byte channel;

            if (byte.TryParse(MidiChannel.Text.Trim(), out channel))
            {
                return (bool)(channel >= (byte)0 && channel < (byte)16);
            }

            return false;
        }

        private byte GetMidiChannel()
        {
            var channel = byte.Parse(MidiChannel.Text.Trim());

            System.Diagnostics.Debug.WriteLine("MIDI Channel: " + channel);

            return channel;
        }




        private async void MidiOutputList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var info = MidiOutputList.SelectedItem as DeviceInformation;

            if (info != null)
            {
                _port = await MidiOutPort.FromIdAsync(info.Id);

                System.Diagnostics.Debug.WriteLine("MIDI Port Selected: " + info.Name);
            }
        }





        private void Start_Click(object sender, RoutedEventArgs e)
        {
            if (ValidateMidiChannel())
            {
                _clock.OutputPorts.Clear();
                _clock.OutputPorts.Add(_port);

                _clock.Start();

                System.Diagnostics.Debug.WriteLine("Clock started");
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("Invalid channel entry for clock.");
            }
        }

        private void Stop_Click(object sender, RoutedEventArgs e)
        {
            _clock.Stop();

            System.Diagnostics.Debug.WriteLine("Clock stopped");
        }



        public event PropertyChangedEventHandler PropertyChanged;

        private void NotifyPropertyChanged([CallerMemberName] string propertyName="")
        {
           // System.Diagnostics.Debug.WriteLine("PropertyChanged: " + propertyName);

            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

    }
}
