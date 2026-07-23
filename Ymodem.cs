using System;
using System.IO;
using System.Diagnostics;
using System.Threading;
using CX900;
using System.IO.Ports;

namespace Ymodem
{
    public enum InitialCrcValue { Zeros, NonZero1 = 0xffff, NonZero2 = 0x1D0F }
    
    public class Ymodem
    {

        /*
         * Upload file via Ymodem protocol to the device
         * ret: is the transfer succeeded? true is if yes
         */
        private string path;
        public string Path { get { return path; } set { path = value; } }
        private string portName;
        public string PortName { get { return portName; } set { portName = value; } }
        private int baudRate;
        public int BaudRate { get { return baudRate; } set { baudRate = value; } }
        public System.IO.Ports.SerialPort serialPort = new System.IO.Ports.SerialPort();
        public event EventHandler NowDownloadProgressEvent;
        public event EventHandler DownloadResultEvent;

        public void YmodemUploadFile()
        {
            /* control signals */
            const byte STX = 2;  // Start of TeXt 
            const byte EOT = 4;  // End Of Transmission
            const byte ACK = 6;  // Positive ACknowledgement
            const byte C = 67;   // capital letter C
            
            /* sizes */
            const int dataSize = 1024;
            const int crcSize = 2;

            /* THE PACKET: 1029 bytes */
            /* header: 3 bytes */
            // STX
            int packetNumber = 0;
            int invertedPacketNumber = 255;
            /* data: 1024 bytes */
            byte[] data = new byte[dataSize];
            /* footer: 2 bytes */
            byte[] CRC = new byte[crcSize];

            /* get the file */
            using (FileStream fileStream = new FileStream(path, FileMode.Open, FileAccess.Read))
            {
                //serialPort.PortName = portName; serialPort.BaudRate = baudRate;
                //serialPort.Open();

                //try
                //{

                //serialPort.Write(new byte[] { 0x31 }, 0, 1);
                /* send the initial packet with filename and filesize */
               
                serialPort.DiscardInBuffer();
            serialPort.ReadTimeout = 5000;
            serialPort.WriteTimeout = 5000;
            /*
            try
            {
            */
            byte byte1;
            MainForm.mutex1.WaitOne();
            try
            {
                byte1 = (byte)serialPort.ReadByte();
            }
            finally
            {
                MainForm.mutex1.ReleaseMutex();
            }
            if (byte1 != C)
                    {
                        Debug.WriteLine("Can't begin the transfer.");
                        serialPort.Close();
                        DownloadResultEvent?.Invoke(this, EventArgs.Empty);
                        return;// false;
                    }
                    else
                    {
                        Debug.WriteLine(" begin the transfer.");

                    }
                    /*
                }
                catch (Exception e)
                {

                    Debug.WriteLine(e.Message);
                }
                */
                

                sendYmodemInitialPacket(STX, packetNumber, invertedPacketNumber, data, dataSize, path, fileStream, CRC, crcSize);
                Thread.Sleep(100);
                
                byte temp;
                MainForm.mutex1.WaitOne();
                try
                {
                    temp = (byte)serialPort.ReadByte();
                }
                finally
                {
                    MainForm.mutex1.ReleaseMutex();
                }
                Debug.WriteLine(temp);
                if (temp != ACK)//(serialPort.ReadByte() != ACK)
                {
                    Debug.WriteLine("Can't send the initial packet.");
                    DownloadResultEvent?.Invoke(this, EventArgs.Empty);
                    return;// false;
                }
                else { };
                MainForm.mutex1.WaitOne();
                try
                {
                    temp = (byte)serialPort.ReadByte();
                }
                finally
                {
                    MainForm.mutex1.ReleaseMutex();
                }
                if (temp != C)
                {
                    DownloadResultEvent?.Invoke(this, EventArgs.Empty);
                    return;// false;
                }
                /* send packets with a cycle until we send the last byte */
                int fileReadCount;
                do
                {
                    /* if this is the last packet fill the remaining bytes with 0 */
                    fileReadCount = fileStream.Read(data, 0, dataSize);
                    if (fileReadCount == 0) break;
                    if (fileReadCount != dataSize)
                        for (int i = fileReadCount; i < dataSize; i++)
                            data[i] = 0;

                    /* calculate packetNumber */
                    packetNumber++;
                    if (packetNumber > 255)
                        packetNumber -= 256;
                    Console.WriteLine(packetNumber);

                    /* calculate invertedPacketNumber */
                    invertedPacketNumber = 255 - packetNumber;

                    /* calculate CRC */
                    Crc16Ccitt crc16Ccitt = new Crc16Ccitt(InitialCrcValue.Zeros);
                    CRC = crc16Ccitt.ComputeChecksumBytes(data);

                /* send the packet */
                sendYmodemPacket(STX, packetNumber, invertedPacketNumber, data, dataSize, CRC, crcSize);
                int progress = (int)(((float)dataSize * packetNumber) / fileStream.Length * 100);
                Debug.WriteLine("progress:  " + progress);
                if (progress > 100) progress = 100;
                NowDownloadProgressEvent?.Invoke(progress, EventArgs.Empty);
                    /* wait for ACK */
                    MainForm.mutex1.WaitOne();
                    try
                    {
                        temp = (byte)serialPort.ReadByte();
                    }
                    finally
                    {
                        MainForm.mutex1.ReleaseMutex();
                    }
                    if (temp != ACK)
                    {
                        Debug.WriteLine("temp"+temp);
                        Debug.WriteLine("Couldn't send a packet.");
                        DownloadResultEvent?.Invoke(this, EventArgs.Empty);
                        return;// false;
                    }
                } while (dataSize == fileReadCount);

                /* send EOT (tell the downloader we are finished) */
                serialPort.Write(new byte[] { EOT }, 0, 1);
                /* send closing packet */
                packetNumber = 0;
                invertedPacketNumber = 255;
                data = new byte[dataSize];
                CRC = new byte[crcSize];
                sendYmodemClosingPacket(STX, packetNumber, invertedPacketNumber, data, dataSize, CRC, crcSize);
                /* get ACK (downloader acknowledge the EOT) */
                MainForm.mutex1.WaitOne();
                try
                {
                    temp = (byte)serialPort.ReadByte();
                }
                finally
                {
                    MainForm.mutex1.ReleaseMutex();
                }
                if (temp != ACK)
                {
                    Debug.WriteLine("Can't complete the transfer.");
                    DownloadResultEvent?.Invoke(this, EventArgs.Empty);

                    return;// false;
                }
           
            //}
            //catch (TimeoutException)
            //{
            //    throw new Exception("Eductor does not answering");
                
            //}
            //finally
            //{
            //    fileStream.Close();

            //}
            //serialPort.Close();
            }
            Debug.WriteLine("File transfer is succesful");
            DownloadResultEvent?.Invoke(this, EventArgs.Empty);
            return;// true;
        }

        private void sendYmodemInitialPacket(byte STX, int packetNumber, int invertedPacketNumber, byte[] data, int dataSize, string filePath, FileStream fileStream, byte[] CRC, int crcSize)
        {
            string fileName = System.IO.Path.GetFileName(filePath);
            string fileSize = fileStream.Length.ToString();
            Debug.WriteLine("fileSize" + fileSize);
            /* add filename to data */
            int i;
            for (i = 0; i < fileName.Length && (fileName.ToCharArray()[i] != 0); i++)
            {
                data[i] = (byte)fileName.ToCharArray()[i];
            }
            data[i] = 0;

            /* add filesize to data */
            int j;
            for (j = 0; j < fileSize.Length && (fileSize.ToCharArray()[j] != 0); j++)
            {
                data[(i + 1) + j] = (byte)fileSize.ToCharArray()[j];
            }
            data[(i + 1) + j] = 0;

            /* fill the remaining data bytes with 0 */
            for (int k = ((i + 1) + j) + 1; k < dataSize; k++)
            {
                data[k] = 0;
            }

            /* calculate CRC */
            Crc16Ccitt crc16Ccitt = new Crc16Ccitt(InitialCrcValue.Zeros);
            CRC = crc16Ccitt.ComputeChecksumBytes(data);

            /* send the packet */
            sendYmodemPacket(STX, packetNumber, invertedPacketNumber, data, dataSize, CRC, crcSize);
        }

        private void sendYmodemClosingPacket(byte STX, int packetNumber, int invertedPacketNumber, byte[] data, int dataSize, byte[] CRC, int crcSize)
        {
            /* calculate CRC */
            Crc16Ccitt crc16Ccitt = new Crc16Ccitt(InitialCrcValue.Zeros);
            CRC = crc16Ccitt.ComputeChecksumBytes(data);

            /* send the packet */
            sendYmodemPacket(STX, packetNumber, invertedPacketNumber, data, dataSize, CRC, crcSize);
        }

        private void sendYmodemPacket(byte STX, int packetNumber, int invertedPacketNumber, byte[] data, int dataSize, byte[] CRC, int crcSize)
        {
            try
            {
                serialPort.Write(new byte[] { STX }, 0, 1);
                serialPort.Write(new byte[] { (byte)packetNumber }, 0, 1);
                Debug.WriteLine("\rpacketNumber:" + packetNumber);
                serialPort.Write(new byte[] { (byte)invertedPacketNumber }, 0, 1);
                Debug.WriteLine("\rinvertedPacketNumber:" + invertedPacketNumber);
                serialPort.Write(data, 0, dataSize);
                serialPort.Write(CRC, 0, crcSize);
                //Debug.WriteLine("\rdata:");
                //for (UInt16 i = 0; i < dataSize; i++)
                //{
                //    Debug.Write(string.Format("{0:X}",data[i]) + "\t");
                //}
                //Debug.WriteLine("");
            }
            catch (Exception ee)
            {

                Debug.WriteLine(ee.Message);
            }
            
        }
    }
    public class Crc16Ccitt
    {
        const ushort poly = 4129;
        ushort[] table = new ushort[256];
        ushort initialValue = 0;

        public ushort ComputeChecksum(byte[] bytes)
        {
            ushort crc = this.initialValue;
            for (int i = 0; i < bytes.Length; ++i)
            {
                crc = (ushort)((crc << 8) ^ table[((crc >> 8) ^ (0xff & bytes[i]))]);
            }
            return crc;
        }

        public byte[] ComputeChecksumBytes(byte[] bytes)
        {
            ushort crc = ComputeChecksum(bytes);
            return BitConverter.GetBytes(crc);
        }

        public Crc16Ccitt(InitialCrcValue initialValue)
        {
            this.initialValue = (ushort)initialValue;
            ushort temp, a;
            for (int i = 0; i < table.Length; ++i)
            {
                temp = 0;
                a = (ushort)(i << 8);
                for (int j = 0; j < 8; ++j)
                {
                    if (((temp ^ a) & 0x8000) != 0)
                    {
                        temp = (ushort)((temp << 1) ^ poly);
                    }
                    else
                    {
                        temp <<= 1;
                    }
                    a <<= 1;
                }
                table[i] = temp;
            }
        }
    }
}