using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using Ymodem;
using System.IO;
using System.IO.Ports;
using System.Diagnostics;

namespace CX900
{
    public partial class DL_form : Form
    {
        public delegate void mydelegate(string path);
       

        public string prortname ;
        public DL_form(string str)
        {
            InitializeComponent();
            prortname = str;
        }

        public  mydelegate mydel;
        
        private void bt_slectfile_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Multiselect = false;
            ofd.Filter = "BIN文件|*.bin";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                long length = new System.IO.FileInfo(ofd.FileName).Length;
                if (length > 0x50000)
                {
                    MessageBox.Show("IAP文件超出范围","提示");
                    return;
                }
                MainForm.IAPpath = ofd.FileName;
               tb_iapfilepath.Text = MainForm.IAPpath;
                
            }
            
        }
        System.Threading.Thread downloadThread;
        private Ymodem.Ymodem ymodem;
        private void bt_updataiap_Click(object sender, EventArgs e)
        {
            try
            {
                if (tb_iapfilepath.Text == "")
                {
                    MessageBox.Show("请选择有效升级文件","提示");
                    return;
                }

            mydel( MainForm.IAPpath);
            Thread.Sleep(2000);
            ymodem = new Ymodem.Ymodem();
            ymodem.serialPort = new System.IO.Ports.SerialPort();
            
            ymodem.Path = MainForm.IAPpath;
            ymodem.serialPort.PortName = prortname;
            ymodem.serialPort.BaudRate = Convert.ToInt32(460800);
            ymodem.serialPort.Parity= System.IO.Ports.Parity.None;
            ymodem.serialPort.StopBits = System.IO.Ports.StopBits.One;
            ymodem.serialPort.DataBits = 8;
            ymodem.serialPort.Open();
            if (!ymodem.serialPort.IsOpen)
            {
                MessageBox.Show("串口没有打开","提示");
                return;
            }
            lb_downloadrasult.Text = "正在下载......";
            bt_updataiap.Enabled = false;
           downloadThread = new System.Threading.Thread(ymodem.YmodemUploadFile);
            ymodem.NowDownloadProgressEvent += new EventHandler(NowDownloadProgressEvent);
            ymodem.DownloadResultEvent += new EventHandler(DownloadFinishEvent);
            downloadThread.Start();

            }
            catch (Exception eee)
            {

                Debug.WriteLine(eee.Message);
            }
        }
        private delegate void DownloadFinish(bool finish);
        private void DownloadFinishEvent(object sender, EventArgs e)
        {
            // 默认假设下载成功，因为 Ymodem 事件没有传递状态
            bool finish = true;
            DownloadFinish status = new DownloadFinish(UploadFileResult);
            this.Invoke(status, finish);
        }
        private void UploadFileResult(bool result)
        {
            if (result == true)
            {
                lb_downloadrasult.Text = "下载成功";
                ymodem.serialPort.Close();
                this.Close();

                //this.progressBar1.Value = 0;
                //serialHelper.Portname = cb_serialprot.Text;
                //serialHelper.Baudrate = 115200;
                //serialHelper.serial.DataReceived += new SerialDataReceivedEventHandler(_dataReceive);
                //progressBar1.Visible = false;
                //lb_downloaddis.ForeColor = Color.Green;
                //lb_downloaddis.Text = "下载成功";
            }
            else
            {
                //lb_downloaddis.ForeColor = Color.Red;
                //lb_downloaddis.Text = "下载失败";
                ymodem.serialPort.Close();
                lb_downloadrasult.Text = "下载失败";
                this.progressBar2.Value = 0;
                progressBar2.Visible = false;
            }
            bt_updataiap.Enabled = true;

        }
        private delegate void NowDownloadProgress(int nowValue);
        private void NowDownloadProgressEvent(object sender, EventArgs e)
        {
            int value = Convert.ToInt32(sender);
            NowDownloadProgress count = new NowDownloadProgress(UploadFileProgress);
            this.Invoke(count, value);
        }
        private void UploadFileProgress(int count)
        {
            progressBar2.Value = count;
        }
    }
}
