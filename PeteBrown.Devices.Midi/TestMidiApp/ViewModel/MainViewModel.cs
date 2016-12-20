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
using Windows.UI.Xaml.Interop;

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

            // these are for debugging only
            _watcher.OutputPortDescriptors.VectorChanged += OutputPortDescriptors_VectorChanged;
            _watcher.InputPortDescriptors.VectorChanged += InputPortDescriptors_VectorChanged;

            // the built-in synth requires an add-on package for the solution, and isn't very good anyway
            // this is not a required setting. However, if you don't ignore it, you need to add the DLS package
            // via project->add reference->universal windows->extensions
            _watcher.IgnoreBuiltInWavetableSynth = true;

            // make sure you have the event handlers wired up before this.
            _watcher.EnumerateInputPorts();
            _watcher.EnumerateOutputPorts();          

        }


        private void InputPortDescriptors_VectorChanged(Windows.Foundation.Collections.IObservableVector<MidiDeviceInformation> sender, Windows.Foundation.Collections.IVectorChangedEventArgs @event)
        {
            //System.Diagnostics.Debug.WriteLine("InputPortDescriptors - VectorChanged ");
            System.Diagnostics.Debug.WriteLine(@event.CollectionChange);
        }

        private void OutputPortDescriptors_VectorChanged(Windows.Foundation.Collections.IObservableVector<MidiDeviceInformation> sender, Windows.Foundation.Collections.IVectorChangedEventArgs @event)
        {
            //System.Diagnostics.Debug.WriteLine("OutputPortDescriptors - VectorChanged");
            System.Diagnostics.Debug.WriteLine(@event.CollectionChange);
        }


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
            _clock.Start();
        }

        public void StopClock()
        {
            _clock.Stop();
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
                //System.Diagnostics.Debug.WriteLine("- Output -----");
                //System.Diagnostics.Debug.WriteLine(info.Name);
                //System.Diagnostics.Debug.WriteLine(info.Id);
                //System.Diagnostics.Debug.WriteLine("--------------");

                var port = (MidiOutPort)await MidiOutPort.FromIdAsync(info.Id);

                DebugDisplayDeviceInformationProperties(info.DeviceInformation);


                // If you don't want the clock on all ports, here's where you'd change the code
                if (port != null)
                    _clock.OutputPorts.Add(port);
                else
                    System.Diagnostics.Debug.WriteLine("Failed to create clock output port with Name:{0} and Id {1}", info.Name, info.Id);
            }

            if (_clock.OutputPorts.Count > 0)
            {
                //System.Diagnostics.Debug.WriteLine("About to create clock.");

                _clock.SendMidiStartMessage = true;
                _clock.SendMidiStopMessage = true;
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("No output ports to wire up.");
            }
        }


        private void DebugDisplayDeviceInformationProperties(DeviceInformation info)
        {
            foreach (var key in info.Properties.Keys)
            {
                var val = info.Properties[key];

                System.Diagnostics.Debug.Write("- (property) " + key + ": ");

                if (val != null)
                {
                    System.Diagnostics.Debug.WriteLine(info.Properties[key].ToString());
                }
                else
                {
                    System.Diagnostics.Debug.WriteLine("(null)");
                }
            }


        }


        // All input ports have been enumerated
        private void _watcher_InputPortsEnumerated(MidiDeviceWatcher sender)
        {
            foreach (var info in sender.InputPortDescriptors)
            {
                System.Diagnostics.Debug.WriteLine("- Input -----");
                System.Diagnostics.Debug.WriteLine("- Name: " + info.Name);
                System.Diagnostics.Debug.WriteLine("- Id: " + info.Id);
                System.Diagnostics.Debug.WriteLine("- Kind: " + info.DeviceInformation.Kind);
                System.Diagnostics.Debug.WriteLine("- InterfaceType: " + info.InterfaceType);

                DebugDisplayDeviceInformationProperties(info.DeviceInformation);

                System.Diagnostics.Debug.WriteLine("--------------");
            }
        }



        // just sends the message out of all channels
        public void SendNrpn(byte channel, ushort parameterNumber, ushort parameterValue)
        {
            var message = new MidiNrpnParameterValueChangeMessage();

            message.ParameterNumber = parameterNumber;
            message.ParameterValue = parameterValue;
            message.Channel = channel;

            // just using the clock OutputPorts because it's convenient. 
            foreach (MidiOutPort port in _clock.OutputPorts)
            {
                System.Diagnostics.Debug.WriteLine("Sending NRPN: Channel: {0}, Parameter: {1}, Value: {2} on interface {3}", message.Channel, message.ParameterNumber, message.ParameterValue, port.DeviceId);
                port.SendMessage(message);
            }
        }

        public void SendNrpnParameterNull(byte channel)
        {
            var message = new MidiNrpnParameterNullMessage();

            message.Channel = channel;

            // just using the clock OutputPorts because it's convenient. 
            foreach (MidiOutPort port in _clock.OutputPorts)
            {
                System.Diagnostics.Debug.WriteLine("Sending NRPN null: Channel: {0}, interface {1}", message.Channel, port.DeviceId);
                port.SendMessage(message);
            }
        }




        private void NotifyPropertyChanged ([CallerMemberName]string propertyName ="")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

    }
}
