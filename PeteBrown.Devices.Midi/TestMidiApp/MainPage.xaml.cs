using PeteBrown.Devices.Midi;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Devices.Midi;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace TestMidiApp
{
    /// <summary>
    /// 
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private MidiClockGenerator _clock = new MidiClockGenerator();
        private MidiDeviceWatcher _watcher = new MidiDeviceWatcher();

        public MainPage()
        {
            this.InitializeComponent();

            Loaded += MainPage_Loaded;
        }

        private void MainPage_Loaded(object sender, RoutedEventArgs e)
        {
            _watcher.InputPortsEnumerated += _watcher_InputPortsEnumerated;
            _watcher.OutputPortsEnumerated += _watcher_OutputPortsEnumerated;

            // the built-in synth requires an add-on package for the solution, and isn't very good anyway
            _watcher.IgnoreBuiltInWavetableSynth = true;

            // make sure you have the event handlers wired up before this.
            _watcher.EnumerateInputPorts();
            _watcher.EnumerateOutputPorts();

            UpdateTempo();

        }

        private void UpdateTempo()
        {
            if (TempoText != null)
                TempoText.Text = Tempo.Value + " bpm";

            _clock.SetTempo((float)Tempo.Value);
        }


        // All output ports have been enumerated
        private async void _watcher_OutputPortsEnumerated(MidiDeviceWatcher sender)
        {
            // event fires on a different thread, so be sure to dispatch to interact with UI
            await Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, async () =>
            {
                foreach (var info in sender.OutputPortDescriptors)
                {
                    // This diagnostic info is how you can see the IDs of all the ports.
                    System.Diagnostics.Debug.WriteLine("- Output -----");
                    System.Diagnostics.Debug.WriteLine(info.Name);
                    System.Diagnostics.Debug.WriteLine(info.Id);
                    System.Diagnostics.Debug.WriteLine("--------------");

                    var port = (MidiOutPort)await MidiOutPort.FromIdAsync(info.Id);

                    // If you don't want the clock on all ports, here's where you'd change the code
                    if (port != null)
                        _clock.OutputPorts.Add(port);
                    else
                        System.Diagnostics.Debug.WriteLine("Failed to create port with id " + info.Id);
                }

                if (_clock.OutputPorts.Count > 0)
                {
                    System.Diagnostics.Debug.WriteLine("About to create clock.");

                    _clock.SetTempo((float)Tempo.Value);
                    _clock.SendMidiStartMessage = true; 
                    _clock.SendMidiStopMessage = true;

                    Start.IsEnabled = true;
                    Stop.IsEnabled = false;
                }
                else
                {
                    System.Diagnostics.Debug.WriteLine("No output ports to wire up.");

                    Start.IsEnabled = false;
                    Stop.IsEnabled = false;
                }
            });
        }


        // All input ports have been enumerated
        private void _watcher_InputPortsEnumerated(MidiDeviceWatcher sender)
        {
            foreach (var info in sender.InputPortDescriptors)
            {
                System.Diagnostics.Debug.WriteLine("- Input -----");
                System.Diagnostics.Debug.WriteLine(info.Name);
                System.Diagnostics.Debug.WriteLine(info.Id);
                System.Diagnostics.Debug.WriteLine("--------------");
            }
        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {
            Start.IsEnabled = false;
            Stop.IsEnabled = true;

            _clock.Start();
        }

        private void Stop_Click(object sender, RoutedEventArgs e)
        {
            Start.IsEnabled = true;
            Stop.IsEnabled = false;

            _clock.Stop();
        }

        private void Tempo_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            UpdateTempo();
        }

    }
}
