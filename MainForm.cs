//using Microsoft.Windows.PowerShell.Gui.Internal;
using Cyotek.Windows.Forms;
using ScintillaNET;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using System.Xml;
using System.Xml.Linq;
using System.Xml.Serialization;
using System.Xml.XPath;
using static CX900.StructClass;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Button;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TextBox;
using Ymodem;
using System.Security.Cryptography;
using ICSharpCode.SharpZipLib.Zip;

namespace CX900
{
    public delegate void probardele(int value);

    public partial class MainForm : Form
    {

        private long receive_count = 0;
        private long send_count = 0;
        private StringBuilder sb = new StringBuilder();     //为了避免在接收处理函数中反复调用，依然声明为一个全局变量
        private DateTime current_time = new DateTime();    //为了避免在接收处理函数中反复调用，依然声明为一个全局变量
        private StringBuilder builder = new StringBuilder();    //避免在事件处理方法中反复创建，定义为全局
        private static bool bootiapflag = false;
        CodeCompile cc = new CodeCompile();
        Label lb_kuancolor = new Label();
        Label lb_backcolor = new Label();
        Label lb_crosskuancolor = new Label();
        Label lb_crossbackcolor = new Label();
        Label lb_colorset = new Label();
        Label lb_fkcolor1 = new Label();
        Label lb_fkcolor2 = new Label();
        Label lb_grcolcolor = new Label();
        Label lb_grrowcolor = new Label();

        public static bool Calculate = false;

        TextBox tb_input1 = new TextBox();
        TextBox tb_input2 = new TextBox();
        TextBox tb_input3 = new TextBox();
        TextBox tb_input4 = new TextBox();
        TextBox tb_input5 = new TextBox();
        TextBox tb_input6 = new TextBox();

        string wide = "";
        string height = "";
        string hfw = "";
        string hbw = "";
        string hsw = "";
        string vfw = "";
        string vbw = "";
        string vsw = "";



        public int FPS = 0;
        public ColorPickerDialog color_picker1;
        public ColorPickerDialog color_picker2;


        List<String> LB_list = new List<string>();
        public String configpath = @"./config.xml";
        public String pixpath = @"./pix_config.xml";
        public String codepath = @"./Module/lcd_cfg.c";
        public String piclistpath = @"./pic_list.xml";
        public string APPPath = @"./build/GD32F303VET6.bin";
        public string Connect = "System_Ready";
        public string Userfilepath= @"./Module/app.c";
        public string userfiledemopath = "./appdemo";
        public string publiccodepath = @"./Module/power_task.c";
        public string moduledirpath = @".\Module";
        public string libpath = @".\libGD32F303VET6.a";
        XmlDocument doc = new XmlDocument();
        public static Mutex mutex1 = new Mutex();
        private Object thisLock = new Object();//创建对象锁

        // 编译错误行映射: RichTextBox行索引 → (文件名, GCC行号)
        private struct CompileErrorInfo
        {
            public string fileName;
            public int lineNumber;
        }
        private Dictionary<int, CompileErrorInfo> _compileErrorMap = new Dictionary<int, CompileErrorInfo>();
        private int _lastParsedLineCount = 0;

        public StructClass.all_paramter parent = new StructClass.all_paramter();
        public StructClass.pMIPI_Para_Table child = new StructClass.pMIPI_Para_Table();

        SerialHelper serialHelper = new SerialHelper();

        // 用于双击打开文件时的文件路径
        public string FileToOpen { get; set; }
        
        public delegate void SerialDataReceivedEventargs(object sender, SerialDataReceivedEventArgs e, byte[] _data);
        public bool ReceiveEventFlag = false;
        public Ymodem.Ymodem ymodem;
        System.Threading.Thread downloadThread;





        //DL_form窗口用
        public static String IAPpath;
        public static bool IAP_Flag;
        public probardele probar;
        #region MainForm
        public MainForm()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;

            // 必须在任何依赖路径的操作之前，将所有相对路径转为基于程序目录的绝对路径
            // 原因：双击 .cxkj 文件启动时，Environment.CurrentDirectory 可能不是程序所在目录
            string appDir = Application.StartupPath;
            configpath = Path.Combine(appDir, "config.xml");
            pixpath = Path.Combine(appDir, "pix_config.xml");
            codepath = Path.Combine(appDir, "Module", "lcd_cfg.c");
            piclistpath = Path.Combine(appDir, "pic_list.xml");
            APPPath = Path.Combine(appDir, "build", "GD32F303VET6.bin");
            Userfilepath = Path.Combine(appDir, "Module", "app.c");
            userfiledemopath = Path.Combine(appDir, "appdemo");
            publiccodepath = Path.Combine(appDir, "Module", "power_task.c");
            moduledirpath = Path.Combine(appDir, "Module");
            libpath = Path.Combine(appDir, "libGD32F303VET6.a");

            try
            {
            this.scintilla1.Styles[32].Size = 10;
            InitHotkeys();
            DoloadParamter();
            DataInit();
            InitSyntaxColoring();
            InitNumberMargin();
            InitNumberMargin2();
            InitDragDropFile();
            InitDragDropFile1();
            InitBookmarkMargin();
            InitBookmarkMargin1();
            
            // 初始化编译输出框的右键菜单
            InitCompileOutputContextMenu();
            
            this.scintilla1.WrapMode = WrapMode.Word;
            this.scintilla1.IndentationGuides = IndentView.LookBoth;

              
          
            LoadDataFromFile(codepath);
            LoadPublicCode(publiccodepath);
            openfile.Dispose();
            progressBar1.Visible = false;
            Image image = MakeImage.makeFrameImg(Color.White, Color.Black, 256, 448);
            pb_photo.Image = image;
            int width = pb_photo.Width + 4;
            int hight = pb_photo.Height + 4;
            pb_back.Size = new Size(Width, hight);
            pb_back.Image = MakeImage.makeColorImg(Color.Gray, 276, 468);
            rb_zhifu.Checked = true;
            rb_sendascii .Checked = true;
            lb_txnumber.Text = "Tx:" + send_count.ToString() + "Bytes";   
            lb_rxnumber.Text = "Rx:" + receive_count.ToString() + "Bytes";
            serialHelper.Baudrate = 460800;
            lb_list.SelectedIndex = 0;
            lb_slect.SelectedIndex = lb_slect.Items.Count - 1;
            cb_lcdtype.SelectedIndex = 0;
                try
                {
                    foreach (var item in System.IO.Ports.SerialPort.GetPortNames())
                    {
                        cb_serialprot.Items.Add(item);
                    }
                    if (cb_serialprot.Items.Count <= 0)
                    {
                        cb_serialprot.Items.Add("NO Serial");
                        cb_serialprot.SelectedIndex = 0;
                        return;
                    }
                    else
                    {
                       cb_serialprot.SelectedIndex = System.IO.Ports.SerialPort.GetPortNames().Length - 1;
                    }
                   
                    serialHelper.Portname = cb_serialprot.Text;
                    
                }
                catch (Exception)
                {

                    //throw;
                }
            }
            catch (Exception)
            {

                //throw;
            }
        }
        #endregion

        private static void BindExceptionHandler()
        {
            //设置应用程序处理异常方式：ThreadException处理
            Application.SetUnhandledExceptionMode(UnhandledExceptionMode.CatchException);
            //处理UI线程异常
            Application.ThreadException += new System.Threading.ThreadExceptionEventHandler(Application_ThreadException);
            //处理未捕获的异常
            AppDomain.CurrentDomain.UnhandledException += new UnhandledExceptionEventHandler(CurrentDomain_UnhandledException);
        }
        /// <summary>
        /// 处理UI线程异常
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        static void Application_ThreadException(object sender, System.Threading.ThreadExceptionEventArgs e)
        {
            //LogHelper.ErrorLog(null, e.Exception as Exception);
        }
        /// <summary>
        /// 处理未捕获的异常
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        static void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            //LogHelper.ErrorLog(null, e.ExceptionObject as Exception);
        }



        #region  wndproc
       
        protected override void WndProc(ref Message m)
        {

            try
            {
                bool flag2 = m.Msg == 537;
                if (flag2)
                {
                    int num = m.WParam.ToInt32();
                    if (num != 32768)
                    {
                        if (num == 32772)
                        {

                            Thread thread = new Thread(new ThreadStart(this.getSerialPortAllName));
                            thread.Start();

                        }
                    }
                    else
                    {

                        Thread thread2 = new Thread(new ThreadStart(this.getSerialPortAllName));
                        thread2.Start();


                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            try
            {
                base.WndProc(ref m);
            }
            catch (Exception ex2)
            {
                MessageBox.Show(ex2.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
            }
        }

        #endregion


        #region checkserial
        public static bool connectflag = false;
        private void checkserial()
        {
            try
            {


                    while (this.IsHandleCreated)
                    {
                        Thread.Sleep(300);
                        mutex1.WaitOne();
                        this?.BeginInvoke((EventHandler)(delegate
                        {
                            try
                            {
                                if (base.IsDisposed == false)
                                {
                                    if (serialHelper.serial.IsOpen)
                                    {
                                        cb_serialprot.Enabled = false;
                                        if (connectflag == false)
                                        {
                                            serialHelper.serial.WriteLine("connect \r\n");
                                            bt_pwon.Enabled = false;
                                            bt_pwoff.Enabled = false;
                                            bt_up.Enabled = false;
                                            bt_down.Enabled = false;
                                            bt_auto.Enabled = false;
                                            bt_downloadapp.Enabled = false;
                                            bt_openserial.BackColor = Color.Red;
                                            bt_openserial.Text = "打开串口";
                                            lb_connect.ForeColor = Color.Red;
                                            lb_connect.Text = "CX900-Tools 已断开";
                                        }
                                        else
                                        {
                                            bt_pwon.Enabled = true;
                                            bt_pwoff.Enabled = true;
                                            bt_up.Enabled = true;
                                            bt_down.Enabled = true;
                                            bt_auto.Enabled = true;
                                            bt_downloadapp.Enabled = true;
                                            bt_openserial.BackColor = Color.Green;
                                            bt_openserial.Text = "关闭串口";
                                            lb_connect.ForeColor = Color.Green;
                                            lb_connect.Text = "CX900-Tools 已连接";
                                        }
                                    }
                                    else
                                    {
                                        serialHelper.serial.Close();
                                        cb_serialprot.Enabled = true;
                                        connectflag = false;
                                        bt_pwon.Enabled = false;
                                        bt_pwoff.Enabled = false;
                                        bt_up.Enabled = false;
                                        bt_down.Enabled = false;
                                        bt_auto.Enabled = false;
                                        bt_downloadapp.Enabled = false;
                                        bt_openserial.BackColor = Color.Red;
                                        bt_openserial.Text = "打开串口";
                                        lb_connect.ForeColor = Color.Red;
                                        lb_connect.Text = "CX900-Tools 已断开";
                                    }
                                }
                                if (Calculate== true & tb_hsw.Text!=""& tb_hfw.Text != "" & tb_hbw.Text != ""& tb_hact.Text != ""& tb_vsw.Text != ""& tb_vfw.Text != "" & tb_vbw.Text != "" & tb_vact.Text != ""& tb_pclk.Text!="")
                                {
                                    if (serialHelper.serial.IsOpen)
                                    {
                                        if (tb_hsw.Text != hsw)
                                        {
                                            hsw = tb_hsw.Text;
                                            serialHelper.serial.WriteLine("rgbhsw" + hsw + "\r\n");
                                        }
                                        if (tb_hfw.Text != hfw)
                                        {
                                            hfw = tb_hfw.Text;
                                            serialHelper.serial.WriteLine("rgbhfw" + hfw + "\r\n");
                                        }
                                        if (tb_hbw.Text != hbw)
                                        {
                                            hbw = tb_hbw.Text;
                                            serialHelper.serial.WriteLine("rgbhbw" + hbw + "\r\n");
                                        }
                                        if (tb_hact.Text != wide)
                                        {
                                            wide = tb_hact.Text;
                                            serialHelper.serial.WriteLine("rgbwide" + wide + "\r\n");
                                        }
                                        if (tb_vsw.Text != vsw)
                                        {
                                            vsw = tb_vsw.Text;
                                            serialHelper.serial.WriteLine("rgbvsw" + vsw + "\r\n");
                                        }
                                        if (tb_vbw.Text != vbw)
                                        {
                                            vbw = tb_vbw.Text;
                                            serialHelper.serial.WriteLine("rgbvbw" + vbw + "\r\n");
                                        }
                                        if (tb_vfw.Text != vfw)
                                        {
                                            vfw = tb_vfw.Text;
                                            serialHelper.serial.WriteLine("rgbvfw" + vfw + "\r\n");
                                        }
                                        if (tb_vact.Text != height)
                                        {
                                            height = tb_vact.Text;
                                            serialHelper.serial.WriteLine("rgbheight" + height + "\r\n");
                                        }
                                    }
                                    int h = Convert.ToUInt16(tb_hsw.Text) + Convert.ToUInt16(tb_hfw.Text) + Convert.ToUInt16(tb_hbw.Text) + Convert.ToUInt16(tb_hact.Text);
                                    int v = Convert.ToUInt16(tb_vsw.Text) + Convert.ToUInt16(tb_vfw.Text) + Convert.ToUInt16(tb_vbw.Text) + Convert.ToUInt16(tb_vact.Text);
                                    int pclock = Convert.ToUInt16(tb_pclk.Text) * 1000000;
                                    if (check_dualport.Checked)
                                    {
                                        FPS = pclock / (h * v) * 2;
                                    }
                                    else
                                    {
                                        FPS = pclock / (h * v);
                                    }
                                    lb_fps.Text = FPS.ToString()+" fps";
                                    Calculate = false;
                                }
                            }
                            catch (Exception)
                            {
                                //MessageBox.Show("erro");
                               // throw;
                            }

                        }));

                        mutex1.ReleaseMutex();
                    }
             
            }
            catch (Exception)
            {

               // throw;
            }
        }
        #endregion







        public void getSerialPortAllName()
        {
            Invoke((EventHandler)(delegate
            {
                try
                {
                    cb_serialprot.Items.Clear();
                    cb_serialprot.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
                    cb_serialprot.SelectedIndex = System.IO.Ports.SerialPort.GetPortNames().Length - 1;//设定选择项    
                    serialHelper.serial.PortName = cb_serialprot.Text;
                    serialHelper.serial.Close();
                    serialHelper.Open();
                    Thread.Sleep(10);
                    serialHelper.serial.Open();
                    bt_openserial.Text = "关闭串口";
                    bt_openserial.BackColor = Color.Green;
                }
                catch (Exception)
                {

                    //throw;
                }

            }));

        }





        private void _dataReceive(object sender, SerialDataReceivedEventArgs e)
        {
           if(serialHelper.serial.IsOpen)
            {
                if (rb_zhifu.Checked)
                {
                    int num = serialHelper.serial.BytesToRead;      //获取接收缓冲区中的字节数
                    receive_count += num;
                    try
                    {
                        //因为要访问UI资源，所以需要使用invoke方式同步ui
                        Invoke((EventHandler)(delegate
                        {
                            if (serialHelper.serial.IsOpen)
                            {
                                if (connectflag == false)
                                {
                                    string str = serialHelper.serial.ReadExisting();
                                    str.Replace("\r\n", "").Replace("\t", "");
                                    //Debug.Write(str);
                                    if (str.Contains(Connect))
                                    {
                                        connectflag = true;
                                       
                                    }
                                    else
                                    {
                                        bt_pwon.Enabled = false;
                                        bt_pwoff.Enabled = false;
                                        bt_up.Enabled = false;
                                        bt_down.Enabled = false;
                                        bt_auto.Enabled = false;
                                        bt_downloadapp.Enabled = false;
                                    }
                                }

                                else
                                {
                                    bt_pwon.Enabled = true;
                                    bt_pwoff.Enabled = true;
                                    bt_up.Enabled = true;
                                    bt_down.Enabled = true;
                                    bt_auto.Enabled = true;
                                    bt_downloadapp.Enabled = true;

                                }
                            }
                            if (cb_checktime.Checked)
                            {
                                current_time = System.DateTime.Now; //获取当前时间
                                if (serialHelper.serial.IsOpen)
                                {
                                    tb_serialreceive.AppendText("[" + current_time.ToString("HH:mm:ss") + "]" + "  " + serialHelper.serial.ReadExisting() + "\r\n");
                                }
                            }
                            else
                            {
                                if (serialHelper.serial.IsOpen)
                                { 
                                    //不显示时间
                                    tb_serialreceive.AppendText(serialHelper.serial.ReadExisting());
                                }
                            }
                            lb_rxnumber.Text = "Rx:" + receive_count.ToString() + "Bytes";
                        }
                          )
                        );
                    }
                    catch (Exception ex)
                    {
                        //响铃并显示异常给用户
                        System.Media.SystemSounds.Beep.Play();
                        MessageBox.Show(ex.Message);

                    }
                }
                else
                {
                    try
                    {


                        int num = serialHelper.serial.BytesToRead;      //获取接收缓冲区中的字节数
                        byte[] received_buf = new byte[num];    //声明一个大小为num的字节数据用于存放读出的byte型数据

                        receive_count += num;                   //接收字节计数变量增加nun
                        lock (thisLock)
                        {
                            serialHelper.serial.Read(received_buf, 0, num);   //读取接收缓冲区中num个字节到byte数组中
                        }
                        //if (Displayer != null)
                        //    Displayer.AddData(received_buf);

                        sb.Clear();     //防止出错,首先清空字符串构造器
                                        //遍历数组进行字符串转化及拼接

                        if (rb_hex.Checked)
                        {
                            //选中HEX模式显示
                            foreach (byte b in received_buf)
                            {
                                sb.Append(b.ToString("X2") + ' ');    //将byte型数据转化为2位16进制文本显示,用空格隔开
                            }
                        }
                        else if (rb_ascii.Checked)
                        {
                            //选中ASCII模式显示

                            sb.Append(Encoding.ASCII.GetString(received_buf));  //将整个数组解码为ASCII数组
                        }


                        try
                        {
                            //因为要访问UI资源，所以需要使用invoke方式同步ui
                            Invoke((EventHandler)(delegate
                            {
                                if (cb_checktime.Checked)
                                {
                                    current_time = System.DateTime.Now; //获取当前时间

                                    tb_serialreceive.AppendText("[" + current_time.ToString("HH:mm:ss") + "]" + "  " + sb.ToString() + "\r\n");

                                }
                                else
                                {
                                    //不显示时间
                                    if (rb_zhifu.Checked)
                                    {

                                    }
                                    else
                                        tb_serialreceive.AppendText(sb.ToString());


                                }
                                lb_rxnumber.Text = "Rx:" + receive_count.ToString() + "Bytes";
                            }
                              )
                            );
                            // 
                        }
                        catch (Exception ex)
                        {
                            //响铃并显示异常给用户
                            System.Media.SystemSounds.Beep.Play();
                            MessageBox.Show(ex.Message);

                        }
                    }
                    catch (Exception)
                    {

                        // throw;
                    }
                }
            }

        }

        #region DataInit
        private void DataInit()
        {

            try
            {
                DataTable DS = new DataTable("VCC");
                DataSet ds = new DataSet("SETING");
                doc.Load(configpath);

                //XmlElement SETING = doc.DocumentElement;
                DS.Columns.Add(new DataColumn("名称", typeof(string)));
                DS.Columns.Add(new DataColumn("电压设置(mV)", typeof(string)));
                DS.Columns.Add(new DataColumn("电压上限(mV)", typeof(string)));
                DS.Columns.Add(new DataColumn("电压下限(mV)", typeof(string)));
                DS.Columns.Add(new DataColumn("电流上限(mA)", typeof(string)));
                DS.Columns.Add(new DataColumn("电流下限(mA)", typeof(string)));
                XmlNode xn = doc.SelectSingleNode("SETING");
                XmlNodeList xnl = xn.ChildNodes;
                foreach (XmlNode xn_temp in xnl)
                {
                    //将节点转为元素，以便得到节点的属性
                    XmlElement xe = (XmlElement)xn_temp;
                    DataRow row = DS.NewRow();
                    row["名称"] = xe.ChildNodes.Item(0).InnerText;

                    row["电压设置(mV)"] = xe.ChildNodes.Item(1).InnerText;

                    row["电压上限(mV)"] = xe.ChildNodes.Item(2).InnerText;

                    row["电压下限(mV)"] = xe.ChildNodes.Item(3).InnerText;

                    row["电流上限(mA)"] = xe.ChildNodes.Item(4).InnerText;

                    row["电流下限(mA)"] = xe.ChildNodes.Item(5).InnerText;

                    DS.Rows.Add(row);
                }
                ds.Tables.Add(DS);
                //DS.WriteXml(@"./config.xml");
                dataGridView1.DataSource = ds;
                dataGridView1.DataMember = ds.Tables[0].TableName;
                dataGridView1.AllowUserToResizeColumns = false;
                dataGridView1.AllowUserToResizeRows = false;
                //隐藏第一列
                dataGridView1.RowHeadersVisible = false;
                //禁止用户添加行
                dataGridView1.AllowUserToAddRows = false;
                //关闭自动排序
                foreach (DataGridViewColumn column in dataGridView1.Columns)
                {
                    //设置自动排序
                    column.SortMode = DataGridViewColumnSortMode.NotSortable;
                }
                XmlDocument xml = new XmlDocument();
                xml.Load(pixpath);
                XmlNode ddd = xml.SelectSingleNode("DocumentElement");
                XmlNodeList ddaa = ddd.ChildNodes;

                tb_hbw.Text = ddaa.Item(0).ChildNodes.Item(0).InnerText;
                tb_hfw.Text = ddaa.Item(0).ChildNodes.Item(1).InnerText;
                tb_hact.Text = ddaa.Item(0).ChildNodes.Item(2).InnerText;
                tb_hsw.Text = ddaa.Item(0).ChildNodes.Item(3).InnerText;
                tb_vbw.Text = ddaa.Item(0).ChildNodes.Item(4).InnerText;
                tb_vfw.Text = ddaa.Item(0).ChildNodes.Item(5).InnerText;
                tb_vact.Text = ddaa.Item(0).ChildNodes.Item(6).InnerText;
                tb_vsw.Text = ddaa.Item(0).ChildNodes.Item(7).InnerText;

                tb_lcdname.Text = ddaa.Item(0).ChildNodes.Item(8).InnerText;
                tb_icname.Text = ddaa.Item(0).ChildNodes.Item(9).InnerText;
                tb_codezip.Text = ddaa.Item(0).ChildNodes.Item(10).InnerText;
                tb_pclk.Text = ddaa.Item(0).ChildNodes.Item(11).InnerText;
                cb_mipilan.Text = ddaa.Item(0).ChildNodes.Item(12).InnerText;
                cb_deset.Text = ddaa.Item(0).ChildNodes.Item(16).InnerText;
                cb_vsset.Text = ddaa.Item(0).ChildNodes.Item(17).InnerText;
                cb_hsset.Text = ddaa.Item(0).ChildNodes.Item(18).InnerText;
                cb_mipimode.Text = ddaa.Item(0).ChildNodes.Item(21).InnerText;
                cb_allmode.Text = ddaa.Item(0).ChildNodes.Item(15).InnerText;
                tb_locktime.Text = ddaa.Item(0).ChildNodes.Item(24).InnerText.ToString();
                cb_alarm.Checked = Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(25).InnerText);


                check_aenable.Checked = Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(13).InnerText);
                check_benable.Checked = Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(14).InnerText);
                check_mipiswap.Checked = Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(19).InnerText);
                check_odlr.Checked = Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(20).InnerText);
                check_dualport.Checked = Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(22).InnerText);
                tb_delay.Text = ddaa.Item(0).ChildNodes.Item(23).InnerText;

                XmlDocument xml1 = new XmlDocument();
                xml1.Load(piclistpath);
                XmlNode selectnode = xml1.SelectSingleNode("piclist");
                XmlNodeList piclist = selectnode.ChildNodes;
                int temp = lb_slect.SelectedIndex;
                lb_slect.Items.Clear();
                for (int i = 0; i < piclist.Count; i++)
                {
                    lb_slect.Items.Add(piclist.Item(i).InnerText);
                }
                lb_picnumcount.ForeColor = Color.Red;
                lb_picnumcount.Text = "画面总数:" + lb_slect.Items.Count.ToString();
                lb_slect.SelectedIndex = temp;
            }
            catch
            {

            }
        }

        #endregion

        #region DoloadParamter

       
        private void DoloadParamter()
        {
            #region pix data
            try
            {
                XmlDocument xml = new XmlDocument();
                xml.Load(pixpath);
                XmlNode ddd = xml.SelectSingleNode("DocumentElement");
                XmlNodeList ddaa = ddd.ChildNodes;
                XmlNodeList dislist = ddd.ChildNodes;
                #endregion

                doc.Load(configpath);
                XmlNode list = doc.SelectSingleNode("SETING");
                XmlNodeList alarm = list.ChildNodes;


                parent.pMIPItable = child;
                child.bLCDName = ddaa.Item(0).ChildNodes.Item(8).InnerText + "\n";
                child.bICName = ddaa.Item(0).ChildNodes.Item(9).InnerText + "\n";
                child.CodeZip = ddaa.Item(0).ChildNodes.Item(10).InnerText + "\n";
                child.DUAL_MIPI_LCD = Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(22).InnerText) == true) ? 1 : 0);
                child.DUAL_MIPI_CHANNEL_SWAP = Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(19).InnerText) == true) ? 1 : 0);
                child.ODD_EVEN_nLEFT_RIGHT = Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(20).InnerText) == true) ? 1 : 0);
                child.PCLK_Freq = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(11).InnerText);
                child.LANE_CNT = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(12).InnerText);
                child.V_DE = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(16).InnerText.Substring(0, 1));
                child.V_VS = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(17).InnerText.Substring(0, 1));
                child.V_HS = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(18).InnerText.Substring(0, 1));
                child.V_CLK = 0;
                child.Display_Mode = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(21).InnerText.Substring(0, 1));
                child.HACT_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(2).InnerText);
                child.VACT_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(6).InnerText);
                child.HFP_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(1).InnerText);
                child.HBP_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(0).InnerText);
                child.HSW_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(3).InnerText);
                child.VFP_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(5).InnerText);
                child.VBP_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(4).InnerText);
                child.VSW_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(7).InnerText);



                child.NomalVCC1SET = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(1).InnerText);
                child.LowperVCC1VOL = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(3).InnerText);
                child.UperVCC1VOL = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(2).InnerText);
                child.LowperVCC1MA = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(5).InnerText);
                child.UperVCC1MA = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(4).InnerText);


                child.NomalVCC2SET = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(1).InnerText);
                child.LowperVCC2VOL = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(3).InnerText);
                child.UperVCC2VOL = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(2).InnerText);
                child.LowperVCC2MA = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(5).InnerText);
                child.UperVCC2MA = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(4).InnerText);

                child.NomalVCC3SET = Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(1).InnerText);
                child.LowperVCC3VOL = Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(3).InnerText);
                child.UperVCC3VOL = Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(2).InnerText);
                child.LowperVCC3MA = Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(5).InnerText);
                child.UperVCC3MA = Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(4).InnerText);

                child.NomalVCC4SET = Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(1).InnerText);
                child.LowperVCC4VOL = Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(3).InnerText);
                child.UperVCC4VOL = Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(2).InnerText);
                child.LowperVCC4MA = Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(5).InnerText);
                child.UperVCC4MA = Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(4).InnerText);

                child.NomalVCC5SET = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(1).InnerText);
                child.LowperVCC5VOL = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(3).InnerText);
                child.UperVCC5VOL = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(2).InnerText);
                child.LowperVCC5MA = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(5).InnerText);
                child.UperVCC5MA = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(4).InnerText);

                child.NomalVCC6SET = Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(1).InnerText);
                child.LowperVCC6VOL = Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(3).InnerText);
                child.UperVCC6VOL = Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(2).InnerText);
                child.LowperVCC6MA = Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(5).InnerText);
                child.UperVCC6MA = Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(4).InnerText);

                child.NomalVSPSET = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(1).InnerText);
                child.LowperVSPVOL = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(3).InnerText);
                child.UperVSPVOL = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(2).InnerText);
                child.LowperVSPMA = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(5).InnerText);
                child.UperVSPMA = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(4).InnerText);

                child.NomalVSNSET = Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(1).InnerText);
                child.LowperVSNVOL = Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(3).InnerText);
                child.UperVSNVOL = Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(2).InnerText);
                child.LowperVSNMA = Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(5).InnerText);
                child.UperVSNMA = Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(4).InnerText);

                child.BLMASET= Convert.ToUInt16(alarm.Item(8).ChildNodes.Item(1).InnerText);
                child.LowperBLVOL= Convert.ToUInt16(alarm.Item(8).ChildNodes.Item(3).InnerText);
                child.UperBLVOL= Convert.ToUInt16(alarm.Item(8).ChildNodes.Item(2).InnerText);
                child.LowperBLMA= Convert.ToUInt16(alarm.Item(8).ChildNodes.Item(5).InnerText);
                child.UperBLMA= Convert.ToUInt16(alarm.Item(8).ChildNodes.Item(4).InnerText);
                child.NomalBLSET = 0;

                child.VCC1Time = Convert.ToUInt32(0x00200032);
                child.VCC2Time = Convert.ToUInt32(0x00200032);
                child.VCC3Time = Convert.ToUInt32(0x00200032);
                child.VCC4Time = Convert.ToUInt32(0x00200032);
                child.VCC5Time = Convert.ToUInt32(0x00200032);
                child.VCC6Time = Convert.ToUInt32(0x00200032);
                child.VSPTime = Convert.ToUInt32(0x00200032);
                child.VSNTime = Convert.ToUInt32(0x00200032);




                child.Low_Delay = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(23).InnerText);
                child.SIZE_OF_SHOW_MODE = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(15).InnerText);
                child.AlarmFlag = Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(25).InnerText) == true) ? 1 : 0);
                child.TimeLock = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(24).InnerText);
                child.Reserve1 = Convert.ToUInt16(100);
                child.Reserve2 = Convert.ToUInt16(100);
                child.Reserve3 = Convert.ToUInt16(100);
                child.Reserve4 = Convert.ToUInt16(100);
                child.Reserve5 = Convert.ToUInt16(100);
                child.MIPI_MODE = 0;
                child.DW1_EN = Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(13).InnerText) == true) ? 1 : 0);
                child.DW2_EN = Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(14).InnerText) == true) ? 1 : 0);

                child.Dismode = StructClass.Dismode;
                parent.flag = 0x01;
                cc.readinfo(Path.Combine(Application.StartupPath, "Module", "user_config.c"), child);

            }
            catch (Exception ex)
            {
                MessageBox.Show("生成user_config.c失败: " + ex.Message + "\n\n" + ex.StackTrace, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }


        }
        #endregion
        public static Color IntToColor(int rgb) => Color.FromArgb((int)byte.MaxValue, (int)(byte)(rgb >> 16), (int)(byte)(rgb >> 8), (int)(byte)rgb);

        #region InitSyntaxColoring
        private void InitSyntaxColoring()
        {
            this.scintilla1.StyleResetDefault();
            this.scintilla1.Styles[Style.Default].Font = "Consolas";
            this.scintilla1.Styles[Style.Default].Size = 10;
            this.scintilla1.Text = "";
            this.scintilla1.Styles[Style.Default].BackColor = IntToColor(0xFFFFFF);
            this.scintilla1.Styles[Style.Default].ForeColor = IntToColor(0x808080);
            this.scintilla1.StyleClearAll();

            this.scintilla1.Styles[Style.Cpp.Identifier].ForeColor = IntToColor(0x000000); //非关键字颜色
            this.scintilla1.Styles[Style.Cpp.Comment].ForeColor = IntToColor(0x40BF57);//块注释颜色
            this.scintilla1.Styles[Style.Cpp.CommentLine].ForeColor = IntToColor(0x40BF57); //行注释颜色
            this.scintilla1.Styles[Style.Cpp.CommentDoc].ForeColor = IntToColor(0x2FAE35);
            this.scintilla1.Styles[Style.Cpp.Number].ForeColor = IntToColor(0xF4580A);//数字颜色
            this.scintilla1.Styles[Style.Cpp.String].ForeColor = IntToColor(0xF24C0C);//字符颜色
            this.scintilla1.Styles[Style.Cpp.Character].ForeColor = IntToColor(0xE95454);
            this.scintilla1.Styles[Style.Cpp.Preprocessor].ForeColor = IntToColor(0xBB7043);//#include 颜色
            this.scintilla1.Styles[Style.Cpp.Operator].ForeColor = IntToColor(0x808080);
            this.scintilla1.Styles[Style.Cpp.Regex].ForeColor = IntToColor(0xff00ff);
            this.scintilla1.Styles[Style.Cpp.CommentLineDoc].ForeColor = IntToColor(0x77A7DB);
            this.scintilla1.Styles[Style.Cpp.Word].ForeColor = IntToColor(0xff);
            this.scintilla1.Styles[Style.Cpp.Word2].ForeColor = IntToColor(0x7F41BD);
            this.scintilla1.Styles[Style.Cpp.CommentDocKeyword].ForeColor = IntToColor(0xB3D991);
            this.scintilla1.Styles[Style.Cpp.CommentDocKeywordError].ForeColor = IntToColor(0xFF0000);
            this.scintilla1.Styles[Style.Cpp.GlobalClass].ForeColor = IntToColor(0x48A8EE);
            this.scintilla1.Lexer = Lexer.Cpp;
            this.scintilla1.CaretLineBackColor = IntToColor(0xFF0000);
            this.scintilla1.SetSelectionForeColor(true, IntToColor(0x808080));
            this.scintilla1.SetSelectionBackColor(true, IntToColor(0xa0a0a0));
            ContextMenu contextMenu = this.scintilla1.ContextMenu;
            //this.scintilla1.SetKeywords(0, "main  bsp_DelayMS spi3w_write spi4w_write spi9b_write qspi_write spi3w_read spi9b_read qspi_read ssd28_rst lcm_reset tp_reset mcu_read mcu8b_write mcu16b_write set_vcc set_iovcc set_vspvol set_vsnvol set_eniovcc set_envcc set_envsp set_envsn Ssd2828ON O_LCD_RESET O_SSD2828_RESET  GPU_BL KeyUp_Process ");
            this.scintilla1.SetKeywords(0, " static switch case else if while break default do for return sizeof goto continue enum struct union typedef int");//蓝色函数名
            this.scintilla1.SetKeywords(1, " void char uint8_t uint16_t uint32_t const extern  unsigned volatile long  int "); //绿色函数名

            this.scintilla2.StyleResetDefault();
            this.scintilla2.Styles[Style.Default].Font = "Consolas";
            this.scintilla2.Styles[Style.Default].Size = 10;
            this.scintilla2.Text = "";
            this.scintilla2.Styles[Style.Default].BackColor = IntToColor(0xFFFFFF);
            this.scintilla2.Styles[Style.Default].ForeColor = IntToColor(0x808080);
            this.scintilla2.StyleClearAll();

            this.scintilla2.Styles[Style.Cpp.Identifier].ForeColor = IntToColor(0x000000); //非关键字颜色
            this.scintilla2.Styles[Style.Cpp.Comment].ForeColor = IntToColor(0x40BF57);//块注释颜色
            this.scintilla2.Styles[Style.Cpp.CommentLine].ForeColor = IntToColor(0x40BF57); //行注释颜色
            this.scintilla2.Styles[Style.Cpp.CommentDoc].ForeColor = IntToColor(0x2FAE35);
            this.scintilla2.Styles[Style.Cpp.Number].ForeColor = IntToColor(0xF4580A);//数字颜色
            this.scintilla2.Styles[Style.Cpp.String].ForeColor = IntToColor(0xF24C0C);//字符颜色
            this.scintilla2.Styles[Style.Cpp.Character].ForeColor = IntToColor(0xE95454);
            this.scintilla2.Styles[Style.Cpp.Preprocessor].ForeColor = IntToColor(0xBB7043);//#include 颜色
            this.scintilla2.Styles[Style.Cpp.Operator].ForeColor = IntToColor(0x808080);
            this.scintilla2.Styles[Style.Cpp.Regex].ForeColor = IntToColor(0xff00ff);
            this.scintilla2.Styles[Style.Cpp.CommentLineDoc].ForeColor = IntToColor(0x77A7DB);
            this.scintilla2.Styles[Style.Cpp.Word].ForeColor = IntToColor(0xff);
            this.scintilla2.Styles[Style.Cpp.Word2].ForeColor = IntToColor(0x7F41BD);
            this.scintilla2.Styles[Style.Cpp.CommentDocKeyword].ForeColor = IntToColor(0xB3D991);
            this.scintilla2.Styles[Style.Cpp.CommentDocKeywordError].ForeColor = IntToColor(0xFF0000);
            this.scintilla2.Styles[Style.Cpp.GlobalClass].ForeColor = IntToColor(0x48A8EE);
            this.scintilla2.Lexer = Lexer.Cpp;
            this.scintilla2.CaretLineBackColor = IntToColor(0xFF0000);
            this.scintilla2.SetSelectionForeColor(true, IntToColor(0x808080));
            this.scintilla2.SetSelectionBackColor(true, IntToColor(0xa0a0a0));
            ContextMenu contextMenu1 = this.scintilla2.ContextMenu;
            //this.scintilla1.SetKeywords(0, "main  bsp_DelayMS spi3w_write spi4w_write spi9b_write qspi_write spi3w_read spi9b_read qspi_read ssd28_rst lcm_reset tp_reset mcu_read mcu8b_write mcu16b_write set_vcc set_iovcc set_vspvol set_vsnvol set_eniovcc set_envcc set_envsp set_envsn Ssd2828ON O_LCD_RESET O_SSD2828_RESET  GPU_BL KeyUp_Process ");
            this.scintilla2.SetKeywords(0, " static   switch case else if while break default do for return sizeof goto continue enum struct union volatile typedef short signed unsigned");//蓝色函数名
            this.scintilla2.SetKeywords(1, " void char uint8_t uint16_t uint32_t const extern int   "); //绿色函数名

        }


        #endregion
        private const int NUMBER_MARGIN = 1;
        private const int NUMBER_MARGIN1 = 1;
        #region InitHotkeys
        private void InitHotkeys()
        {
            HotKeyManager.AddHotKey(this, OpenSearch, Keys.F, true);
            HotKeyManager.AddHotKey(this, OpenFindDialog, Keys.F, true, false, true);
            HotKeyManager.AddHotKey(this, OpenReplaceDialog, Keys.R, true);
            HotKeyManager.AddHotKey(this, OpenReplaceDialog, Keys.H, true);
            HotKeyManager.AddHotKey(this, Uppercase, Keys.U, true);
            HotKeyManager.AddHotKey(this, Lowercase, Keys.L, true);
            HotKeyManager.AddHotKey(this, ZoomIn, Keys.Oemplus, true);
            HotKeyManager.AddHotKey(this, ZoomOut, Keys.OemMinus, true);
            HotKeyManager.AddHotKey(this, ZoomDefault, Keys.D0, true);
            HotKeyManager.AddHotKey(this, CloseSearch, Keys.Escape);
            // remove conflicting hotkeys from scintilla
            scintilla1.ClearCmdKey(Keys.Control | Keys.F);
            scintilla1.ClearCmdKey(Keys.Control | Keys.R);
            scintilla1.ClearCmdKey(Keys.Control | Keys.H);
            scintilla1.ClearCmdKey(Keys.Control | Keys.L);
            scintilla1.ClearCmdKey(Keys.Control | Keys.U);

            HotKeyManager.AddHotKey(this, OpenSearch1, Keys.F, true);
            HotKeyManager.AddHotKey(this, OpenFindDialog1, Keys.F, true, false, true);
            HotKeyManager.AddHotKey(this, OpenReplaceDialog1, Keys.R, true);
            HotKeyManager.AddHotKey(this, OpenReplaceDialog1, Keys.H, true);
            HotKeyManager.AddHotKey(this, Uppercase1, Keys.U, true);
            HotKeyManager.AddHotKey(this, Lowercase1, Keys.L, true);
            HotKeyManager.AddHotKey(this, ZoomIn1, Keys.Oemplus, true);
            HotKeyManager.AddHotKey(this, ZoomOut1, Keys.OemMinus, true);
            HotKeyManager.AddHotKey(this, ZoomDefault1, Keys.D0, true);
            HotKeyManager.AddHotKey(this, CloseSearch1, Keys.Escape);
            // remove conflicting hotkeys from scintilla
            scintilla2.ClearCmdKey(Keys.Control | Keys.F);
            scintilla2.ClearCmdKey(Keys.Control | Keys.R);
            scintilla2.ClearCmdKey(Keys.Control | Keys.H);
            scintilla2.ClearCmdKey(Keys.Control | Keys.L);
            scintilla2.ClearCmdKey(Keys.Control | Keys.U);
        }
        #endregion
        #region  scintillalabaot
        private void Lowercase()
        {
            int selectionStart = this.scintilla1.SelectionStart;
            int selectionEnd = this.scintilla1.SelectionEnd;
            this.scintilla1.ReplaceSelection(this.scintilla1.GetTextRange(selectionStart, selectionEnd - selectionStart).ToLower());
            this.scintilla1.SetSelection(selectionStart, selectionEnd);
        }
        private void Lowercase1()
        {
            int selectionStart = this.scintilla2.SelectionStart;
            int selectionEnd = this.scintilla2.SelectionEnd;
            this.scintilla2.ReplaceSelection(this.scintilla2.GetTextRange(selectionStart, selectionEnd - selectionStart).ToLower());
            this.scintilla2.SetSelection(selectionStart, selectionEnd);
        }
        // Token: 0x060000DC RID: 220 RVA: 0x0000FCFC File Offset: 0x0000DEFC
        private void Uppercase()
        {
            int selectionStart = this.scintilla1.SelectionStart;
            int selectionEnd = this.scintilla1.SelectionEnd;
            this.scintilla1.ReplaceSelection(this.scintilla1.GetTextRange(selectionStart, selectionEnd - selectionStart).ToUpper());
            this.scintilla1.SetSelection(selectionStart, selectionEnd);
        }
        private void Uppercase1()
        {
            int selectionStart = this.scintilla2.SelectionStart;
            int selectionEnd = this.scintilla2.SelectionEnd;
            this.scintilla2.ReplaceSelection(this.scintilla2.GetTextRange(selectionStart, selectionEnd - selectionStart).ToUpper());
            this.scintilla2.SetSelection(selectionStart, selectionEnd);
        }
        // Token: 0x060000DD RID: 221 RVA: 0x0000F3EF File Offset: 0x0000D5EF
        private void OpenFindDialog()
        {
            // this.MyFindReplace.ShowFind();
        }
        private void OpenFindDialog1()
        {
            // this.MyFindReplace.ShowFind();
        }
        // Token: 0x060000DE RID: 222 RVA: 0x0000FD50 File Offset: 0x0000DF50
        private void OpenReplaceDialog()
        {
            //this.MyFindReplace.ShowReplace();
        }
        private void OpenReplaceDialog1()
        {
            //this.MyFindReplace.ShowReplace();
        }
        // Token: 0x060000DF RID: 223 RVA: 0x0000FD5F File Offset: 0x0000DF5F
        private void ZoomIn()
        {
            this.scintilla1.ZoomIn();
        }
        private void ZoomIn1()
        {
            this.scintilla2.ZoomIn();
        }
        // Token: 0x060000E0 RID: 224 RVA: 0x0000FD6E File Offset: 0x0000DF6E
        private void ZoomOut()
        {
            this.scintilla1.ZoomOut();
        }
        private void ZoomOut1()
        {
            this.scintilla2.ZoomOut();
        }
        // Token: 0x060000E1 RID: 225 RVA: 0x0000FD7D File Offset: 0x0000DF7D
        private void ZoomDefault()
        {
            this.scintilla1.Zoom = 0;
        }
        private void ZoomDefault1()
        {
            this.scintilla2.Zoom = 0;
        }
        private void InitNumberMargin()
        {

            scintilla1.Styles[Style.LineNumber].BackColor = Color.FromArgb(0xffffff); ;
            scintilla1.Styles[Style.LineNumber].ForeColor = IntToColor(0xff0000);
            scintilla1.Styles[Style.IndentGuide].ForeColor = IntToColor(0x0);
            scintilla1.Styles[Style.IndentGuide].BackColor = IntToColor(0xffff00);

            var nums = scintilla1.Margins[NUMBER_MARGIN];
            nums.Width = 30;
            nums.Type = MarginType.Number;
            nums.Sensitive = true;
            nums.Mask = 0;

            scintilla1.MarginClick += TextArea_MarginClick;
        }
        private void InitNumberMargin2()
        {

            scintilla2.Styles[Style.LineNumber].BackColor = Color.FromArgb(0xffffff); ;
            scintilla2.Styles[Style.LineNumber].ForeColor = IntToColor(0xff0000);
            scintilla2.Styles[Style.IndentGuide].ForeColor = IntToColor(0x0);
            scintilla2.Styles[Style.IndentGuide].BackColor = IntToColor(0xffff00);

            var nums = scintilla2.Margins[NUMBER_MARGIN1];
            nums.Width = 30;
            nums.Type = MarginType.Number;
            nums.Sensitive = true;
            nums.Mask = 0;

            scintilla2.MarginClick += TextArea_MarginClick2;
        }
        public void InvokeIfNeeded(Action action)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(action);
            }
            else
            {
                action.Invoke();
            }
        }
        /// <summary>
        /// 
        /// 
        /// </summary>
        bool SearchIsOpen = false;
        public void OpenSearch()
        {

            SearchManager.SearchBox = TxtSearch;
            SearchManager.TextArea = scintilla1;

            if (!SearchIsOpen)
            {
                SearchIsOpen = true;
                InvokeIfNeeded(delegate ()
                {
                    PanelSearch.Visible = true;
                    TxtSearch.Text = SearchManager.LastSearch;
                    TxtSearch.Focus();
                    TxtSearch.SelectAll();
                });
            }
            else
            {
                InvokeIfNeeded(delegate ()
                {
                    TxtSearch.Focus();
                    TxtSearch.SelectAll();
                });
            }
        }
        bool SearchIsOpen1 = false;
        public void OpenSearch1()
        {

            SearchManager.SearchBox = TxtSearch1;
            SearchManager.TextArea = scintilla2;

            if (!SearchIsOpen1)
            {
                SearchIsOpen1 = true;
                InvokeIfNeeded(delegate ()
                {
                    PanelSearch1.Visible = true;
                    TxtSearch1.Text = SearchManager.LastSearch;
                    TxtSearch1.Focus();
                    TxtSearch1.SelectAll();
                });
            }
            else
            {
                InvokeIfNeeded(delegate ()
                {
                    TxtSearch1.Focus();
                    TxtSearch1.SelectAll();
                });
            }
        }

        private void CloseSearch()
        {
            if (SearchIsOpen)
            {
                SearchIsOpen = false;
                InvokeIfNeeded(delegate ()
                {
                    PanelSearch.Visible = false;
                    //CurBrowser.GetBrowser().StopFinding(true);
                });
            }
        }
        private void CloseSearch1()
        {
            if (SearchIsOpen1)
            {
                SearchIsOpen1 = false;
                InvokeIfNeeded(delegate ()
                {
                    PanelSearch1.Visible = false;
                    //CurBrowser.GetBrowser().StopFinding(true);
                });
            }
        }

        private const int BOOKMARK_MARGIN = 2;
        private const int BOOKMARK_MARKER = 2;
        private void TextArea_MarginClick(object sender, MarginClickEventArgs e)
        {
            if (e.Margin == BOOKMARK_MARGIN)
            {
                // Do we have a marker for this line?
                const uint mask = (1 << BOOKMARK_MARKER);
                var line = scintilla1.Lines[scintilla1.LineFromPosition(e.Position)];
                if ((line.MarkerGet() & mask) > 0)
                {
                    // Remove existing bookmark
                    line.MarkerDelete(BOOKMARK_MARKER);
                }
                else
                {
                    // Add bookmark
                    line.MarkerAdd(BOOKMARK_MARKER);
                }
            }
        }
        private const int BOOKMARK_MARGIN1 = 2;
        private const int BOOKMARK_MARKER1 = 2;
        private void TextArea_MarginClick2(object sender, MarginClickEventArgs e)
        {
            if (e.Margin == BOOKMARK_MARGIN1)
            {
                // Do we have a marker for this line?
                const uint mask = (1 << BOOKMARK_MARKER1);
                var line = scintilla2.Lines[scintilla2.LineFromPosition(e.Position)];
                if ((line.MarkerGet() & mask) > 0)
                {
                    // Remove existing bookmark
                    line.MarkerDelete(BOOKMARK_MARKER1);
                }
                else
                {
                    // Add bookmark
                    line.MarkerAdd(BOOKMARK_MARKER1);
                }
            }
        }
        private void InitBookmarkMargin()
        {

            //TextArea.SetFoldMarginColor(true, IntToColor(BACK_COLOR));

            var margin = scintilla1.Margins[BOOKMARK_MARGIN];
            margin.Width = 10;
            margin.Sensitive = true;
            margin.Type = MarginType.Symbol;
            margin.Mask = (1 << BOOKMARK_MARKER);
            //margin.Cursor = MarginCursor.Arrow;

            var marker = scintilla1.Markers[BOOKMARK_MARKER];
            marker.Symbol = MarkerSymbol.Circle;
            marker.SetBackColor(IntToColor(0xFF003B));
            marker.SetForeColor(IntToColor(0x000000));
            marker.SetAlpha(100);

        }

        private void InitBookmarkMargin1()
        {

            //TextArea.SetFoldMarginColor(true, IntToColor(BACK_COLOR));

            var margin = scintilla2.Margins[BOOKMARK_MARGIN];
            margin.Width = 10;
            margin.Sensitive = true;
            margin.Type = MarginType.Symbol;
            margin.Mask = (1 << BOOKMARK_MARKER);
            //margin.Cursor = MarginCursor.Arrow;

            var marker = scintilla2.Markers[BOOKMARK_MARKER];
            marker.Symbol = MarkerSymbol.Circle;
            marker.SetBackColor(IntToColor(0xFF003B));
            marker.SetForeColor(IntToColor(0x000000));
            marker.SetAlpha(100);

        }      /// <summary>
               /// 文件拖拽
               /// 
               /// </summary>
        public void InitDragDropFile()
        {

            scintilla1.AllowDrop = true;
            scintilla1.DragEnter += delegate (object sender, DragEventArgs e)
            {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                    e.Effect = DragDropEffects.Copy;
                else
                    e.Effect = DragDropEffects.None;
            };
            scintilla1.DragDrop += delegate (object sender, DragEventArgs e)
            {

                // get file drop
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                {

                    Array a = (Array)e.Data.GetData(DataFormats.FileDrop);
                    if (a != null)
                    {

                        string path = a.GetValue(0).ToString();

                        LoadDataFromFile(path);

                    }
                }
            };

        }
        public void InitDragDropFile1()
        {

            scintilla2.AllowDrop = true;
            scintilla2.DragEnter += delegate (object sender, DragEventArgs e)
            {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                    e.Effect = DragDropEffects.Copy;
                else
                    e.Effect = DragDropEffects.None;
            };
            scintilla2.DragDrop += delegate (object sender, DragEventArgs e)
            {

                // get file drop
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                {

                    Array a = (Array)e.Data.GetData(DataFormats.FileDrop);
                    if (a != null)
                    {

                        string path = a.GetValue(0).ToString();

                        LoadDataFromFile(path);

                    }
                }
            };

        }
        private void LoadDataFromFile(string path)
        {
            if (File.Exists(path))
            {
                string fileDir = Environment.CurrentDirectory;
               // this.Text = "CX900_Tools   " + fileDir + "\\" + Path.GetFileName(path);
                scintilla1.Text = File.ReadAllText(path);
            }
        }

        /// <summary>
        /// 校验.CXKJ文件格式
        /// </summary>
        /// <param name="filePath">文件路径</param>
        /// <returns>是否为有效的.CXKJ文件</returns>
        private bool ValidateCXKJFile(string filePath)
        {
            try
            {
                // 检查文件是否存在
                if (!File.Exists(filePath))
                {
                    return false;
                }

                // 检查文件扩展名
                if (!filePath.EndsWith(".CXKJ", StringComparison.OrdinalIgnoreCase))
                {
                    return false;
                }

                // 检查文件是否为有效的ZIP文件（.CXKJ本质上是ZIP压缩文件）
                using (FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read))
                {
                    byte[] header = new byte[4];
                    int bytesRead = fs.Read(header, 0, 4);

                    // 确保读取了4个字节
                    if (bytesRead < 4)
                    {
                        return false;
                    }

                    // ZIP文件的魔数：PK\x03\x04 或 PK\x05\x06
                    if (header[0] != 0x50 || header[1] != 0x4B)
                    {
                        return false;
                    }
                }

                // 检查文件中是否包含必要的文件
                List<string> requiredFiles = new List<string>
                {
                    "config.xml",
                    "pix_config.xml",
                    "lcd_cfg.c",
                    "power_task.c",
                    "pic_list.xml",
                    "libGD32F303VET6.a"
                };

                using (ZipInputStream zipStream = new ZipInputStream(File.OpenRead(filePath)))
                {
                    ZipEntry entry;
                    List<string> foundFiles = new List<string>();

                    while ((entry = zipStream.GetNextEntry()) != null)
                    {
                        string fileName = Path.GetFileName(entry.Name);
                        foundFiles.Add(fileName);
                    }

                    // 检查所有必需的文件是否存在
                    foreach (string requiredFile in requiredFiles)
                    {
                        if (!foundFiles.Contains(requiredFile))
                        {
                            Debug.WriteLine($"缺少必需文件: {requiredFile}");
                            return false;
                        }
                    }
                }

                return true;
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"校验文件失败: {ex.Message}");
                return false;
            }
        }

        /// <summary>
        /// 加载.CXKJ项目文件
        /// </summary>
        /// <param name="filePath">文件路径</param>
        private void LoadCXKJFile(string filePath)
        {
            if (!File.Exists(filePath))
            {
                MessageBox.Show($"文件不存在: {filePath}", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // 校验文件格式
            if (!ValidateCXKJFile(filePath))
            {
                MessageBox.Show($"文件格式不正确！\n\n该文件不是有效的.CXKJ工程文件。\n\n请选择正确的工程文件。", "文件格式错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string appDirectory = Application.StartupPath;
            string backupDir = Path.Combine(appDirectory, "backup_" + DateTime.Now.Ticks);

            // 旧文件路径
            string oldConfigPath = Path.Combine(appDirectory, "config.xml");
            string oldPixPath = Path.Combine(appDirectory, "pix_config.xml");
            string oldCodePath = Path.Combine(appDirectory, "Module", "lcd_cfg.c");
            string oldPublicPath = Path.Combine(appDirectory, "Module", "power_task.c");
            string oldPicListPath = Path.Combine(appDirectory, "pic_list.xml");

            // 备份文件路径
            string backupConfigPath = Path.Combine(backupDir, "config.xml");
            string backupPixPath = Path.Combine(backupDir, "pix_config.xml");
            string backupCodePath = Path.Combine(backupDir, "lcd_cfg.c");
            string backupPublicPath = Path.Combine(backupDir, "power_task.c");
            string backupPicListPath = Path.Combine(backupDir, "pic_list.xml");

            try
            {
                // 更新窗口标题显示当前打开的文件
                this.Text = "CX900_Tools     [程序路径: " + appDirectory + "]     " + filePath;

                // 创建备份目录
                Directory.CreateDirectory(backupDir);

                // 备份旧文件
                try
                {
                    if (File.Exists(oldConfigPath))
                        File.Copy(oldConfigPath, backupConfigPath, true);
                    if (File.Exists(oldPixPath))
                        File.Copy(oldPixPath, backupPixPath, true);
                    if (File.Exists(oldCodePath))
                        File.Copy(oldCodePath, backupCodePath, true);
                    if (File.Exists(oldPublicPath))
                        File.Copy(oldPublicPath, backupPublicPath, true);
                    if (File.Exists(oldPicListPath))
                        File.Copy(oldPicListPath, backupPicListPath, true);
                }
                catch (Exception ex)
                {
                    Debug.WriteLine($"备份旧文件失败: {ex.Message}");
                }

                // 删除旧配置文件，确保使用最新版本
                try
                {
                    if (File.Exists(oldConfigPath))
                        File.Delete(oldConfigPath);
                    if (File.Exists(oldPixPath))
                        File.Delete(oldPixPath);
                    if (File.Exists(oldCodePath))
                        File.Delete(oldCodePath);
                    if (File.Exists(oldPublicPath))
                        File.Delete(oldPublicPath);
                    if (File.Exists(oldPicListPath))
                        File.Delete(oldPicListPath);
                }
                catch (Exception ex)
                {
                    Debug.WriteLine($"删除旧文件失败: {ex.Message}");
                }

                // 解压.CXKJ文件到程序所在目录（而不是文件所在目录）
                SharpZip.UnpackFiles(filePath, appDirectory);

                // 重新初始化数据
                DataInit();

                // 重新加载参数
                DoloadParamter();

                // 重新加载代码文件
                LoadDataFromFile(codepath);

                // 重新加载公共代码
                LoadPublicCode(publiccodepath);

                // 刷新界面显示
                this.Refresh();

                Debug.WriteLine($"成功加载文件: {filePath}");
            }
            catch (Exception ex)
            {
                MessageBox.Show($"加载文件失败: {ex.Message}\n\n正在恢复之前的配置...", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);

                // 恢复备份的旧文件
                try
                {
                    if (File.Exists(backupConfigPath) && !File.Exists(oldConfigPath))
                        File.Copy(backupConfigPath, oldConfigPath, true);
                    if (File.Exists(backupPixPath) && !File.Exists(oldPixPath))
                        File.Copy(backupPixPath, oldPixPath, true);
                    if (File.Exists(backupCodePath) && !File.Exists(oldCodePath))
                        File.Copy(backupCodePath, oldCodePath, true);
                    if (File.Exists(backupPublicPath) && !File.Exists(oldPublicPath))
                        File.Copy(backupPublicPath, oldPublicPath, true);
                    if (File.Exists(backupPicListPath) && !File.Exists(oldPicListPath))
                        File.Copy(backupPicListPath, oldPicListPath, true);

                    // 重新加载旧数据
                    DataInit();
                    DoloadParamter();
                    LoadDataFromFile(codepath);
                    LoadPublicCode(publiccodepath);

                    this.Refresh();

                    MessageBox.Show("已恢复到之前的配置", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception restoreEx)
                {
                    Debug.WriteLine($"恢复备份失败: {restoreEx.Message}");
                }

                try
                {
                    Directory.Delete(backupDir, true);
                }
                catch { }
            }
            finally
            {
                // 清理备份目录
                try
                {
                    if (Directory.Exists(backupDir))
                        Directory.Delete(backupDir, true);
                }
                catch (Exception ex)
                {
                    Debug.WriteLine($"删除备份目录失败: {ex.Message}");
                }
            }
        }



        private void LoadPublicCode(string path)
        {
            if (File.Exists(path))
            {
                string fileDir = Environment.CurrentDirectory;
                // this.Text = "CX900_Tools   " + fileDir + "\\" + Path.GetFileName(path);
                scintilla2.Text = File.ReadAllText(path);
            }
        }
        #endregion
        public static OpenFileDialog openfile = new OpenFileDialog();

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void 打开文件ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog prjfilepath = new OpenFileDialog();
            prjfilepath.Filter = "CXKJ|*.CXKJ";
            if (prjfilepath.ShowDialog() == DialogResult.OK)
            {
                // 校验文件格式
                if (!ValidateCXKJFile(prjfilepath.FileName))
                {
                    MessageBox.Show($"文件格式不正确！\n\n该文件不是有效的.CXKJ工程文件。\n\n请注意版本!", "文件格式错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                string appDirectory = Application.StartupPath;
                string backupDir = Path.Combine(appDirectory, "backup_" + DateTime.Now.Ticks);

                // 旧文件路径
                string oldConfigPath = Path.Combine(appDirectory, "config.xml");
                string oldPixPath = Path.Combine(appDirectory, "pix_config.xml");
                string oldCodePath = Path.Combine(appDirectory, "Module", "lcd_cfg.c");
                string oldPublicPath = Path.Combine(appDirectory, "Module", "power_task.c");

                // 备份文件路径
                string backupConfigPath = Path.Combine(backupDir, "config.xml");
                string backupPixPath = Path.Combine(backupDir, "pix_config.xml");
                string backupCodePath = Path.Combine(backupDir, "lcd_cfg.c");
                string backupPublicPath = Path.Combine(backupDir, "power_task.c");

                try
                {
                    // 创建备份目录
                    Directory.CreateDirectory(backupDir);

                    // 备份旧文件
                    try
                    {
                        if (File.Exists(oldConfigPath))
                            File.Copy(oldConfigPath, backupConfigPath, true);
                        if (File.Exists(oldPixPath))
                            File.Copy(oldPixPath, backupPixPath, true);
                        if (File.Exists(oldCodePath))
                            File.Copy(oldCodePath, backupCodePath, true);
                        if (File.Exists(oldPublicPath))
                            File.Copy(oldPublicPath, backupPublicPath, true);
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine($"备份旧文件失败: {ex.Message}");
                    }

                    // 删除旧配置文件，确保使用最新版本
                    try
                    {
                        if (File.Exists(oldConfigPath))
                            File.Delete(oldConfigPath);
                        if (File.Exists(oldPixPath))
                            File.Delete(oldPixPath);
                        if (File.Exists(oldCodePath))
                            File.Delete(oldCodePath);
                        if (File.Exists(oldPublicPath))
                            File.Delete(oldPublicPath);
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine($"删除旧文件失败: {ex.Message}");
                    }

                    // 解压.CXKJ文件到程序所在目录（而不是文件所在目录）
                    SharpZip.UnpackFiles(prjfilepath.FileName, appDirectory);

                    this.Text = "CX900_Tools     [程序路径: " + appDirectory + "]     " + prjfilepath.FileName;

                    DataInit();
                    DoloadParamter();
                    LoadDataFromFile(codepath);
                    LoadPublicCode(publiccodepath);

                    // 刷新界面显示
                    this.Refresh();

                    // 删除备份目录
                    try
                    {
                        Directory.Delete(backupDir, true);
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine($"删除备份目录失败: {ex.Message}");
                    }

                    openfile.Dispose();
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"打开工程失败: {ex.Message}\n\n正在恢复之前的配置...", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);

                    // 恢复备份的旧文件
                    try
                    {
                        if (File.Exists(backupConfigPath) && !File.Exists(oldConfigPath))
                            File.Copy(backupConfigPath, oldConfigPath, true);
                        if (File.Exists(backupPixPath) && !File.Exists(oldPixPath))
                            File.Copy(backupPixPath, oldPixPath, true);
                        if (File.Exists(backupCodePath) && !File.Exists(oldCodePath))
                            File.Copy(backupCodePath, oldCodePath, true);
                        if (File.Exists(backupPublicPath) && !File.Exists(oldPublicPath))
                            File.Copy(backupPublicPath, oldPublicPath, true);

                        // 重新加载旧数据
                        DataInit();
                        DoloadParamter();
                        LoadDataFromFile(codepath);
                        LoadPublicCode(publiccodepath);

                        this.Refresh();

                        MessageBox.Show("已恢复到之前的配置", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    catch (Exception restoreEx)
                    {
                        Debug.WriteLine($"恢复备份失败: {restoreEx.Message}");
                    }

                    try
                    {
                        Directory.Delete(backupDir, true);
                    }
                    catch { }

                    openfile.Dispose();
                }
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            // 记录初始窗体大小,用于后续按比例缩放
            _initialFormWidth = this.ClientSize.Width;
            _initialFormHeight = this.ClientSize.Height;

            // 注册.CXKJ文件关联
            try
            {
                FileAssociationManager.RegisterFileAssociation();
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"注册文件关联失败: {ex.Message}");
            }

            // 设置所有相对路径为基于程序目录的绝对路径
            string appDirectory = Application.StartupPath;
            configpath = Path.Combine(appDirectory, "config.xml");
            pixpath = Path.Combine(appDirectory, "pix_config.xml");
            codepath = Path.Combine(appDirectory, "Module", "lcd_cfg.c");
            piclistpath = Path.Combine(appDirectory, "pic_list.xml");
            APPPath = Path.Combine(appDirectory, "build", "GD32F303VET6.bin");
            Userfilepath = Path.Combine(appDirectory, "Module", "app.c");
            userfiledemopath = Path.Combine(appDirectory, "appdemo");
            publiccodepath = Path.Combine(appDirectory, "Module", "power_task.c");
            moduledirpath = Path.Combine(appDirectory, "Module");
            libpath = Path.Combine(appDirectory, "libGD32F303VET6.a");

            // 显示程序路径在窗口标题
            this.Text =" CX900_Tools "     + appDirectory+"/cx900_tools.exe   " + Userfilepath;

            CloseSearch();
            Thread thcheckserial = new Thread(checkserial);
            thcheckserial.IsBackground = true;
            thcheckserial.Start();

            Thread threadpic = new Thread(picturset);
            threadpic.IsBackground = true;
            threadpic.Start();

            // 如果有双击打开的文件,加载该文件
            if (!string.IsNullOrEmpty(FileToOpen))
            {
                // 延迟加载,确保窗体完全初始化
                this.BeginInvoke(new Action(() =>
                {
                    LoadCXKJFile(FileToOpen);
                }));
            }
        }

        // 记录初始窗体大小
        private float _initialFormWidth;
        private float _initialFormHeight;

        // 窗体大小改变事件处理
        private void MainForm_Resize(object sender, EventArgs e)
        {
            // 防止在最小化时处理
            if (this.WindowState == FormWindowState.Minimized)
                return;

            // 调整 splitContainer1 的分割器距离,保持合理的比例
            try
            {
                if (splitContainer1 != null)
                {
                    // 设置分割器距离为窗体宽度的 67%
                    int newSplitterDistance = (int)(this.ClientSize.Width * 0.67);
                    // 确保分割器距离在合理范围内
                    newSplitterDistance = Math.Max(400, Math.Min(newSplitterDistance, this.ClientSize.Width - 400));
                    splitContainer1.SplitterDistance = newSplitterDistance;
                }
            }
            catch (Exception ex)
            {
                // 忽略调整过程中的错误
                System.Diagnostics.Debug.WriteLine($"调整分割器位置时出错: {ex.Message}");
            }

            // 更新初始尺寸为当前尺寸,避免累积缩放
            _initialFormWidth = this.ClientSize.Width;
            _initialFormHeight = this.ClientSize.Height;
        }

        public bool picthreacontrl = false;
        public bool pic2threacontrl = false;
        public Color colortemp = new Color();
        public Color colortemp1 = new Color();

        #region  画面编辑用线程
        /// <summary>
        /// 画面编辑用线程
        /// </summary>
        private void picturset()
        {
            while (true)
            {
                if (color_picker1?.DialogResult == DialogResult.OK)
                {
                    if (picthreacontrl)
                    {
                        this?.BeginInvoke((EventHandler)(delegate
                        {
                            
                            switch (lb_list.SelectedItem)
                            {

                                case "Color":
                                    lb_colorset.BackColor = color_picker1.Color;
                                    color_picker1.Dispose();
                                    picthreacontrl = false;
                                    break;
                                case "BlackWight":
                                    lb_kuancolor.BackColor = color_picker1.Color;
                                    color_picker1.Dispose();
                                    picthreacontrl = false;
                                    break;
                                case "Flicker":
                                    if (color_picker1 != null)
                                    {
                                        lb_fkcolor1.BackColor = color_picker1.Color;
                                        color_picker1.Dispose();
                                        picthreacontrl = false;
                                    }
                                    break;
                                case "GradientCol":
                                    lb_grcolcolor.BackColor = color_picker1.Color;
                                    color_picker1.Dispose();
                                    picthreacontrl = false;
                                    break;
                                case "GradientRow":
                                    lb_grrowcolor.BackColor = color_picker1.Color;
                                    color_picker1.Dispose();
                                    picthreacontrl = false;
                                    break;
                                case "CrossTalk":
                                    lb_crosskuancolor.BackColor = color_picker1.Color;
                                    color_picker1.Dispose();
                                    picthreacontrl = false;
                                    break;
                                default: break;
                            }
                        }));
                    }
                }
                if (color_picker2?.DialogResult == DialogResult.OK)
                {
                    if (pic2threacontrl)
                    {
                        this?.BeginInvoke((EventHandler)(delegate
                        {
                            switch (lb_list.SelectedItem)
                            {
                                case "BlackWight":

                                    if (color_picker2 != null)
                                    {
                                        colortemp1 = color_picker2.Color;
                                        lb_backcolor.BackColor = colortemp1;
                                        color_picker2.Dispose();
                                        pic2threacontrl = false;
                                    }


                                    break;
                                case "Flicker":

                                    if (color_picker2 != null)
                                    {
                                        lb_fkcolor2.BackColor = color_picker2.Color;
                                        color_picker2.Dispose();
                                        pic2threacontrl = false;
                                    }
                                    break;

                                case "CrossTalk":
                                    if (color_picker2 != null)
                                    {
                                        lb_crossbackcolor.BackColor = color_picker2.Color;
                                        color_picker2.Dispose();
                                        pic2threacontrl = false;
                                    }
                                    break;
                                default: break;
                            }

                            
                        }));
                    }
                }

                 
        Thread.Sleep(100);

            }

        }
        #endregion
        public string prjpath = @"./Template.rar";


        #region 保存功能
        private void 保存ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bt_saveconfig_Click_1(sender, e);
            DirectoryInfo prjdir = Directory.CreateDirectory(@"./prj");
            SaveFileDialog save = new SaveFileDialog();
            save.Title = "保存工程";
            save.Filter = "CXKJ|*.CXKJ";// 默认的文件格式
            save.InitialDirectory = @"./prj";// AppDomain.CurrentDomain.BaseDirectory; // 默认的保存路径
            save.FileName = "CX_" + tb_lcdname.Text+"_"+ tb_icname.Text;
            if (save.FileName != string.Empty)
            {

                save.ShowDialog();
                string path = save.FileName;
                string.Format(@"./prj", path);
                if (!File.Exists(path)) // 判断文件是否存在，不存在就保存，存在就提示
                {
                   
                   // DeleteDirectory(@"./Template");
                    DirectoryInfo dd = Directory.CreateDirectory(@"./Template");

                    File.Copy(publiccodepath, @"./Template/pic_list.xml",true);
                    File.Copy(configpath, @"./Template/config.xml", true);
                    File.Copy(pixpath, @"./Template/pix_config.xml", true);
                    File.Copy(libpath, @"./Template/libGD32F303VET6.a", true);
                    CopyDirectory(moduledirpath, @".\Template\Module");

                   


                    File.Delete(path);
                    SharpZip.PackFiles(path, @"./Template");
                }
                else
                {
                  File.Delete(path);
                    //DeleteDirectory(@"./Template");
                    DirectoryInfo dd = Directory.CreateDirectory(@"./Template");
                    
                    foreach (var item in dd.GetFiles())
                  {
                      File.Delete(item.FullName);
                  }
                  
                    File.Copy(configpath, @"./Template/config.xml");
                    File.Copy(pixpath, @"./Template/pix_config.xml");
                    File.Copy(piclistpath, @"./Template/pic_list.xml");
                    File.Copy(libpath, @"./Template/libGD32F303VET6.a");
                    CopyDirectory(moduledirpath,@".\Template\Module");
                    File.Delete(path);
                  SharpZip.PackFiles(path, @"./Template");

                }

            }




        }
        public static void DeleteDirectory(string targetDir)
        {
            string[] files = Directory.GetFiles(targetDir);
            string[] dirs = Directory.GetDirectories(targetDir);

            foreach (string file in files)
            {
                File.SetAttributes(file, FileAttributes.Normal);
                File.Delete(file);
            }

            foreach (string dir in dirs)
            {
                DeleteDirectory(dir);
            }

            Directory.Delete(targetDir, true);
        }
        public static void CopyDirectory(string sourceDir, string targetDir)
        {
            DirectoryInfo dir = new DirectoryInfo(sourceDir);
            DirectoryInfo[] dirs = dir.GetDirectories();

            // If the source directory does not exist, throw an exception.
            if (!dir.Exists)
            {
                throw new DirectoryNotFoundException($"Source directory does not exist or could not be found: {sourceDir}");
            }

            // If the destination directory does not exist, create it.
            if (!Directory.Exists(targetDir))
            {
                Directory.CreateDirectory(targetDir);
            }

            // Get the files in the directory and copy them to the new location.
            FileInfo[] files = dir.GetFiles();
            foreach (FileInfo file in files)
            {
                string tempPath = Path.Combine(targetDir, file.Name);
                file.CopyTo(tempPath, true);
            }

            // If copying subdirectories, copy them and their contents to the new location.
            foreach (DirectoryInfo subdir in dirs)
            {
                string tempPath = Path.Combine(targetDir, subdir.Name);
                CopyDirectory(subdir.FullName, tempPath);
            }
        }
        #endregion
        private void textBox8_TextChanged(object sender, EventArgs e)
        {

        }

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void splitContainer3_Panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }


        #region bt_saveconfig_Click_1
        private void bt_saveconfig_Click_1(object sender, EventArgs e)
        {
            try
            {

        
            DataSet TT1 = (DataSet)dataGridView1.DataSource;
            
            DataTable dataSet = new DataTable("pix");
            dataSet.Columns.Add(new DataColumn("HBW", typeof(string)));
            dataSet.Columns.Add(new DataColumn("HFW", typeof(string)));
            dataSet.Columns.Add(new DataColumn("HACT", typeof(string)));
            dataSet.Columns.Add(new DataColumn("HSW", typeof(string)));
            dataSet.Columns.Add(new DataColumn("VBW", typeof(string)));
            dataSet.Columns.Add(new DataColumn("VFW", typeof(string)));
            dataSet.Columns.Add(new DataColumn("VACT", typeof(string)));
            dataSet.Columns.Add(new DataColumn("VSW", typeof(string)));

            dataSet.Columns.Add(new DataColumn("LCDNAME", typeof(string)));
            dataSet.Columns.Add(new DataColumn("ICNAME", typeof(string)));
            dataSet.Columns.Add(new DataColumn("CODEZIP", typeof(string)));
            dataSet.Columns.Add(new DataColumn("PCLK", typeof(string)));
            dataSet.Columns.Add(new DataColumn("MIPILAN", typeof(string)));
            dataSet.Columns.Add(new DataColumn("AENABLE", typeof(string)));
            dataSet.Columns.Add(new DataColumn("BENABLE", typeof(string)));
            dataSet.Columns.Add(new DataColumn("ALLMODE", typeof(string)));
            dataSet.Columns.Add(new DataColumn("DESET", typeof(string)));
            dataSet.Columns.Add(new DataColumn("VSSET", typeof(string)));
            dataSet.Columns.Add(new DataColumn("HSSET", typeof(string)));
            dataSet.Columns.Add(new DataColumn("MIPISWAP", typeof(string)));
            dataSet.Columns.Add(new DataColumn("ODLR", typeof(string)));
            dataSet.Columns.Add(new DataColumn("MIPIMODE", typeof(string)));
            dataSet.Columns.Add(new DataColumn("DUALPORT", typeof(string)));
            dataSet.Columns.Add(new DataColumn("DELAY", typeof(string)));
            dataSet.Columns.Add(new DataColumn("TimeLock", typeof(string)));
            dataSet.Columns.Add(new DataColumn("AlarmFlag", typeof(string)));
                DataRow row = dataSet.NewRow();
            row["HBW"] = tb_hbw.Text.ToString();
            row["HFW"] = tb_hfw.Text.ToString();
            row["HACT"] = tb_hact.Text.ToString();
            row["HSW"] = tb_hsw.Text.ToString();
            row["VBW"] = tb_vbw.Text.ToString();
            row["VFW"] = tb_vfw.Text.ToString();
            row["VACT"] = tb_vact.Text.ToString();
            row["VSW"] = tb_vsw.Text.ToString();

            row["LCDNAME"] = tb_lcdname.Text.ToString();
            row["ICNAME"] = tb_icname.Text.ToString();
            row["CODEZIP"] = tb_codezip.Text.ToString();
            row["PCLK"] = tb_pclk.Text.ToString();
            row["MIPILAN"] = cb_mipilan.Text.ToString();
            row["AENABLE"] = check_aenable.Checked.ToString();
            row["BENABLE"] = check_benable.Checked.ToString();
            row["ALLMODE"] =  lb_slect.Items.Count ;
            row["DESET"] = cb_deset.Text.ToString();
            row["VSSET"] = cb_vsset.Text.ToString();
            row["HSSET"] = cb_hsset.Text.ToString();
            row["MIPISWAP"] = check_mipiswap.Checked.ToString();
            row["ODLR"] = check_odlr.Checked.ToString();
            row["MIPIMODE"] = cb_mipimode.Text.ToString();
            row["DUALPORT"] = check_dualport.Checked.ToString();
            row["DELAY"] = tb_delay.Text.ToString();
            row["TimeLock"] = tb_locktime.Text.ToString();
            row["AlarmFlag"] = cb_alarm.Checked.ToString();
                dataSet.Rows.Add(row);
            DataTable dislistdataset = new DataTable("dislist");
            dataSet.WriteXml(pixpath);
            TT1.WriteXml(configpath);
            File.WriteAllText(codepath, scintilla1.Text);
            File.WriteAllText(publiccodepath, scintilla2.Text);

                if (lb_slect.Items.Count >= 0)
                {
                    for (int i = 0; i < lb_slect.Items.Count; i++)
                    {
                        LB_list.Add(lb_slect.Items[i].ToString());

                    }
                }
                else;
                cb_allmode.Refresh();
               
                DoloadParamter();
                Writexml(piclistpath, LB_list);
            }
            catch (Exception)
            {

                throw;
            }
        }


        private void Writexml(string path,List<string> str)
        {
            if (str == null)
            {
                return;
            }
            else
            {

                XmlDocument doc = new XmlDocument();
                XmlDeclaration dec = doc.CreateXmlDeclaration("1.0", "utf-8", null);
                doc.AppendChild(dec);
                // <root>
                XmlElement root = doc.CreateElement("piclist");
                doc.AppendChild(root);
                // <root>/<user>/<username>
                for (int i = 0; i < str.Count; i++)
                {
                    XmlElement user = doc.CreateElement("图片"+i);
                    user.InnerText = str[i];
                    root.AppendChild(user);



                }
                str.Clear();
                doc.Save(path);
                dislistcompile();
            }
        }
        #endregion
        private void pictureBox2_Click(object sender, EventArgs e)
        {
            OpenSearch();
            SearchManager.Find(false, true);
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            OpenSearch();
            SearchManager.Find(true, false);
        }

        private void pictureBox4_Click(object sender, EventArgs e)
        {
            OpenSearch();
            SearchManager.Find(false, false);
            CloseSearch();
        }
        #region compile
        private void 编译ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bt_building_Click(sender, e);
        }
        private List<string> codeStrs = new List<string>();
     



       
        #endregion

        
        private void 下载APPToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bootiapflag = false;
            DL_form form1 = new DL_form(cb_serialprot .Text);
            form1.mydel += new DL_form.mydelegate(download);
            form1.ShowDialog();


        }

        private void download( string path)
        {
            if (!serialHelper.serial.IsOpen)
            {

                MessageBox.Show("串口没有打开", "提示");
                return;
            }
            serialHelper.serial.WriteLine("power off" + "\r\n");
            if (bootiapflag == false)
            {
                serialHelper.serial.WriteLine("updata iap" + "\r\n");
            }
            else
            {
                serialHelper.serial.WriteLine("updata boot" + "\r\n");
            }
            serialHelper.serial.Close();
            bt_openserial.BackColor = Color.Red;
            bt_openserial.Text = "打开串口";
        }

        private void tb_vfw_TextChanged(object sender, EventArgs e)
        {

        }
        
        private void bt_pwon_Click(object sender, EventArgs e)
        {

            try
            {
                if (!serialHelper.serial.IsOpen)
                {
                    MessageBox.Show("串口没有打开", "提示");
                    return;
                }
                serialHelper.serial.WriteLine("power on" + "\r\n");
            }
            catch (Exception)
            {

                //  throw;
            }
        }

        private void bt_pwoff_Click(object sender, EventArgs e)
        {
            try
            {

                try
                {
                    if (!serialHelper.serial.IsOpen)
                    {
                        MessageBox.Show("串口没有打开", "提示");
                        return;
                    }
                    serialHelper.serial.WriteLine("power off" + "\r\n");
                }
                catch (Exception)
                {

                    //  throw;
                }

            }
            catch (Exception)
            {

                // throw;
            }
        }
        
        private void button1_Click_1(object sender, EventArgs e)
        {

            try
            {
               
                if (!serialHelper.serial.IsOpen)
                {
                    serialHelper.Open();
                    serialHelper.serial.Close();
                    serialHelper.serial.PortName = cb_serialprot.Text;
                    serialHelper.serial.Open();
                    bt_openserial.Text = "关闭串口";
                    bt_openserial.BackColor = Color.Green;
                    serialHelper.serial.DataReceived += new SerialDataReceivedEventHandler(_dataReceive);
                   
                }
                else
                {
                    bt_openserial.Text = "打开串口";
                    serialHelper.serial.Close();
                    connectflag = false;
                    bt_openserial.BackColor = Color.Red;
                }
            }
            catch (Exception)
            {
                MessageBox.Show("此串口拒绝访问");
                //throw;
            }

        }

        private void bt_up_Click(object sender, EventArgs e)
        {
            try
            {
                try
                {
                    serialHelper.serial.WriteLine("turn up" + "\r\n");
                }
                catch (Exception)
                {

                    //  throw;
                }
            }
            catch (Exception)
            {

                throw;
            }
           
        }

        private void bt_down_Click(object sender, EventArgs e)
        {
            try
            {
                if (!serialHelper.serial.IsOpen)
                {
                    MessageBox.Show("串口没有打开","提示");
                    return;
                }
                serialHelper.serial.WriteLine("turn down" + "\r\n");
            }
            catch (Exception)
            {

                throw;
            }
            
        }

        private void bt_auto_Click(object sender, EventArgs e)
        {
            try
            {
                if (!serialHelper.serial.IsOpen)
                {
                    MessageBox.Show("串口没有打开", "提示");
                    return;
                }
                serialHelper.serial.WriteLine("turn auto" + "\r\n");
            }
            catch (Exception)
            {

                throw;
            }
        }

        private void 连接设备ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if (!serialHelper.serial.IsOpen)
                {

                    serialHelper.serial.PortName = cb_serialprot.Text;
                    serialHelper.serial.Open();
                    bt_openserial.Text = "关闭串口";
                    bt_openserial.BackColor = Color.Green;
                }
                else
                {
                    bt_openserial.Text = "打开串口";
                    serialHelper.serial.Close();
                    bt_openserial.BackColor = Color.Red;
                }
            }
            catch (Exception)
            {
                //serialHelper.serial.Close();
                MessageBox.Show("此串口拒绝访问");
                throw;
            }
        }

        private void 断开设备ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                bt_openserial.Text = "打开串口";
                serialHelper.serial.Close();
                bt_openserial.BackColor = Color.Red;
            }
            catch (Exception)
            {

                throw;
            }

        }
        const byte C = 67;
        private void 下载配置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bt_downloadapp_Click(sender, e);

        }


        private static ManualResetEvent posReceiveDone = new ManualResetEvent(false);


        public  void YmodeDownLoad(string path)
        {
            ymodem = new Ymodem.Ymodem();
            ymodem.serialPort = serialHelper.serial;          
            ymodem.Path = path; 
            ymodem.PortName = serialHelper.serial.PortName;
            ymodem.BaudRate = serialHelper.Baudrate;
            
            this.Invoke(new Action(() =>
            {
                downloadThread = new System.Threading.Thread(ymodem.YmodemUploadFile);
                ymodem.NowDownloadProgressEvent += new EventHandler(NowDownloadProgressEvent);
                ymodem.DownloadResultEvent += new EventHandler(DownloadFinishEvent);
                downloadThread.Start();
            }));
            //downloadThread = new Thread(delegate () { ymodem.YmodemUploadFile(); }); downloadThread.Start();
            

        }

     
        public void bt_downloadapp_Click(object sender, EventArgs e)
        {

            try
            {
                serialHelper.serial.DataReceived -= _dataReceive;
                long length = new System.IO.FileInfo(APPPath).Length;
                if (length > 0x70000|| length<0)
                {
                    MessageBox.Show("APP文件超出范围", "提示");
                    return;
                }

                if (!serialHelper.serial.IsOpen)
                {
                    
                    MessageBox.Show("串口没有打开","提示");
                    return;
                }
                if (!File.Exists(APPPath))
                {
                    MessageBox.Show("文件不存在");
                    return;
                }
                progressBar1.Visible = true;
                lb_downloaddis.ForeColor = Color.Black;
                lb_downloaddis.Text = "正在下载";
                bt_downloadapp.Enabled = false;
                bt_downloadapp.Refresh();
                serialHelper.serial.WriteLine("power off" + "\r\n");
                Thread.Sleep(500);
                serialHelper.serial.WriteLine("updata app" + "\r\n");
                Thread.Sleep(1000);

                YmodeDownLoad(APPPath);
                


            }
            catch (Exception)
            {

                //MessageBox.Show("没有打开串口","提示");
            }
        }
        private delegate void DownloadFinish(bool finish);
        private void DownloadFinishEvent(object sender, EventArgs e)
        {
            // 下载完成，sender 是 Ymodem 对象，无法转换为 Boolean
            // 根据实际情况判断是否成功，这里假设成功
            bool finish = true;
            DownloadFinish status = new DownloadFinish(UploadFileResult);
            this.Invoke(status, finish);
        }

        private void UploadFileResult(bool result)
        {
            if (result == true)
            {
               // MessageBox.Show("下载成功");
               
                this.progressBar1.Value = 0;
                serialHelper.Portname = cb_serialprot.Text;
                serialHelper.Baudrate = 460800;
                serialHelper.serial.DataReceived += new SerialDataReceivedEventHandler(_dataReceive);
                progressBar1.Visible = false;
                lb_downloaddis.ForeColor = Color.Green;
                lb_downloaddis.Text = "下载成功";
                connectflag = false;
            }
            else
            {
                lb_downloaddis.ForeColor = Color.Red;
                lb_downloaddis.Text = "下载失败";

                this.progressBar1.Value = 0;
                progressBar1.Visible = false;
                connectflag = false;
            }
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
            progressBar1.Value = count;
        }
        private byte[] GetFilelenToByet(string path)
        {
            byte[] temp = new byte[4];
            byte[] f = File.ReadAllBytes(path);
            UInt32 len = (UInt32)f.Length;
            temp[0] = Convert.ToByte(len >> 24 & 0xff);
            temp[1] = Convert.ToByte(len >> 16 & 0xff);
            temp[2] = Convert.ToByte(len >> 8 & 0xff);
            temp[3] = Convert.ToByte(len & 0xff);
            return temp;
        }

        private void sendapp()
        {
            serialHelper.SendFile(APPPath);
        }

        private void 新建工程ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            File.Delete(configpath);
            File.Delete(pixpath);
            File.Delete(codepath);
            File.Delete(piclistpath);
            SharpZip.UnpackFiles(@"./Template.zip", @"./");
            DataInit();
            DoloadParamter();
            LoadDataFromFile(codepath);
            openfile.Dispose();
        }

        private void 另存为ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bt_saveconfig_Click_1(sender, e);
            DirectoryInfo prjdir = Directory.CreateDirectory(@"./prj");
            SaveFileDialog save = new SaveFileDialog();
            save.Title = "保存工程";
            save.Filter = "CXKJ|*.CXKJ";// 默认的文件格式
            save.InitialDirectory = @"./prj";// AppDomain.CurrentDomain.BaseDirectory; // 默认的保存路径
            save.FileName = "CX_" + tb_lcdname.Text + "_" + tb_icname.Text;
            if (save.FileName != string.Empty)
            {

                save.ShowDialog();
                string path = save.FileName;
                string.Format(@"./prj", path);
                if (!File.Exists(path)) // 判断文件是否存在，不存在就保存，存在就提示
                {

                    // DeleteDirectory(@"./Template");
                    DirectoryInfo dd = Directory.CreateDirectory(@"./Template");

                    File.Copy(publiccodepath, @"./Template/pic_list.xml", true);
                    File.Copy(configpath, @"./Template/config.xml", true);
                    File.Copy(pixpath, @"./Template/pix_config.xml", true);
                    File.Copy(libpath, @"./Template/libGD32F303VET6.a", true);
                    CopyDirectory(moduledirpath, @".\Template\Module");




                    File.Delete(path);
                    SharpZip.PackFiles(path, @"./Template");
                }
                else
                {
                    File.Delete(path);
                    //DeleteDirectory(@"./Template");
                    DirectoryInfo dd = Directory.CreateDirectory(@"./Template");

                    foreach (var item in dd.GetFiles())
                    {
                        File.Delete(item.FullName);
                    }

                    File.Copy(configpath, @"./Template/config.xml");
                    File.Copy(pixpath, @"./Template/pix_config.xml");
                    File.Copy(piclistpath, @"./Template/pic_list.xml");
                    File.Copy(libpath, @"./Template/libGD32F303VET6.a");
                    CopyDirectory(moduledirpath, @".\Template\Module");
                    File.Delete(path);
                    SharpZip.PackFiles(path, @"./Template");

                }

            }
        }

        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            ColorPickerDialog colorPickerDialog = new ColorPickerDialog();
            colorPickerDialog.Show();
        }
        // public ColorPickerDialog colorPickerDialog;
       
        private void textBox1_Click(object sender, EventArgs e)
        {

        }


        #region  添加画面按钮
        private void button1_Click_2(object sender, EventArgs e)
        {
            string temp = "";
            if (lb_slect.Items.Count >50-1)
            {
                MessageBox.Show("超出最大画面数20张");
                return;
            }
            switch (lb_list.SelectedItem)
            {
                case "Color":
                    temp = "Color(" + "0x" +Convert.ToString( (UInt32)lb_colorset.BackColor.ToArgb(),16)+")";
                    lb_slect.Items.Add(temp);
                    break;

                case "BlackWight":
                    temp = "BlackWight(0x" + Convert.ToString((UInt32)lb_kuancolor.BackColor.ToArgb(), 16) + ",0x" + Convert.ToString((UInt32)lb_backcolor.BackColor.ToArgb(), 16) + ")";
                    lb_slect.Items.Add(temp);
                    break;

                case "ColorBarRow":
                    temp = "ColorBarRow(" + tb_input1.Text.ToString() + ")";
                    lb_slect.Items.Add(temp);
                    break;
                case "ColorBarCol":
                    temp = "ColorBarCol(" + tb_input2.Text.ToString() + ")";
                    lb_slect.Items.Add(temp);
                    break;
                case "Flicker":
                    temp = "Flicker(0x" + Convert.ToString((UInt32)lb_fkcolor1.BackColor.ToArgb(), 16) + ",0x" + Convert.ToString((UInt32)lb_fkcolor2.BackColor.ToArgb(), 16) + ")";
                    lb_slect.Items.Add(temp);
                    break;
                case "Picture":
                    temp = "Picture(" + tb_input3.Text.ToString() + ")";
                    lb_slect.Items.Add(temp);
                    break;
                case "GradientCol":                    
                    temp = "GradientCol(0x" + Convert.ToString((UInt32)lb_grcolcolor.BackColor.ToArgb(), 16) + "," + tb_input4.Text + ")";
                    lb_slect.Items.Add(temp);
                    break;
                case "GradientRow":
                    
                    temp = "GradientRow(0x" + Convert.ToString((UInt32)lb_grrowcolor.BackColor.ToArgb(), 16) + "," + tb_input5.Text + ")";
                    lb_slect.Items.Add(temp);
                    break;
                case "Checkerboard":
                    temp = "Checkerboard(" + tb_input6.Text + ")";
                    lb_slect.Items.Add(temp);
                    break;
                case "CrossTalk":
                    
                    temp = "CrossTalk(0x" + Convert.ToString((UInt32)lb_crossbackcolor.BackColor.ToArgb(), 16) + ",0x" + Convert.ToString((UInt32)lb_crosskuancolor.BackColor.ToArgb(), 16) + ")";
                    lb_slect.Items.Add(temp);
                    break;
                case "TpTest":
                    temp = "TpTest(" + ")";
                    lb_slect.Items.Add(temp);
                    break;
                default:
                    gb_imgset.Controls.Clear();
                    break;
            }
            lb_slect.SelectedIndex = lb_slect.Items.Count - 1;
            bt_saveconfig_Click_1(sender, e);
            DataInit();
        }

        #endregion



        #region lb_list_Click
        private void lb_list_Click(object sender, EventArgs e)
        {

        }

        #endregion
        /// <summary>
        /// 判断是不为数字
        /// </summary>
        /// <param name="numstr"></param>
        /// <returns></returns>
        private bool isNumber(string numstr)
        {
            try
            {
                Convert.ToInt32(numstr);
                return true;
            }
            catch (Exception)
            {
                try
                {
                    Convert.ToInt32(numstr, 16);
                    return numstr.Contains("0x");
                }
                catch
                {
                    try
                    {
                        Convert.ToDouble(numstr);
                        return true;
                    }
                    catch
                    {
                        // Console.WriteLine(ex.StackTrace);
                        return false;
                    }
                }
            }
        }

        /// <summary>
        /// 解析用户要显示的列表
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
   /*     public DisModule[] JXdislist(List<string> str)
        {
            DisModule[] disModules = new DisModule[20];
            int count = str.Count;
            for (int i = 0; i < count; i++)
            {
                int length2 = str[i].IndexOf('(');
                string oldValue = str[i].ToString().Substring(0, length2);
                string[] strArray = str[i].ToString().Replace(oldValue, "").Replace("(", "").Replace(")", "").Split(',');

                switch (oldValue)
                {
                    case "Color":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.PURECOLOR;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = 0;
                        }
                        break;
                    case "BlackWight":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.BLACKWIGHT;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = strArray[1].Contains("0x") ? Convert.ToUInt32(strArray[1], 16) : Convert.ToUInt32(strArray[1]);
                        }
                        break;
                    case "ColorBarCol":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.BARCOL;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = 0;
                        }
                        break;
                    case "ColorBarRow":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.BARROW;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = 0;
                        }
                        break;
                    case "GradientCol":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.GRADIentCol;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = strArray[1].Contains("0x") ? Convert.ToUInt32(strArray[1], 16) : Convert.ToUInt32(strArray[1]);
                        }
                        break;
                    case "GradientRow":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.GradientRow;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = strArray[1].Contains("0x") ? Convert.ToUInt32(strArray[1], 16) : Convert.ToUInt32(strArray[1]);
                        }
                        break;
                    case "Flicker":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.FLINKER;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = strArray[1].Contains("0x") ? Convert.ToUInt32(strArray[1], 16) : Convert.ToUInt32(strArray[1]);
                        }
                        break;
                    case "Picture":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.DISBMP;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = 0;
                        }
                        break;
                    case "Checkerboard":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.CHECKerboard;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = 0;
                        }
                        break;
                    case "CrossTalk":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.CROSS;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = strArray[1].Contains("0x") ? Convert.ToUInt32(strArray[1], 16) : Convert.ToUInt32(strArray[1]);
                        }
                        break;
                    case "TpTest":
                        disModules[i].FuncName = (UInt32)FuncNameEnum.FuncName.DISBMP;
                        if (!isNumber(strArray[0]))
                        {
                            break;
                        }
                        else
                        {
                            disModules[i].Parameter1 = strArray[0].Contains("0x") ? Convert.ToUInt32(strArray[0], 16) : Convert.ToUInt32(strArray[0]);
                            disModules[i].Parameter2 = 0;
                        }
                        break;
                    default: break;
                }
            }
            return disModules;
        }
   */
        #region  显示列表编译
        /// <summary>
        /// 
        /// </summary>
        private void dislistcompile()
        {
       
            List<string> temp = new List<string>();
            int count = lb_slect.Items.Count;
            for (int i = 0; i < count; i++)
            {
                temp.Add(lb_slect.Items[i].ToString());
            }
            FileStream fs = new FileStream(Userfilepath, FileMode.Create);
            StreamWriter sw = new StreamWriter(fs);
            sw.WriteLine("#include\"user_config.h\"");
            sw.WriteLine("#include \"delay.h\"");
            sw.WriteLine("#include \"GPU_Cfg.h\"");
            sw.WriteLine("#include \"GPU_PIC.h\"");
            sw.WriteLine("#include \"GPU_Show.h\"");
            sw.WriteLine("#include \"usartfifo.h\"");
            sw.WriteLine("#include \"timer.h\"");
            sw.WriteLine("#include \"mytext.h\"");
            sw.WriteLine("#include \"mytext.h\"");
            sw.WriteLine("extern uint8_t P0_SampleValue;");
            sw.Write("extern uint8_t KeyPowerPressed;\r\n"+
                "extern uint8_t KeyUpPressed;\r\n" +
                "extern uint8_t KeyDownPressed;\r\n" +
                "extern uint8_t ShowMode;\r\n" +
                "void Init_IO(void)\r\n" + "{\r\n" +
                "init_spi();\r\n" +
                "}\r\n" +
                "/**********************************************************************************************************\r\n"+
                "*     函 数 名: Lcd_ShowMode\r\n" +
                "*     功能说明:\r\n" +
                "*     形    参: --\r\n" +
                "*     返 回 值:\r\n" +
                "*     日期	 :2022-10-08\r\n" +
                "*********************************************************************************************************\r\n" +
                "*/ \r\n"



                );
            FileStream fd = new FileStream(userfiledemopath, FileMode.Open);
            StreamReader rd = new StreamReader(fd);
            string rdfile = rd.ReadToEnd();
            sw.Write(rdfile);
            rd.Dispose();
            rd.Close();
            fd.Close();



            sw.Write("\nvoid Lcd_ShowMode(uint8_t ShowId) " + "\n" +
                "{" + "\n" +
               "    uint16_t Width, Hight;" + "\n" +
               "    uint8_t temp[64];" + "\n" +
               "    char path[30];" + "\n" );
            sw.Write("  switch (ShowId)" + "\n" +
            "   {" + "\n");
            for (int i = 0; i < temp.Count; i++)
            {
                sw.Write("case " + i + ":" + "\n" +
                    "   " + "   " + temp[i] + ";" + "\n" + " break;" + "\n"
                    );

            }
            sw.Write("\n" +
                " default:break; " + "\n" +
               "}" + "\n"
                + "}");
            sw.Write("\r\n");
            sw.Flush();
            sw.Dispose();
            sw.Close();
            fs.Close();

        }

        #endregion

        #region 显示图片列表框解析
        private void lb_slect_SelectedIndexChanged(object sender, EventArgs e)
        {
            Color temp, temp1;
            try
            {
                if (lb_slect.SelectedItem == null)
                {
                    return;
                }
            int length2 = lb_slect.SelectedItem.ToString().IndexOf('(');
            string oldValue = lb_slect.SelectedItem.ToString().Substring(0, length2);
            string[] strArray = lb_slect.SelectedItem.ToString().Replace(oldValue, "").Replace("(", "").Replace(")", "").Split(',');
            switch (oldValue)
            {
                case "Color":
                    temp = ColorTranslator.FromHtml("#" + strArray[0].Replace("0x", ""));
                    pb_photo.Image = MakeImage.makeColorImg(temp, 256, 448); break;
                case "BlackWight":
                    temp = ColorTranslator.FromHtml("#" + strArray[0].Replace("0x", ""));
                    temp1 = ColorTranslator.FromHtml("#" + strArray[1].Replace("0x", ""));
                    pb_photo.Image = MakeImage.makeFrameImg(temp, temp1, 256, 448);
                    break;
                case "ColorBarRow":
                    int number3 = Convert.ToUInt16(strArray[0]);
                    pb_photo.Image = MakeImage.MakeColorBarRow(number3, 256, 448);
                    break;
                case "ColorBarCol":

                    int number4 = Convert.ToUInt16(strArray[0]);
                    pb_photo.Image = MakeImage.MakeColorBarCol(number4, 256, 448); break;
                case "Flicker":
                    temp = ColorTranslator.FromHtml("#" + strArray[0].Replace("0x", ""));
                    temp1 = ColorTranslator.FromHtml("#" + strArray[1].Replace("0x", ""));
                    pb_photo.Image = MakeImage.makeLineFlicerImg(temp, temp1, 256, 448);
                    break;
                case "Picture":
                    int number1 = Convert.ToUInt16(strArray[0]);
                    Font f = new Font("Arial", 20, FontStyle.Bold);
                    Bitmap bitmap = MakeImage.TextToBitmap("F" + number1.ToString("00") + ".BMP", f, Rectangle.Empty, Color.Red, Color.White);
                    pb_photo.Image = bitmap; 
                    break;
                case "GradientCol":
                    temp = ColorTranslator.FromHtml("#" + strArray[0].Replace("0x", ""));
                    int number5 = Convert.ToUInt16(strArray[1]);
                    pb_photo.Image = MakeImage.MakeGradCol(temp, number5);
                    break;
                case "GradientRow":
                    temp = ColorTranslator.FromHtml("#" + strArray[0].Replace("0x", ""));
                    int number6 = Convert.ToUInt16(strArray[1]);
                    pb_photo.Image = MakeImage.MakeGradRow(temp, number6);
                    break;
                case "Checkerboard":
                    int numbe7 = Convert.ToUInt16(strArray[0]);
                    pb_photo.Image = MakeImage.makeWBImg(numbe7, numbe7, Color.White, Color.Black, 256, 448);
                    break;
                case "CrossTalk":
                    temp = ColorTranslator.FromHtml("#" + strArray[0].Replace("0x", ""));
                    temp1 = ColorTranslator.FromHtml("#" + strArray[1].Replace("0x", ""));
                    pb_photo.Image = MakeImage.makeCrossTalkImg(temp, temp1, 256, 448);
                    break;
                    case "TpTest":
                        Font f1 = new Font("Arial", 20, FontStyle.Bold);
                        Bitmap bitmap1 = MakeImage.TextToBitmap("TP TEST", f1, Rectangle.Empty, Color.Red, Color.White);
                        pb_photo.Image = bitmap1;
                        break;
                    default: break;
            }
               
                
            }
            catch (Exception)
            {

                //throw;
            }
        }
       
        private void lb_list_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (lb_list.SelectedItem)
            {
                case "Color":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "Color Seting";
                    Label lbcolorsettital = new Label();
                    lbcolorsettital.Location = new Point(15, 35);
                    lbcolorsettital.Text = "Color:";
                    lbcolorsettital.Visible = true;
                    lbcolorsettital.Width = 60;
                    lbcolorsettital.Height = 20;
                    lb_colorset.Location = new Point(60, 30);
                    lb_colorset.Text = "";
                    lb_colorset.BorderStyle = BorderStyle.FixedSingle;
                    lb_colorset.Width = 60;
                    lb_colorset.Height = 20;
                    lb_colorset.Visible = true;
                    lb_colorset.Enabled = true;
                    lb_colorset.Click += Lb_color_Click;
                    gb_imgset.Controls.Add(lb_colorset);
                    gb_imgset.Controls.Add(lbcolorsettital);
                    gb_imgset.BackColor= Color.FromArgb(0xff, 0xff, 0xff);
                    pb_photo.Image = MakeImage.makeColorImg(lb_colorset.BackColor, 256, 448);
                    break;

                case "BlackWight":

                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "BlackWight Seting";
                    Label titlekuang = new Label();
                    titlekuang.Location = new Point(15, 35);
                    titlekuang.Text = "四边颜色:";
                    titlekuang.Width = 60;
                    titlekuang.Height = 20;
                    titlekuang.Visible = true;
                    gb_imgset.Controls.Add(titlekuang);
                    lb_kuancolor.Location = new Point(75, 30);
                    lb_kuancolor.Text = "";
                    lb_kuancolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_kuancolor.Width = 60;
                    lb_kuancolor.Height = 20;
                    lb_kuancolor.BackColor = Color.FromArgb(0xff, 0xff, 0xff);
                    lb_kuancolor.Visible = true;
                    lb_kuancolor.Enabled = true;
                    lb_kuancolor.Click += Lb_color_Click;
                    gb_imgset.Controls.Add(lb_kuancolor);

                    Label titlebackcolor = new Label();
                    titlebackcolor.Location = new Point(170, 35);
                    titlebackcolor.Text = "中间颜色:";
                    titlebackcolor.Width = 60;
                    titlebackcolor.Height = 20;
                    titlebackcolor.Visible = true;
                    gb_imgset.Controls.Add(titlebackcolor);

                    lb_backcolor.Location = new Point(230, 30);
                    lb_backcolor.Text = "";
                    lb_backcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_backcolor.BackColor = Color.FromArgb(0, 0, 0);
                    lb_backcolor.Width = 60;
                    lb_backcolor.Height = 20;
                    lb_backcolor.Visible = true;
                    lb_backcolor.Enabled = true;
                    lb_backcolor.Click += Lb_color1_Click;
                    gb_imgset.Controls.Add(lb_backcolor);

                    pb_photo.Image = MakeImage.makeFrameImg(lb_kuancolor.BackColor, lb_backcolor.BackColor, 256, 448);
                    break;

                case "ColorBarRow":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "ColorBarRow Seting";
                    Label titlecolor1 = new Label();
                    titlecolor1.Location = new Point(15, 35);
                    titlecolor1.Text = "条数:";
                    titlecolor1.AutoSize = true;
                    titlecolor1.Visible = true;
                    titlecolor1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
                    gb_imgset.Controls.Add(titlecolor1);

                    tb_input1.Location = new Point(55, 30);
                    tb_input1.Text = "8";
                    tb_input1.BorderStyle = BorderStyle.FixedSingle;
                    tb_input1.Width = 60;
                    tb_input1.Height = 20;
                    tb_input1.Visible = true;
                    tb_input1.Enabled = true;
                    gb_imgset.Controls.Add(tb_input1);
                    pb_photo.Image = MakeImage.MakeColorBarRow(Convert.ToInt16( tb_input1.Text), 256, 448); 
                    break;
                case "ColorBarCol":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "ColorBarCol Seting";
                    Label titlecolor2 = new Label();
                    titlecolor2.Location = new Point(15, 35);
                    titlecolor2.Text = "条数:";
                    titlecolor2.AutoSize = true;
                    titlecolor2.Visible = true;
                    titlecolor2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
                    gb_imgset.Controls.Add(titlecolor2);
                    tb_input2.Location = new Point(55, 30);
                    tb_input2.Text = "8";
                    tb_input2.BorderStyle = BorderStyle.FixedSingle;
                    tb_input2.Width = 60;
                    tb_input2.Height = 20;
                    tb_input2.Visible = true;
                    tb_input2.Enabled = true;
                    gb_imgset.Controls.Add(tb_input2);
                    pb_photo.Image = MakeImage.MakeColorBarCol(Convert.ToInt16(tb_input2.Text), 256, 448);
                    break;
                case "Flicker":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "Flicker Seting";
                    Label titleflick1 = new Label();
                    titleflick1.Location = new Point(15, 35);
                    titleflick1.Text = "颜色1:";
                    titleflick1.AutoSize = true;
                    titleflick1.Visible = true;
                    gb_imgset.Controls.Add(titleflick1);
                    lb_fkcolor1.Location = new Point(60, 30);
                    lb_fkcolor1.Text = "";
                    lb_fkcolor1.BorderStyle = BorderStyle.FixedSingle;
                    lb_fkcolor1.Width = 60;
                    lb_fkcolor1.BackColor = Color.FromArgb(0xff, 0, 0xff);
                    lb_fkcolor1.Height = 20;
                    lb_fkcolor1.Visible = true;
                    lb_fkcolor1.Enabled = true;
                    lb_fkcolor1.Click += Lb_color_Click;
                    gb_imgset.Controls.Add(lb_fkcolor1);
                    Label titleflick2 = new Label();
                    titleflick2.Location = new Point(170, 35);
                    titleflick2.Text = "颜色2:";
                    titleflick2.AutoSize = true;
                    titleflick2.Visible = true;
                    gb_imgset.Controls.Add(titleflick2);

                    lb_fkcolor2.Location = new Point(215, 30);
                    lb_fkcolor2.Text = "";
                    lb_fkcolor2.BorderStyle = BorderStyle.FixedSingle;
                    lb_fkcolor2.Width = 60;
                    lb_fkcolor2.Height = 20;
                    lb_fkcolor2.BackColor = Color.FromArgb(0, 0xff, 0);
                    lb_fkcolor2.Visible = true;
                    lb_fkcolor2.Enabled = true;
                    lb_fkcolor2.Click += Lb_color1_Click;
                    gb_imgset.Controls.Add(lb_fkcolor2);
                    pb_photo.Image = MakeImage.makeLineFlicerImg(lb_fkcolor1.BackColor, lb_fkcolor2.BackColor, 256, 448);
                    break;
                case "Picture":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "Picture Seting";
                    Label titalnum = new Label();
                    titalnum.Location = new Point(15, 35);
                    titalnum.Text = "Number:";
                    titalnum.Visible = true;
                    titalnum.Width = 60;
                    titalnum.Height = 20;
                    tb_input3.Location = new Point(60, 30);
                    tb_input3.Text = "1";
                    tb_input3.BorderStyle = BorderStyle.FixedSingle;
                    tb_input3.Width = 60;
                    tb_input3.Height = 20;
                    tb_input3.Visible = true;
                    tb_input3.Enabled = true;
                    gb_imgset.Controls.Add(tb_input3);
                    gb_imgset.Controls.Add(titalnum);
                    Font f = new Font("Arial", 20, FontStyle.Bold);
                    Bitmap bitmap = MakeImage.TextToBitmap("F0" + tb_input3.Text+ ".BMP", f, Rectangle.Empty, Color.Red, Color.White);
                    pb_photo.Image = bitmap; 
                    break;
                case "GradientCol":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "GradientCol Seting";
                    Label titlecolorset = new Label();
                    titlecolorset.Location = new Point(15, 35);
                    titlecolorset.Text = "渐变颜色:";
                    titlecolorset.Width = 60;
                    titlecolorset.Height = 20;
                    titlecolorset.Visible = true;
                    gb_imgset.Controls.Add(titlecolorset);
                    lb_grcolcolor.Location = new Point(75, 30);
                    lb_grcolcolor.Text = "";

                    lb_grcolcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_grcolcolor.Width = 60;
                    lb_grcolcolor.Height = 20;
                    lb_grcolcolor.BackColor = Color.FromArgb(0xff, 0xff, 0xff, 0xff);
                    lb_grcolcolor.Visible = true;
                    lb_grcolcolor.Enabled = true;
                    lb_grcolcolor.Click += Lb_color_Click;
                    gb_imgset.Controls.Add(lb_grcolcolor);
                    Label titlegradnum = new Label();
                    titlegradnum.Location = new Point(170, 35);
                    titlegradnum.Text = "渐变数量:";
                    titlegradnum.Width = 60;
                    titlegradnum.Height = 20;
                    titlegradnum.Visible = true;
                    gb_imgset.Controls.Add(titlegradnum);
                    tb_input4.Location = new Point(230, 30);
                    tb_input4.Text = "8";
                    tb_input4.BorderStyle = BorderStyle.FixedSingle;
                    tb_input4.Width = 60;
                    tb_input4.Height = 20;
                    tb_input4.Visible = true;
                    tb_input4.Enabled = true;
                    gb_imgset.Controls.Add(tb_input4);
                    pb_photo.Image = MakeImage.MakeGradCol(lb_grcolcolor.BackColor,Convert.ToInt16( tb_input4.Text));
                    break;
                case "GradientRow":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "GradientRow Seting";
                    Label titlegradcolor2 = new Label();
                    titlegradcolor2.Location = new Point(15, 35);
                    titlegradcolor2.Text = "渐变颜色:";
                    titlegradcolor2.Width = 60;
                    titlegradcolor2.Height = 20;
                    titlegradcolor2.Visible = true;
                    gb_imgset.Controls.Add(titlegradcolor2);
                    lb_grrowcolor.Location = new Point(75, 30);
                    lb_grrowcolor.Text = "";
                    lb_grrowcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_grrowcolor.Width = 60;
                    lb_grrowcolor.Height = 20;
                    lb_grrowcolor.BackColor = Color.FromArgb(0xff, 0xff, 0xff);
                    lb_grrowcolor.Visible = true;
                    lb_grrowcolor.Enabled = true;
                    lb_grrowcolor.Click += Lb_color_Click;
                    gb_imgset.Controls.Add(lb_grrowcolor);
                    Label titlegradnum1 = new Label();
                    titlegradnum1.Location = new Point(170, 35);
                    titlegradnum1.Text = "渐变数量:";
                    titlegradnum1.Width = 60;
                    titlegradnum1.Height = 20;
                    titlegradnum1.Visible = true;
                    gb_imgset.Controls.Add(titlegradnum1);

                    tb_input5.Location = new Point(230, 30);
                    tb_input5.Text = "8";
                    tb_input5.BorderStyle = BorderStyle.FixedSingle;
                    tb_input5.Width = 60;
                    tb_input5.Height = 20;
                    tb_input5.Visible = true;
                    tb_input5.Enabled = true;
                    gb_imgset.Controls.Add(tb_input5);
                    pb_photo.Image = MakeImage.MakeGradRow(lb_grrowcolor.BackColor, Convert.ToInt16(tb_input5.Text));
                    break;
                case "Checkerboard":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "Checkerboard Seting";
                    Label titalchecknum = new Label();
                    titalchecknum.Location = new Point(15, 35);
                    titalchecknum.Text = "Number:";
                    titalchecknum.Visible = true;
                    titalchecknum.Width = 60;
                    titalchecknum.Height = 20;
                    tb_input6.Location = new Point(60, 30);
                    tb_input6.Text = "8";
                    tb_input6.BorderStyle = BorderStyle.FixedSingle;
                    tb_input6.Width = 60;
                    tb_input6.Height = 20;
                    tb_input6.Visible = true;
                    tb_input6.Enabled = true;
                    gb_imgset.Controls.Add(tb_input6);
                    gb_imgset.Controls.Add(titalchecknum);
                    pb_photo.Image = MakeImage.makeWBImg(Convert.ToInt16( tb_input6.Text), Convert.ToInt16(tb_input6.Text), Color.White, Color.Black, 256, 448);
                    break;
                case "CrossTalk":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "BlackWight Seting";
                    Label titlekuangcolor = new Label();
                    titlekuangcolor.Location = new Point(15, 35);
                    titlekuangcolor.Text = "中间颜色:";
                    titlekuangcolor.Width = 60;
                    titlekuangcolor.Height = 20;
                    titlekuangcolor.Visible = true;
                    gb_imgset.Controls.Add(titlekuangcolor);
                    lb_crosskuancolor.Location = new Point(75, 30);
                    lb_crosskuancolor.Text = "";
                    lb_crosskuancolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_crosskuancolor.Width = 60;
                    lb_crosskuancolor.Height = 20;
                    lb_crosskuancolor.BackColor = Color.FromArgb(0xff, 0xff, 0xff);
                    lb_crosskuancolor.Visible = true;
                    lb_crosskuancolor.Enabled = true;
                    lb_crosskuancolor.Click += Lb_color_Click;
                    gb_imgset.Controls.Add(lb_crosskuancolor);

                    Label titleCrosscolor = new Label();
                    titleCrosscolor.Location = new Point(170, 35);
                    titleCrosscolor.Text = "背景颜色:";
                    titleCrosscolor.Width = 60;
                    titleCrosscolor.Height = 20;
                    titleCrosscolor.Visible = true;
                    gb_imgset.Controls.Add(titleCrosscolor);

                    lb_crossbackcolor.Location = new Point(230, 30);
                    lb_crossbackcolor.Text = "";
                    lb_crossbackcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_crossbackcolor.BackColor = Color.FromArgb(0, 0, 0);
                    lb_crossbackcolor.Width = 60;
                    lb_crossbackcolor.Height = 20;
                    lb_crossbackcolor.Visible = true;
                    lb_crossbackcolor.Enabled = true;
                    lb_crossbackcolor.Click += Lb_color1_Click;
                    gb_imgset.Controls.Add(lb_crossbackcolor);
                    pb_photo.Image = MakeImage.makeCrossTalkImg(lb_crosskuancolor.BackColor, lb_crossbackcolor.BackColor, 256, 448);
                    break;
                case "TpTest":
                    gb_imgset.Controls.Clear();
                    gb_imgset.Text = "TpTest Seting";
                    Label titalnum1 = new Label();
                    titalnum1.Location = new Point(15, 35);
                    titalnum1.Text = "Number:";
                    titalnum1.Visible = true;
                    titalnum1.Width = 60;
                    titalnum1.Height = 20;
                    tb_input3.Location = new Point(60, 30);
                    tb_input3.Text = "1";
                    tb_input3.BorderStyle = BorderStyle.FixedSingle;
                    tb_input3.Width = 60;
                    tb_input3.Height = 20;
                    tb_input3.Visible = true;
                    tb_input3.Enabled = true;
                    gb_imgset.Controls.Add(tb_input3);
                    gb_imgset.Controls.Add(titalnum1);
                    Font f1 = new Font("Arial", 20, FontStyle.Bold);
                    Bitmap bitmap1 = MakeImage.TextToBitmap("TP TEST", f1, Rectangle.Empty, Color.Red, Color.White);
                    pb_photo.Image = bitmap1;
                    break;
                default:
                    gb_imgset.Controls.Clear();
                    break;
            }
            
        }
        private void Lb_color1_Click(object sender, EventArgs e)
        {
            try
            {
                switch (lb_list.SelectedItem)
                {

                    case "BlackWight":
                        color_picker2?.Dispose();
                        color_picker2 = new ColorPickerDialog();
                        color_picker2.Show();
                        pic2threacontrl = true;
                        break;
                    case "Flicker":
                        color_picker2?.Dispose();
                        color_picker2 = new ColorPickerDialog();
                        color_picker2.Show();
                        pic2threacontrl = true;
                        break;
                    case "CrossTalk":
                        color_picker2?.Dispose();
                        color_picker2 = new ColorPickerDialog();
                        color_picker2.Show();
                        pic2threacontrl = true;
                        break;

                    default: break;

                }


            }
            catch (Exception)
            {

                // throw;
            }

        }
        private void Lb_color_Click(object sender, EventArgs e)
        {
            try
            {
                switch (lb_list.SelectedItem)
                {

                    case "Color":
                        color_picker1?.Dispose();
                        color_picker1 = new ColorPickerDialog();
                        color_picker1.Show();
                        picthreacontrl = true;
                        break;
                    case "BlackWight":
                        color_picker1?.Dispose();
                        color_picker1 = new ColorPickerDialog();
                        color_picker1.Show();
                        picthreacontrl = true;
                        break;
                    case "Flicker":
                        color_picker1?.Dispose();
                        color_picker1 = new ColorPickerDialog();
                        color_picker1.Show();
                        picthreacontrl = true;
                        break;
                    case "GradientCol":
                        color_picker1?.Dispose();
                        color_picker1 = new ColorPickerDialog();
                        color_picker1.Show();
                        picthreacontrl = true;
                        break;
                    case "GradientRow":

                        color_picker1?.Dispose();
                        color_picker1 = new ColorPickerDialog();
                        color_picker1.Show();
                        picthreacontrl = true;
                        break;

                    case "CrossTalk":
                        color_picker1?.Dispose();
                        color_picker1 = new ColorPickerDialog();
                        color_picker1.Show();
                        picthreacontrl = true;
                        break;
                    default: break;

                }
            }
            catch (Exception)
            {

                // throw;
            }

        }
        private void bt_add_Click(object sender, EventArgs e)
        {
            button1_Click_2(sender, e);
        }

        private void bt_sub_Click(object sender, EventArgs e)
        {

            try
            {

                    string str = lb_slect.SelectedItem.ToString();
                    int index = lb_slect.SelectedIndex;
                    if (index == 0)
                    {
                        lb_slect.SelectedIndex = index + 1;

                    }
                    else
                    {
                        lb_slect.SelectedIndex = index - 1;
                    }
                    LB_list.Remove(str);
                    lb_slect.Items.RemoveAt(index);
                    bt_saveconfig_Click_1(sender, e);
                    XmlDocument xml1 = new XmlDocument();
                    xml1.Load(piclistpath);
                    XmlNode selectnode = xml1.SelectSingleNode("piclist");
                    XmlNodeList piclist = selectnode.ChildNodes;
                    lb_slect.Items.Clear();
                    for (int i = 0; i < piclist.Count; i++)
                    {
                        lb_slect.Items.Add(piclist.Item(i).InnerText);
                    }
                    lb_slect.SelectedIndex = lb_slect.Items.Count - 1;
                    bt_saveconfig_Click_1(sender, e);
                    DataInit();
            }
            catch (Exception)
            {

                MessageBox.Show("不能删除全部");
            }
            
        }
        #endregion

        private void 在线调试ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedIndex =1;

        }

        private void bt_clearreceve_Click(object sender, EventArgs e)
        {
            tb_serialreceive.Text = "";  //清空接收文本框
            receive_count = 0;          //计数清零
            lb_rxnumber.Text = "Rx:" + receive_count.ToString() + "Bytes";   //刷新界面

        }

        private void bt_serialsend_Click(object sender, EventArgs e)
        {
            byte[] temp = new byte[1];
            try
            {
                //首先判断串口是否开启
                if (serialHelper.serial.IsOpen)
                {
                    int num = 0;   //获取本次发送字节数
                    //串口处于开启状态，将发送区文本发送

                    //判断发送模式
                    if (rb_sendhex.Checked)
                    {
                        //以HEX模式发送
                        //首先需要用正则表达式将用户输入字符中的十六进制字符匹配出来
                        string buf = tb_serialsend.Text;
                        string pattern = @"\s";
                        string replacement = "";
                        Regex rgx = new Regex(pattern);
                        string send_data = rgx.Replace(buf, replacement);

                        //不发送新行
                        num = (send_data.Length - send_data.Length % 2) / 2;
                        for (int i = 0; i < num; i++)
                        {
                            temp[0] = Convert.ToByte(send_data.Substring(i * 2, 2), 16);
                            serialHelper.serial.Write(temp, 0, 1);  //循环发送
                        }
                        //如果用户输入的字符是奇数，则单独处理
                        if (send_data.Length % 2 != 0)
                        {
                            temp[0] = Convert.ToByte(send_data.Substring(tb_serialsend.Text.Length - 1, 1), 16);
                            serialHelper.serial.Write(temp, 0, 1);
                            num++;
                        }
                        //判断是否需要发送新行
                        if (cb_newline.Checked)
                        {
                            //自动发送新行

                            serialHelper.serial.WriteLine(""+"\r");
                        }
                    }
                    else
                    {
                        //以ASCII模式发送
                        //判断是否需要发送新行
                        if (cb_newline.Checked)
                        {
                            //自动发送新行
                            serialHelper.serial.WriteLine(tb_serialsend.Text+"\r");

                            num = tb_serialsend.Text.Length + 2; //回车占两个字节
                        }
                        else
                        {
                            //不发送新行
                            serialHelper.serial.Write(tb_serialsend.Text);
                            num = tb_serialsend.Text.Length;
                        }
                    }

                    send_count += num;      //计数变量累加
                    lb_txnumber.Text = "Tx:" + send_count.ToString() + "Bytes";   //刷新界面
                }
                else 
                {
                    MessageBox.Show("请打开串口", "提示");
                }
            }
            catch (Exception ex)
            {

                System.Media.SystemSounds.Beep.Play();
                MessageBox.Show(ex.Message);

            }

        }

        private void bt_clearsend_Click(object sender, EventArgs e)
        {
            tb_serialsend.Text = "";     //清空发送文本框
            send_count = 0;          //计数清零
            lb_txnumber.Text = "Tx:" + send_count.ToString() + "Bytes";   //刷新界面
        }

        private void bt_upmove_Click(object sender, EventArgs e)
        {
            if (lb_slect.SelectedIndex == 0)
            {
                return;
            }
            else
            {
                int index1 = lb_slect.SelectedIndex;
                int index2 = lb_slect.SelectedIndex - 1;
                lb_slect.Items.Insert(index2, lb_slect.SelectedItem);
                lb_slect.Items.RemoveAt(index1 + 1);
                lb_slect.SelectedIndex = index2;
                //bt_saveconfig_Click_1(sender, e);
            }
        }

        private void bt_downmove_Click(object sender, EventArgs e)
        {
           
                if (lb_slect.SelectedIndex == lb_slect.Items.Count-1)
                {
                    return;
                }
                else
                {
                    int index1 = lb_slect.SelectedIndex;
                    int index2 = lb_slect.SelectedIndex + 2;
                    lb_slect.Items.Insert(index2, lb_slect.SelectedItem);
                    lb_slect.Items.RemoveAt(index1);
                    lb_slect.SelectedIndex = index1 + 1;
                   // bt_saveconfig_Click_1(sender, e);
            }

        }

        private void tb_pclk_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
                
            }
        }

        private void tb_pclk_TextChanged(object sender, EventArgs e)
        {
            if (tb_pclk.Text == "")
            {
                return;
            }

            int number = int.Parse(tb_pclk.Text);
            if (number > 176)
            {
                MessageBox.Show("超出最大值176", "提示");
            }
            Calculate = true;
        }

        private void tb_hsw_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
                
            }
            Calculate = true;
        }

        private void tb_hbw_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;

            }
            Calculate = true;
        }

        private void tb_hact_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;

            }
            Calculate = true;
        }

        private void tb_hfw_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;

            }
            Calculate = true;
        }

        private void tb_vsw_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;

            }
            Calculate = true;
        }

        private void tb_vbw_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;

            }
            Calculate = true;
        }

        private void tb_vact_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;

            }
            Calculate = true;
        }

        private void tb_vfw_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;

            }
            Calculate = true;
        }

        private void pictureBox5_Click(object sender, EventArgs e)
        {

        }

        private void textbox_discompileinfo(string str)
        {

            textBox_compile.ForeColor = Color.Green;
            lb_display.ForeColor = Color.Green;
            textBox_compile.AppendText(str + "\r\n");
            lb_display.Text = "编译完成";


        }

        public void textbox_erroinfo(string str)
        {
            textBox_compile.ForeColor = Color.Red;
            textBox_compile.AppendText(str);
            lb_display.ForeColor = Color.Red;
            lb_display.Text = "编译失败";


        }

      
        private void bt_building_Click(object sender, EventArgs e)
        {
            lb_display.ForeColor = Color.Black;
            lb_downloaddis.Text = "";
            lb_display.Text = "正在编译.....";
            bt_downloadapp.Enabled = false;
            bt_downloadapp.Refresh();
            lb_display.Refresh();
            
            // 保存配置后直接编译（StartCmdWithBat内部异步启动进程，不会阻塞UI线程）
            bt_saveconfig_Click_1(sender, e);
            StartCmdWithBat();
        }
        private Process cmdProcess;
        private string batFilePath;
        private DateTime compilationStartTime; // 记录编译开始时间

        private void StartCmdWithBat()
        {
            // 停止并释放已有的进程
            if (cmdProcess != null)
            {
                try
                {
                    if (!cmdProcess.HasExited)
                    {
                        cmdProcess.Kill();
                        cmdProcess.WaitForExit(2000); // 等待最多2秒确保进程完全退出
                    }
                    cmdProcess.Dispose();
                }
                catch (Exception ex)
                {
                    Debug.WriteLine($"清理进程时出错: {ex.Message}");
                }
                cmdProcess = null;
            }

            // 延迟一小段时间,确保所有资源释放完成
            Thread.Sleep(100);

            textBox_compile.Clear();
            _compileErrorMap.Clear();
            _lastParsedLineCount = 0;
            lb_display.Text = "";
            
            // 记录编译开始时间,用于判断bin文件是否是本次生成的
            compilationStartTime = DateTime.Now;
            
            // 查找编译批处理文件 - 支持多种运行环境
            string cmdpath = null;
            string workingDir = Application.StartupPath;
            
            // 尝试的路径列表（按优先级排序）
            string[] possiblePaths = new string[]
            {
                // 根目录的compile.bat（推荐，它会自动检测环境）
                @"compile.bat",
                // 开发环境运行（Debug目录）
                @"bin\x86\Debug\compile.bat",
                // 开发环境运行（cx900_tools目录）
                @"bin\x86\cx900_tools\compile.bat",
                // 已安装程序运行（bin\Debug目录）
                @"Debug\compile.bat",
                // 已安装程序运行（bin\cx900_tools目录）
                @"cx900_tools\compile.bat",
                // 向上两级查找（如果程序在bin\x86\Debug\下运行）
                @"..\..\compile.bat"
            };
            
            // 查找存在的批处理文件
            foreach (string path in possiblePaths)
            {
                string fullPath = Path.Combine(workingDir, path);
                if (File.Exists(fullPath))
                {
                    cmdpath = fullPath;
                    // 确定正确的工作目录
                    if (path.Contains(@"\..\"))
                    {
                        // 处理上级目录路径
                        workingDir = Path.GetFullPath(Path.Combine(workingDir, path));
                    }
                    else if (path.StartsWith(@"bin\x86\"))
                    {
                        // 从程序根目录运行
                        workingDir = Path.GetDirectoryName(Path.GetDirectoryName(fullPath));
                    }
                    else if (path.StartsWith(@"bin\"))
                    {
                        // 从程序根目录运行
                        workingDir = Path.GetDirectoryName(fullPath);
                    }
                    break;
                }
            }
            
            if (string.IsNullOrEmpty(cmdpath) || !File.Exists(cmdpath))
            {
                UpdateOutput("错误: 找不到编译批处理文件!", Color.Red);
                UpdateOutput("请确保以下任一路径中存在compile.bat:", Color.Yellow);
                foreach (string path in possiblePaths)
                {
                    UpdateOutput($"  - {Path.Combine(Application.StartupPath, path)}", Color.Gray);
                }
                lb_display.ForeColor = Color.Red;
                lb_display.Text = "编译失败";
                return;
            }

            UpdateOutput($"使用编译脚本: {cmdpath}", Color.Gray);
            UpdateOutput($"工作目录: {workingDir}", Color.Gray);
            UpdateOutput("", Color.Black);

            // 创建进程信息
            ProcessStartInfo startInfo = new ProcessStartInfo
            {
                FileName = "cmd.exe",
                // 命令行参数: /c 表示执行后关闭,使用chcp 65001设置UTF-8编码
                // 使用 && 确保返回原目录,避免批处理文件改变工作目录影响后续编译
                Arguments = $"/c \"chcp 65001 >nul 2>&1 && cd /d \"{workingDir}\" && \"{cmdpath}\"\" && exit /b %ERRORLEVEL%",
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                RedirectStandardInput = true,
                CreateNoWindow = true, // 不显示CMD窗口
                WorkingDirectory = workingDir,
                // 设置输出编码为UTF-8,解决中文乱码问题
                StandardOutputEncoding = Encoding.UTF8,
                StandardErrorEncoding = Encoding.UTF8
            };

            // 启动进程
            cmdProcess = new Process { StartInfo = startInfo };

            try
            {
                cmdProcess.Start();

                // 异步读取输出 - 改进:添加时间戳和格式化
                cmdProcess.OutputDataReceived += (sender, e) =>
                {
                    if (!string.IsNullOrEmpty(e.Data))
                    {
                        string output = e.Data.Trim();
                        if (!string.IsNullOrEmpty(output))
                        {
                            // 根据输出内容决定颜色
                            Color outputColor = Color.Green;
                            
                            // 编译相关输出使用特定颜色
                            if (output.Contains("Compiling") || output.Contains("Linking"))
                            {
                                outputColor = Color.DodgerBlue;
                            }
                            else if (output.Contains("Entering directory") || output.Contains("Leaving directory"))
                            {
                                outputColor = Color.DarkGray;
                            }
                            else if (output.Contains("warning:"))
                            {
                                outputColor = Color.Orange;
                            }
                            
                            // 添加时间戳
                            string timestamp = DateTime.Now.ToString("HH:mm:ss.fff");
                            UpdateOutput($"[{timestamp}] {output}", outputColor);
                        }
                    }
                };

                // 异步读取错误输出 - 改进:区分错误和警告
                cmdProcess.ErrorDataReceived += (sender, e) =>
                {
                    if (!string.IsNullOrEmpty(e.Data))
                    {
                        string output = e.Data.Trim();
                        if (!string.IsNullOrEmpty(output))
                        {
                            // 添加时间戳,错误使用红色,警告使用橙色
                            string timestamp = DateTime.Now.ToString("HH:mm:ss.fff");
                            Color errorColor = output.ToLower().Contains("error:") ? Color.Red : Color.Orange;
                            UpdateOutput($"[{timestamp}] {output}", errorColor);
                        }
                    }
                };

                cmdProcess.BeginOutputReadLine();
                cmdProcess.BeginErrorReadLine();

                // 进程退出时的处理 - 改进:添加统计信息
                cmdProcess.Exited += (sender, e) =>
                {
                    // Exited事件在非UI线程触发，所有UI操作必须Invoke到UI线程
                    try
                    {
                        if (textBox_compile.InvokeRequired)
                        {
                            textBox_compile.Invoke(new Action(() =>
                            {
                                HandleCompileExited(cmdProcess, workingDir, compilationStartTime);
                            }));
                        }
                        else
                        {
                            HandleCompileExited(cmdProcess, workingDir, compilationStartTime);
                        }
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine($"编译退出处理异常: {ex.Message}");
                    }
                };
                cmdProcess.EnableRaisingEvents = true;
                
            }
            catch (Exception ex)
            {
                UpdateOutput($"启动进程时出错: {ex.Message}", Color.Red);
            }
        }

        /// <summary>
        /// 处理编译进程退出事件（必须在UI线程调用）
        /// </summary>
        private void HandleCompileExited(Process process, string workingDir, DateTime startTime)
        {
            try
            {
                // 检查编译是否成功的条件:生成了.bin文件且是在本次编译过程中生成的
                bool binFileExists = false;
                string binFilePath = "";

                // 根据工作目录查找.bin文件
                try
                {
                    string buildDir = Path.Combine(workingDir, "build");
                    if (Directory.Exists(buildDir))
                    {
                        string[] binFiles = Directory.GetFiles(buildDir, "*.bin");
                        foreach (string binFile in binFiles)
                        {
                            // 检查文件是否在编译开始后被修改过
                            FileInfo fileInfo = new FileInfo(binFile);
                            if (fileInfo.LastWriteTime >= startTime.AddSeconds(-1))
                            {
                                binFileExists = true;
                                binFilePath = binFile;
                                break;
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    Debug.WriteLine($"查找.bin文件时出错: {ex.Message}");
                }

                if (binFileExists)
                {
                    UpdateOutput("╔═════════════════════════════╗", Color.Green);
                    UpdateOutput("║         编译成功完成!        ║", Color.Green);
                    UpdateOutput($"║生成文件: {Path.GetFileName(binFilePath),-36}║", Color.Green);
                    UpdateOutput("╚═════════════════════════════╝", Color.Green);

                    lb_display.ForeColor = Color.Green;
                    lb_display.Text = "编译成功";
                }
                else
                {
                    string exitCodeMsg = process.ExitCode != 0 ? $" 退出代码: {process.ExitCode}" : "";
                    UpdateOutput("╔════════════════════════════╗", Color.Red);
                    UpdateOutput($"║ 编译失败! 未生成.bin文件{exitCodeMsg}║", Color.Red);
                    UpdateOutput("╚════════════════════════════╝", Color.Red);

                    lb_display.ForeColor = Color.Red;
                    lb_display.Text = "编译失败";
                }

                // 自动滚动到底部
                textBox_compile.Select(textBox_compile.TextLength, 0);
                textBox_compile.ScrollToCaret();

                // 将编译输出写入compile.log
                try
                {
                    string logPath = Path.Combine(Application.StartupPath, "compile.log");
                    File.WriteAllText(logPath, textBox_compile.Text ?? "", Encoding.UTF8);
                }
                catch (Exception logEx)
                {
                    Debug.WriteLine($"写入compile.log失败: {logEx.Message}");
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"处理编译结果时出错: {ex.Message}");
            }
            finally
            {
                try
                {
                    process.Dispose();
                }
                catch { }
            }
        }

        // 更新输出到富文本框 - 改进:优化性能和显示效果
        private void UpdateOutput(string text, Color color)
        {
            if (textBox_compile.InvokeRequired)
            {
                // 如果跨线程调用，使用Invoke
                textBox_compile.Invoke(new Action<string, Color>(UpdateOutput), text, color);
            }
            else
            {
                // 暂停重绘以提高性能
                textBox_compile.SuspendLayout();
                
                try
                {
                    textBox_compile.SelectionStart = textBox_compile.TextLength;
                    textBox_compile.SelectionLength = 0;
                    textBox_compile.SelectionColor = color;
                    textBox_compile.SelectionFont = new Font("Consolas", 9F, FontStyle.Regular);
                    textBox_compile.AppendText(text + Environment.NewLine);
                    
                    // 限制最大行数,避免内存溢出(最多保留5000行)
                    if (textBox_compile.Lines.Length > 5000)
                    {
                        int removeLength = textBox_compile.GetFirstCharIndexFromLine(textBox_compile.Lines.Length - 5000);
                        textBox_compile.Select(0, removeLength);
                        textBox_compile.SelectedText = "";
                    }
                    
                    textBox_compile.ScrollToCaret();
                }
                finally
                {
                    textBox_compile.ResumeLayout();
                }
            }
        }

        // 窗体关闭时确保进程被终止
        private void CmdBatForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (cmdProcess != null && !cmdProcess.HasExited)
            {
                cmdProcess.Kill();
            }
        }
        
        // 清空编译输出
        private void ClearCompileOutput()
        {
            textBox_compile.Clear();
            _compileErrorMap.Clear();
            _lastParsedLineCount = 0;
            lb_display.Text = "";
            lb_display.ForeColor = Color.Black;
        }
        
        // 保存编译日志到文件
        private void SaveCompileLog()
        {
            try
            {
                SaveFileDialog saveDlg = new SaveFileDialog
                {
                    Filter = "文本文件|*.txt|所有文件|*.*",
                    Title = "保存编译日志",
                    FileName = $"compile_log_{DateTime.Now:yyyyMMdd_HHmmss}.txt",
                    InitialDirectory = Application.StartupPath
                };
                
                if (saveDlg.ShowDialog() == DialogResult.OK)
                {
                    File.WriteAllText(saveDlg.FileName, textBox_compile.Text, Encoding.UTF8);
                    MessageBox.Show($"编译日志已保存到:\n{saveDlg.FileName}", "保存成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"保存日志失败: {ex.Message}", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        
        // 复制编译输出到剪贴板
        private void CopyCompileOutput()
        {
            if (textBox_compile.SelectedText.Length > 0)
            {
                Clipboard.SetText(textBox_compile.SelectedText);
            }
            else
            {
                Clipboard.SetText(textBox_compile.Text);
            }
        }
        
        // 初始化编译输出框的右键菜单
        private void InitCompileOutputContextMenu()
        {
            ContextMenuStrip contextMenu = new ContextMenuStrip();
            
            // 复制
            ToolStripMenuItem copyItem = new ToolStripMenuItem("复制(&C)");
            copyItem.ShortcutKeys = Keys.Control | Keys.C;
            copyItem.Click += (sender, e) => CopyCompileOutput();
            contextMenu.Items.Add(copyItem);
            
            // 复制全部
            ToolStripMenuItem copyAllItem = new ToolStripMenuItem("复制全部(&A)");
            copyAllItem.Click += (sender, e) =>
            {
                Clipboard.SetText(textBox_compile.Text);
            };
            contextMenu.Items.Add(copyAllItem);
            
            contextMenu.Items.Add(new ToolStripSeparator());
            
            // 保存日志
            ToolStripMenuItem saveItem = new ToolStripMenuItem("保存日志(&S)");
            saveItem.ShortcutKeys = Keys.Control | Keys.S;
            saveItem.Click += (sender, e) => SaveCompileLog();
            contextMenu.Items.Add(saveItem);
            
            contextMenu.Items.Add(new ToolStripSeparator());
            
            // 清空
            ToolStripMenuItem clearItem = new ToolStripMenuItem("清空(&L)");
            clearItem.ShortcutKeys = Keys.Control | Keys.L;
            clearItem.Click += (sender, e) => ClearCompileOutput();
            contextMenu.Items.Add(clearItem);
            
            // 查找
            ToolStripMenuItem findItem = new ToolStripMenuItem("查找(&F)");
            findItem.ShortcutKeys = Keys.Control | Keys.F;
            findItem.Click += (sender, e) =>
            {
                if (textBox_compile.SelectedText.Length > 0)
                {
                    // 简单的查找功能
                    string searchText = textBox_compile.SelectedText;
                    int startIndex = textBox_compile.SelectionStart + textBox_compile.SelectionLength;
                    int index = textBox_compile.Find(searchText, startIndex, RichTextBoxFinds.None);
                    if (index == -1)
                    {
                        index = textBox_compile.Find(searchText, 0, RichTextBoxFinds.None);
                    }
                    if (index != -1)
                    {
                        textBox_compile.Select(index, searchText.Length);
                        textBox_compile.ScrollToCaret();
                    }
                }
                else
                {
                    MessageBox.Show("请先选择要查找的文本", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            };
            contextMenu.Items.Add(findItem);
            
            // 璁句负鍙, 闃叉 RichTextBox 鍐呴儴鍗曡瘝閫夋嫨鍚炴帀鍙屽嚮浜嬩欢
            textBox_compile.ReadOnly = true;
            textBox_compile.AutoWordSelection = true;
            textBox_compile.ContextMenuStrip = contextMenu;

            // 双击错误行跳转到源代码
            textBox_compile.MouseDoubleClick += TextBox_compile_MouseDoubleClick;
        }

        /// <summary>
        /// TextChanged 时增量解析编译输出，构建"行索引→(文件名,行号)"映射
        /// 避免双击时依赖坐标映射（控件太小/WordWrap会导致坐标不准）
        /// </summary>
        private void textBox_compile_TextChanged(object sender, EventArgs e)
        {
            try
            {
                string[] lines = textBox_compile.Lines;
                int totalLines = lines.Length;
                Debug.WriteLine($"[DEBUG TextChanged] totalLines={totalLines}, _lastParsedLineCount={_lastParsedLineCount}");
                if (totalLines <= _lastParsedLineCount)
                    return;

                // 只解析新增的行
                for (int i = _lastParsedLineCount; i < totalLines; i++)
                {
                    string lineText = lines[i].Trim();
                    if (string.IsNullOrEmpty(lineText))
                        continue;

                    // 支持带时间戳的格式: [11:20:04.486] Module/power_task.c:25:23: error:
                    // 也支持纯格式: Module/power_task.c:25:23: error:
                    var match = System.Text.RegularExpressions.Regex.Match(
                        lineText, @"([A-Za-z0-9_/\\-]+\.[ch])[:\(](\d+)");
                    Debug.WriteLine($"[DEBUG TextChanged] line {i}: match={match.Success}, groups='{match.Value}', line='{lineText.Substring(0, Math.Min(80, lineText.Length))}'");
                    if (match.Success)
                    {
                        _compileErrorMap[i] = new CompileErrorInfo
                        {
                            fileName = match.Groups[1].Value,
                            lineNumber = int.Parse(match.Groups[2].Value)
                        };
                        Debug.WriteLine($"[DEBUG TextChanged] Parsed line {i}: file={match.Groups[1].Value}, num={match.Groups[2].Value}");
                    }
                }
                _lastParsedLineCount = totalLines;
            }
            catch { }
        }

        /// <summary>
        /// 双击编译输出中的错误行，跳转到 scintilla 对应的源代码行并高亮
        /// 如 [10:09:06.194] Module/power_task.c:25:23: error: ...
        ///   power_task.c → scintilla2,  lcd_cfg.c → scintilla1
        /// </summary>
        private void TextBox_compile_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            BeginInvoke(new Action(() =>
            {
                try
                {
                    int selStart = textBox_compile.SelectionStart;
                    if (selStart < 0 || selStart >= textBox_compile.TextLength)
                        return;

                    int lineIndex = textBox_compile.GetLineFromCharIndex(selStart);
                    string lineText = textBox_compile.Lines[lineIndex];
                    Debug.WriteLine($"[DEBUG DoubleClick] lineIndex={lineIndex}, map count={_compileErrorMap.Count}, line='{lineText}'");

                    if (!_compileErrorMap.TryGetValue(lineIndex, out CompileErrorInfo errorInfo))
                    {
                        Debug.WriteLine($"[DEBUG DoubleClick] No entry in map for lineIndex={lineIndex}");
                        return;
                    }

                    Debug.WriteLine($"[DEBUG DoubleClick] file={errorInfo.fileName}, line={errorInfo.lineNumber}");

                    string fileName = errorInfo.fileName;
                    int lineNumber = errorInfo.lineNumber;

                    // 文件映射
                    ScintillaNET.Scintilla targetScintilla = null;
                    string fileNameLower = fileName.ToLower();

                    if (fileNameLower.Contains("lcd_cfg"))
                        targetScintilla = scintilla1;
                    else if (fileNameLower.Contains("power_task"))
                        targetScintilla = scintilla2;
                    else if (fileNameLower.EndsWith(".c") || fileNameLower.EndsWith(".h"))
                        targetScintilla = scintilla1;

                    if (targetScintilla == null)
                        return;

                    // 切换到对应tab
                    TabPage targetTab = (TabPage)targetScintilla.Parent;
                    if (targetTab != null)
                        tabControl1.SelectedTab = targetTab;

                    // GCC 行号 1 基 → Scintilla 行号 0 基
                    int targetLine = lineNumber - 1;
                    if (targetLine < 0) targetLine = 0;
                    if (targetLine >= targetScintilla.Lines.Count)
                        targetLine = targetScintilla.Lines.Count - 1;

                    // 跳转并选中整行高亮
                    targetScintilla.Lines[targetLine].Goto();
                    int lineStart = targetScintilla.Lines[targetLine].Position;
                    int lineEnd = lineStart + targetScintilla.Lines[targetLine].Length;
                    targetScintilla.SetSelection(lineEnd, lineStart);
                    targetScintilla.Focus();
                }
                catch (Exception ex)
                {
                    Debug.WriteLine("Double-click error jump failed: " + ex.Message);
                }
            }));
        }

        private void compile()
        {
            try
            {
               
                    this.Invoke(new Action(() =>
                    {
                        Task.Run(() =>
                        {
                            cc.upstr = textbox_discompileinfo;
                            cc.upfail += textbox_erroinfo;
                            cc.cleancompile();
                            cc.startcompile();
                        });
                        textBox_compile.Refresh();
                        this.textBox_compile.Focus();
                        //设置光标的位置到文本尾
                        this.textBox_compile.Select(this.textBox_compile.TextLength, 0);
                        //滚动到控件光标处
                        this.textBox_compile.ScrollToCaret();
                        bt_downloadapp.Enabled = true;
                        bt_downloadapp.Refresh();
                       
                    }));

               
               
            }
            catch (Exception e)
            {

                MessageBox.Show(e.Message);
            }



        }
        private void cb_lcdtype_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cb_lcdtype.SelectedIndex == 0)
            {
                cb_mipilan.Enabled = true;
                cb_mipimode.Enabled= true;
                check_mipiswap.Enabled = true;
                check_dualport.Enabled = true;
                //check_odlr.Enabled = true;
            }
            else
            {
                cb_mipilan.Enabled  = false;
                cb_mipimode.Enabled = false;
                check_mipiswap.Enabled = false;
                check_dualport.Enabled = false;
               // check_odlr.Enabled = false;
            }

        }

        private void 升级BOOTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bootiapflag = true;
            DL_form form1 = new DL_form(cb_serialprot.Text);
            form1.mydel += new DL_form.mydelegate(download);
            form1.Text = "Boot Updata";
            form1.ShowDialog();
        }

        private void 在线升级ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                Process process = new Process();
                FileInfo fileInfo = new FileInfo("up.bat");
                process.StartInfo.WorkingDirectory = fileInfo.Directory.FullName;
                process.StartInfo.FileName = fileInfo.Name;
                process.StartInfo.CreateNoWindow = false;
                process.Start();

                process.WaitForExit();
                process.Close();
            }
            catch (Exception s)
            {
                Console.WriteLine(s.Message);
            }

        }
        public Dictionary<int, int> to_com = new Dictionary<int, int>();
        public int to_ls = 0;
      

        private void bt_default_Click(object sender, EventArgs e)
        {
            for (int i=0;i< dataGridView1.Rows.Count;i++ )
            {
                if (i < 8)
                {
                    dataGridView1.Rows[i].Cells[2].Value = Convert.ToUInt16(dataGridView1.Rows[i].Cells[1].Value) + 100;
                    dataGridView1.Rows[i].Cells[3].Value = Convert.ToUInt16(dataGridView1.Rows[i].Cells[1].Value) - 100;
                }
                else
                {
                    dataGridView1.Rows[i].Cells[2].Value = 40000;
                    dataGridView1.Rows[i].Cells[3].Value = 0;
                }
                if (i < 6)
                {
                    dataGridView1.Rows[i].Cells[4].Value = 300;
                }
                else if (i < 8)
                {
                    dataGridView1.Rows[i].Cells[4].Value = 100;
                }
                else 
                {
                    dataGridView1.Rows[i].Cells[4].Value = 100;
                }
                
                dataGridView1.Rows[i].Cells[5].Value = 0;
            }
            

        }

        private void cb_alarm_MouseClick(object sender, MouseEventArgs e)
        {
            if (cb_alarm.Checked == true)
            {
                bt_default_Click(sender, e);
            }
        }

        private void dataGridView1_CurrentCellChanged(object sender, EventArgs e)
        {
            int j = 0;
            for (int i = 0; i < dataGridView1.Rows.Count-1; i++)
            {
                j += 1;
                if (Convert.ToUInt16(dataGridView1.Rows[i].Cells[1].Value) >= Convert.ToUInt16(dataGridView1.Rows[i].Cells[2].Value))
                {
                    DataGridViewCell bb = dataGridView1.Rows[i].Cells[1];
                    bb.Style.ForeColor = Color.Red;
                    bb.Style.BackColor = Color.Yellow;
                    return;
                   // MessageBox.Show("第"+j+"行第2列比第3列值大，请修改");
                }
                else if(Convert.ToUInt16(dataGridView1.Rows[i].Cells[1].Value) <= Convert.ToUInt16(dataGridView1.Rows[i].Cells[3].Value))
                {
                    DataGridViewCell bb = dataGridView1.Rows[i].Cells[1];
                    bb.Style.ForeColor = Color.Red;
                    bb.Style.BackColor = Color.Yellow;
                    return;
                    // MessageBox.Show("第" + j + "行第2列比第4列值小，请修改");
                }
                else
                {
                    DataGridViewCell aa = dataGridView1.Rows[i].Cells[1];
                    aa.Style.ForeColor = Color.Black;
                    aa.Style.BackColor = Color.White;

                }

                
            }
        }

        private void aPI文档ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("notepad.exe", "api.txt");
        }

        private void check_dualport_CheckedChanged(object sender, EventArgs e)
        {
            if (check_dualport.Checked)
            {
                check_odlr.Enabled = true;
            }
            else
            {
                check_odlr.Enabled = false;
            }

        }

        private void pictureBox5_Click_1(object sender, EventArgs e)
        {
            OpenSearch1();
            SearchManager.Find(false, true);
        }

        private void pictureBox6_Click(object sender, EventArgs e)
        {
            OpenSearch1();
            SearchManager.Find(true, false);
        }

        private void pictureBox7_Click(object sender, EventArgs e)
        {
            OpenSearch1();
            SearchManager.Find(false, false);
            CloseSearch1();
        }
    }
}
