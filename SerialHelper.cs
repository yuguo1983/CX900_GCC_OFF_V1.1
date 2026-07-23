using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CX900
{
    internal class SerialHelper
    {
        private int baudRate;
        private byte order;
        private byte devnum;
        private Int16 datalen;
        private string portname;

        public byte askflag = 0;
        public SerialPort serial=new SerialPort ();
        public int Baudrate { get => baudRate; set => baudRate = value; }
        public byte Order { get => order; set => order = value; }
        public byte Devnum { get => devnum; set => devnum = value; }
        public short Datalen { get => datalen; set => datalen = value; }
        public string Portname { get => portname; set => portname = value; }

        public SerialHelper()
        {
        }




        public void Open()
        {
            serial.PortName = portname;
            serial.BaudRate = baudRate;
            serial.Parity = Parity.None;
            serial.StopBits = StopBits.One;
            serial.DataBits = 8;
            if (!serial.IsOpen)
            {
                serial.Open();
            }
        }




        /// <summary>
        /// 数据包封装
        /// </summary>
        /// <param name="buf"></param>
        /// <param name="offset"></param>
        /// <param name="len"></param>
        public void SendPake(byte[] buf, int length)
        {

            try
            {
                if (!serial.IsOpen)
                {
                    MessageBox.Show("串口没有打开");
                }
                else
                {
                    byte xor = 0;
                    byte[] tembuf = new byte[2048];
                    tembuf[0] = 0x55;
                    tembuf[1] = 0xaa;
                    tembuf[2] = devnum;
                    tembuf[3] = order;
                    tembuf[4] = Convert.ToByte(length >> 8);
                    tembuf[5] = Convert.ToByte(length & 0xff);
                    for (int i = 0; i < length; i++)
                    {
                        tembuf[i + 6] = buf[i];
                    }
                    for (int i = 0; i < length + 6; i++)
                    {
                        xor ^= tembuf[i];
                    }
                    tembuf[length + 6] = xor;
                    tembuf[length + 7] = 0xe3;
                    tembuf[length + 8] = 0xe4;
                    int length1 = length + 9;
                    serial.Write(tembuf, 0, length1);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("SendPake exception: " + ex.Message);
                throw;
            }

        }



       // public Progbar bar;

        Mutex mutex = new Mutex();



        public int test()
        {
            return varclass.Prosbar;
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="path"></param>
        public void SendFile(string path)
        {

            mutex.WaitOne();
            int temp = 0;

            varclass.Prosbar = 0;
            byte[] fs = File.ReadAllBytes(path);
            order = (byte)SendType.FILE;
            devnum = 0x01;
            int val = 0;
            byte[] buffer = new byte[4096];
            byte[] recvebuf = new byte[2048];
            if (fs.Length > 1024)
            {
                int lens = fs.Length / 1024;

                for (int i = 0; i < lens; i++)
                {
                    for (int j = 0; j < 1024; j++)
                    {
                        buffer[j] = fs[i * 1024 + j];

                    }
                    Array.Clear(recvebuf, 0, recvebuf.Length);
                    SendPake(buffer, 1024);
                    int ackTimeout = 500;
                    while (ackTimeout-- > 0)
                    {
                        int bytesAvailable = serial.BytesToRead;
                        if (bytesAvailable <= 0)
                        {
                            Thread.Sleep(10);
                            continue;
                        }
                        int d = serial.Read(recvebuf, 0, Math.Min(bytesAvailable, recvebuf.Length));
                        if (d < 5) continue;
                        if (recvebuf[0] == 0x55 && recvebuf[1] == 0xaa)
                        {
                            if (recvebuf[4] == 0x01)
                            {
                                break;
                            }
                            else if (recvebuf[4] == 0x02)
                            {
                                SendPake(buffer, 1024);
                                break;
                            }
                        }
                        Thread.Sleep(10);
                    }
                    if (ackTimeout <= 0)
                    {
                        Debug.WriteLine("SendFile timeout waiting for acknowledgement.");
                        break;
                    }
                    Array.Clear(recvebuf, 0, recvebuf.Length);
                    val++;
                    Debug.WriteLine("send {0} form sucessful", val.ToString());
                    varclass.Prosbar = 80;
                   
                }
                int len = fs.Length % 1024;
                for (int k = 0; k < len; k++)
                {
                    buffer[k] = fs[lens * 1024 + k];
                    temp += 1;
                    temp = temp / fs.Length * 10000;

                }
                Array.Clear(recvebuf, 0, recvebuf.Length);
                SendPake(buffer, len);
                int ackTimeout2 = 500;
                while (ackTimeout2-- > 0)
                {
                    int bytesAvailable = serial.BytesToRead;
                    if (bytesAvailable <= 0)
                    {
                        Thread.Sleep(10);
                        continue;
                    }
                    int d = serial.Read(recvebuf, 0, Math.Min(bytesAvailable, recvebuf.Length));
                    if (d < 5) continue;
                    if (recvebuf[0] == 0x55 && recvebuf[1] == 0xaa)
                    {
                        if (recvebuf[4] == 0x01) break;
                        else if (recvebuf[4] == 0x02)
                        {
                            SendPake(buffer, len);
                            break;
                        }
                    }
                    Thread.Sleep(10);
                }
                if (ackTimeout2 <= 0)
                {
                    Debug.WriteLine("SendFile timeout waiting for acknowledgement (remainder).");
                }
                Array.Clear(recvebuf, 0, recvebuf.Length);


                val++;
                Debug.WriteLine("send {0} form finish", val.ToString());
                varclass.Prosbar = 100;
                
            }
            else
            {
                varclass.Prosbar = 0;
                
                for (int i = 0; i < fs.Length; i++)
                {
                    buffer[i] = fs[i];
                    varclass.Prosbar = i / fs.Length * 1000;
                    test();
                    val++;
                }
                varclass.Ask = 0;
                Array.Clear(recvebuf, 0, recvebuf.Length);
                SendPake(buffer, fs.Length);
                int ackTimeout3 = 500;
                while (ackTimeout3-- > 0)
                {
                    int bytesAvailable = serial.BytesToRead;
                    if (bytesAvailable <= 0)
                    {
                        Thread.Sleep(10);
                        continue;
                    }
                    int d = serial.Read(recvebuf, 0, Math.Min(bytesAvailable, recvebuf.Length));
                    if (d < 5) continue;
                    if (recvebuf[0] == 0x55 && recvebuf[1] == 0xaa)
                    {
                        if (recvebuf[4] == 0x01) break;
                        else if (recvebuf[4] == 0x02)
                        {
                            SendPake(buffer, fs.Length);
                            break;
                        }
                    }
                    Thread.Sleep(10);
                }
                if (ackTimeout3 <= 0)
                {
                    Debug.WriteLine("SendFile timeout waiting for acknowledgement (short file).");
                }
                Array.Clear(recvebuf, 0, recvebuf.Length);
                varclass.Prosbar = 100;
               
            }
            mutex.ReleaseMutex();
        }







        /// <summary>
        /// 
        /// </summary>
        /// <param name="command"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public byte[] SendCommand(command command, byte[] value)
        {
            byte[] temp = new byte[20];
            temp[0] = (byte)command;
            int len = value.Length;
            if (len > 19)
            {
                Debug.Write("命令超出范围");
            }
            else
            {
                for (int i = 0; i < len; i++)
                {
                    temp[1 + i] = value[i];
                }
            }

            return temp;
        }




    
}
}
