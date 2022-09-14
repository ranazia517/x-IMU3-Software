// This file was generated by Examples/CSharp/x-IMU3-Examples/generate_main.py

using System;

namespace Ximu3Examples
{
    class Program
    {
        static int Main(string[] args)
        {
            Console.WriteLine("Select example");
            Console.WriteLine("A. BluetoothConnection");
            Console.WriteLine("B. Commands");
            Console.WriteLine("C. DataLogger");
            Console.WriteLine("D. FileConverter");
            Console.WriteLine("E. GetAvailablePorts");
            Console.WriteLine("F. NetworkAnnouncement");
            Console.WriteLine("G. OpenAndPing");
            Console.WriteLine("H. SerialConnection");
            Console.WriteLine("I. SerialDiscovery");
            Console.WriteLine("J. TcpConnection");
            Console.WriteLine("K. UdpConnection");
            Console.WriteLine("L. UsbConnection");
            switch (Helpers.GetKey())
            {
                case 'A':
                    new BluetoothConnection();
                    break;
                case 'B':
                    new Commands();
                    break;
                case 'C':
                    new DataLogger();
                    break;
                case 'D':
                    new FileConverter();
                    break;
                case 'E':
                    new GetAvailablePorts();
                    break;
                case 'F':
                    new NetworkAnnouncement();
                    break;
                case 'G':
                    new OpenAndPing();
                    break;
                case 'H':
                    new SerialConnection();
                    break;
                case 'I':
                    new SerialDiscovery();
                    break;
                case 'J':
                    new TcpConnection();
                    break;
                case 'K':
                    new UdpConnection();
                    break;
                case 'L':
                    new UsbConnection();
                    break;
            }
            Console.WriteLine("Press any key to exit");
            Helpers.GetKey();
            return 0;
        }
    }
}
