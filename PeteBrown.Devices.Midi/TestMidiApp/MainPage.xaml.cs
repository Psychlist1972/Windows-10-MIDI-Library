
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

using PeteBrown.Devices.Midi;
using TestMidiApp.ViewModel;

namespace TestMidiApp
{
    /// <summary>
    /// 
    /// </summary>
    public sealed partial class MainPage : Page
    {

        private MainViewModel _vm;

        public MainPage()
        {
            this.InitializeComponent();

            _vm = new MainViewModel();

        }

        public MainViewModel ViewModel
        {
            get { return _vm; }
        }


        private void Start_Click(object sender, RoutedEventArgs e)
        {
            Start.IsEnabled = false;
            Stop.IsEnabled = true;

            _vm.StartClock();
        }

        private void Stop_Click(object sender, RoutedEventArgs e)
        {
            Start.IsEnabled = true;
            Stop.IsEnabled = false;

            _vm.StopClock();
        }

        //private void Tempo_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        //{
        //    UpdateTempo();
        //}


        private void TestNrpn_Click(object sender, RoutedEventArgs e)
        {
            var channel = byte.Parse(Channel.Text);

            // send the NRPN full (parameter + value) message
            _vm.SendNrpn(channel, UInt16.Parse(ParameterNumber.Text), UInt16.Parse(ParameterValue.Text));

            // a best practice is to null out the parameter when you've finished. This prevents unexpected value changes later
            _vm.SendNrpnParameterNull(channel);
        }





        private void TestRpn_Click(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Debug.WriteLine("Not implemented");
        }
    }
}
