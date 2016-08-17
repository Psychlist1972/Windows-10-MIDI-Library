using PeteBrown.Devices.Midi;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.Midi;

namespace TestMidiApp.ViewModel
{
    public class MainViewModel : INotifyPropertyChanged
    {
        private MidiClockGenerator _clock = new MidiClockGenerator();
        private MidiDeviceWatcher _watcher = new MidiDeviceWatcher();

        public event PropertyChangedEventHandler PropertyChanged;

        public MainViewModel()
        {
            _watcher.InputPortsEnumerated += _watcher_InputPortsEnumerated;
            _watcher.OutputPortsEnumerated += _watcher_OutputPortsEnumerated;

#if DEBUG
            // these are for debugging only
            _watcher.OutputPortDescriptors.CollectionChanged += OutputPortDescriptors_CollectionChanged;
            _watcher.InputPortDescriptors.CollectionChanged += InputPortDescriptors_CollectionChanged;
            _watcher.OutputPortDescriptors.VectorChanged += OutputPortDescriptors_VectorChanged;
            _watcher.InputPortDescriptors.VectorChanged += InputPortDescriptors_VectorChanged;
#endif

            // the built-in synth requires an add-on package for the solution, and isn't very good anyway
            // this is not a required setting. However, if you don't ignore it, you need to add the DLS package
            // via project->add reference->universal windows->extensions
            _watcher.IgnoreBuiltInWavetableSynth = true;

            // make sure you have the event handlers wired up before this.
            _watcher.EnumerateInputPorts();
            _watcher.EnumerateOutputPorts();          

        }

#if DEBUG
        private void InputPortDescriptors_VectorChanged(Windows.Foundation.Collections.IObservableVector<DeviceInformation> sender, Windows.Foundation.Collections.IVectorChangedEventArgs @event)
        {
            System.Diagnostics.Debug.WriteLine("InputPortDescriptors - VectorChanged: " + @event.CollectionChange);
        }

        private void OutputPortDescriptors_VectorChanged(Windows.Foundation.Collections.IObservableVector<DeviceInformation> sender, Windows.Foundation.Collections.IVectorChangedEventArgs @event)
        {
            System.Diagnostics.Debug.WriteLine("OutputPortDescriptors - VectorChanged: " + @event.CollectionChange);
        }

        private void InputPortDescriptors_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            System.Diagnostics.Debug.WriteLine("InputPortDescriptors - CollectionChanged: " + e.Action);

            if (e.NewItems != null)
            {
                foreach (DeviceInformation item in e.NewItems)
                {
                    System.Diagnostics.Debug.WriteLine(" -- " + item.Name);
                }
            }

        }

        private void OutputPortDescriptors_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            System.Diagnostics.Debug.WriteLine("OutputPortDescriptors - CollectionChanged: " + e.Action);

            if (e.NewItems != null)
            {
                foreach (DeviceInformation item in e.NewItems)
                {
                    System.Diagnostics.Debug.WriteLine(" -- " + item.Name);
                }
            }
        }
#endif

        public ObservableDeviceInformationCollection InputPortDescriptors
        {
            get { return _watcher.InputPortDescriptors; }
        }

        public ObservableDeviceInformationCollection OutputPortDescriptors
        {
            get { return _watcher.OutputPortDescriptors; }
        }


        public void StartClock()
        {

        }

        public void StopClock()
        {

        }

        public double ClockTempo
        {
            get { return _clock.Tempo; }
            set
            {
                _clock.Tempo = value;
                NotifyPropertyChanged();
            }
        }

        // All output ports have been enumerated
        private async void _watcher_OutputPortsEnumerated(MidiDeviceWatcher sender)
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

                _clock.SendMidiStartMessage = true;
                _clock.SendMidiStopMessage = true;
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("No output ports to wire up.");
            }
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




        private void NotifyPropertyChanged ([CallerMemberName]string propertyName ="")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

    }
}
