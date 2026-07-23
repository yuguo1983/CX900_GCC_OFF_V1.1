//using Microsoft.Windows.PowerShell.Gui.Internal;
using Cyotek.Windows.Forms;
using ScintillaNET;
using System;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Security.Cryptography.X509Certificates;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Linq;
using static CX900.StructClass;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TextBox;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ToolBar;

namespace CX900
{
    public partial class MainForm : Form
    {
        public String configpath = @"./config.xml";
        public String pixpath = @"./pix_config.xml";
        public String codepath = @"./code.c";
        XmlDocument doc = new XmlDocument();
       
       

  
        public StructClass.all_paramter parent = new StructClass.all_paramter();
        public StructClass.pMIPI_Para_Table child = new StructClass.pMIPI_Para_Table();
        
        SerialHelper serialHelper = new SerialHelper();
        public delegate void SerialDataReceivedEventargs(object sender, SerialDataReceivedEventArgs e, byte[] _data);
        public event SerialDataReceivedEventargs Datareceve;

        public bool ReceiveEventFlag = false;
        #region MainForm
        public MainForm()
        {
            InitializeComponent();

            this.scintilla1.Styles[32].Size = 10;
            InitHotkeys();
            DataInit();
            DoloadParamter();
            InitSyntaxColoring();
            InitNumberMargin();
            InitDragDropFile();
            InitBookmarkMargin();
            this.scintilla1.WrapMode = WrapMode.Word;
            this.scintilla1.IndentationGuides = IndentView.LookBoth;
            LoadDataFromFile(codepath);
            openfile.Dispose();
            foreach (var item in System.IO.Ports.SerialPort.GetPortNames())
            {
                cb_serialprot.Items.Add(item);
            }
            cb_serialprot.SelectedIndex = cb_serialprot.TabIndex - 1;
            serialHelper.Baudrate = 115200;
            progressBar1.Visible = false;
            Image image = MakeImage.makeFrameImg(Color.White, Color.Black, 256, 448);
            pb_photo.Image = image;
            int width = pb_photo.Width + 4;
            int hight = pb_photo.Height + 4;
            pb_back.Size = new Size(Width, hight);
            pb_back.Image = MakeImage.makeColorImg(Color.Gray, 276, 468);
           
        }
        #endregion
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
        Label lb_colorset;
        Label lb_kuancolor;
        Label lb_backcolor;
        Color colorset;
        Color kuangrset;
        Color backset;

        #region checkserial
        private void checkserial()
        {

            while (this.IsHandleCreated)
            {
                Thread.Sleep(100);
               
                    this?.BeginInvoke((EventHandler)(delegate
                    {
                        try
                        {
                            if (base.IsDisposed == false)
                            {

                                if (serialHelper.serial.IsOpen)
                                {
                                    cb_serialprot.Enabled = false;
                                }
                                else
                                {
                                    cb_serialprot.Enabled = true;
                                }
                            }
                            if (colorPickerDialog != null && lb_colorset != null)
                            {
                                if (colorPickerDialog.DialogResult == DialogResult.OK)
                                {
                                    lb_colorset.BackColor = colorPickerDialog.Color;
                                    if (colorset != lb_colorset.BackColor)
                                    {
                                        colorset = lb_colorset.BackColor;
                                        Image i = MakeImage.makeColorImg(colorset, 256, 448);
                                        pb_photo.Image = i;
                                    }
                                }
                            }
                            if (colorkuan != null)
                            {
                                if (colorkuan.DialogResult == DialogResult.OK)
                                {
                                    lb_kuancolor.BackColor = colorkuan.Color;


                                    if (kuangrset != lb_kuancolor.BackColor)
                                    {
                                        kuangrset = lb_kuancolor.BackColor;

                                        Image i = MakeImage.makeFrameImg(kuangrset, backset, 256, 448);
                                        pb_photo.Image = i;
                                    }

                                }
                            }
                            if (colorback != null)
                            { 
                                if (colorback.DialogResult == DialogResult.OK)
                                {
                                    lb_backcolor.BackColor = colorback.Color;
                                    if (backset != lb_backcolor.BackColor)
                                    {
                                        backset = lb_backcolor.BackColor;
                                        Image i = MakeImage.makeFrameImg(kuangrset, backset, 256, 448);
                                        pb_photo.Image = i;
                                    }
                                }
                            }
                        }
                        catch (Exception)
                        {
                            //checkflag = false;
                            //throw;
                        }

                    }));
                }
            
        }
        #endregion
        
        private void Lb_backcolor_Click(object sender, EventArgs e)
        {
            try
            {
                colorback = new ColorPickerDialog();
                colorback.Show();
            }
            catch (Exception)
            {

                throw;
            }
            
        }

        private void Lb_kuancolor_Click(object sender, EventArgs e)
        {
            try
            {
                colorkuan= new ColorPickerDialog();
                colorkuan.Show();
            }
            catch (Exception)
            {

                throw;
            }
                           
        }

        private void Lb_colorset_Click(object sender, EventArgs e)
        {
            colorPickerDialog = new ColorPickerDialog();
            colorPickerDialog.Show();
        }

        public void getSerialPortAllName()
        {
            Invoke((EventHandler)(delegate {
                cb_serialprot.Items.Clear();
                cb_serialprot.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
                cb_serialprot.SelectedIndex = System.IO.Ports.SerialPort.GetPortNames().Length - 1;//设定选择项    
                try
                {
                    serialHelper.serial.PortName = cb_serialprot.Text;
                    serialHelper.serial.Open();
                }
                catch (Exception)
                {

                    //throw;
                }
               
            }));

        }




    
    private void _dataReceive(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                Thread.Sleep(100);
                byte[] _data = new byte[serialHelper.serial.BytesToRead];
                serialHelper.serial.Read(_data, 0, _data.Length);

                if (_data.Length== 0)
                {
                    return;
                }

                Datareceve?.Invoke(sender, e, _data);
                

            }
            catch (Exception)
            {

                //throw;
            }
        
        }

        #region DataInit
        private void DataInit()
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
            tb_icname.Text= ddaa.Item(0).ChildNodes.Item(9).InnerText;
            tb_codezip.Text= ddaa.Item(0).ChildNodes.Item(10).InnerText;
            tb_pclk.Text = ddaa.Item(0).ChildNodes.Item(11).InnerText;
            cb_mipilan.Text = ddaa.Item(0).ChildNodes.Item(12).InnerText;
            cb_deset.Text = ddaa.Item(0).ChildNodes.Item(16).InnerText;
            cb_vsset.Text = ddaa.Item(0).ChildNodes.Item(17).InnerText;
            cb_hsset.Text = ddaa.Item(0).ChildNodes.Item(18).InnerText;
            cb_mipimode.Text = ddaa.Item(0).ChildNodes.Item(21).InnerText;
            cb_allmode.Text = ddaa.Item(0).ChildNodes.Item(15).InnerText;

            check_aenable.Checked =Convert.ToBoolean( ddaa.Item(0).ChildNodes.Item(13).InnerText);
            check_benable.Checked= Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(14).InnerText);
            check_mipiswap.Checked= Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(19).InnerText);
            check_odlr.Checked= Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(20).InnerText);
            check_dualport.Checked= Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(22).InnerText);
        }

        #endregion

        #region DoloadParamter
        private void DoloadParamter()
        {
            #region pix data
            XmlDocument xml = new XmlDocument();
            xml.Load(pixpath);
            XmlNode ddd = xml.SelectSingleNode("DocumentElement");
            XmlNodeList ddaa = ddd.ChildNodes;
            #endregion
            
            doc.Load(configpath);
            XmlNode list = doc.SelectSingleNode("SETING");
            XmlNodeList alarm = list.ChildNodes;


            parent.pMIPItable = child;
            child.bLCDName = ddaa.Item(0).ChildNodes.Item(8).InnerText+"\n";
            child.bICName = ddaa.Item(0).ChildNodes.Item(9).InnerText + "\n";
            child.CodeZip = ddaa.Item(0).ChildNodes.Item(10).InnerText + "\n";
            child.DUAL_MIPI_LCD =  Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(22).InnerText) == true) ? 1 : 0);
            child.DUAL_MIPI_CHANNEL_SWAP = Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(19).InnerText) == true) ? 1 : 0);
            child.ODD_EVEN_nLEFT_RIGHT = Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(20).InnerText) == true) ? 1 : 0);
            child.PCLK_Freq = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(11).InnerText);
            child.LANE_CNT  = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(12).InnerText); 
            child.V_DE = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(16).InnerText.Substring(0, 1));
            child.V_VS = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(17).InnerText.Substring(0, 1));
            child.V_HS = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(18).InnerText.Substring(0, 1));
            child.V_CLK = 0;
            child.Display_Mode = Convert.ToByte(ddaa.Item(0).ChildNodes.Item(21).InnerText.Substring(0, 1));
            child.HACT_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(2).InnerText);
            child.VACT_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(6).InnerText);
            child.HFP_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(1).InnerText);
            child.HBP_WIDTH = Convert.ToUInt16( ddaa.Item(0).ChildNodes.Item(0).InnerText);
            child.HSW_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(3).InnerText);
            child.VFP_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(5).InnerText);
            child.VBP_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(4).InnerText);
            child.VSW_WIDTH = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(7).InnerText);



            child.NomalVCC1SET  = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(1).InnerText);
            child.LowperVCC1VOL = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(3).InnerText);
            child.UperVCC1VOL   = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(2).InnerText);
            child.LowperVCC1MA  = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(5).InnerText);
            child.UperVCC1MA    = Convert.ToUInt16(alarm.Item(0).ChildNodes.Item(4).InnerText);


            child.NomalVCC2SET  = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(1).InnerText);
            child.LowperVCC2VOL = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(3).InnerText);
            child.UperVCC2VOL   = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(2).InnerText);
            child.LowperVCC2MA  = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(5).InnerText);
            child.UperVCC2MA    = Convert.ToUInt16(alarm.Item(1).ChildNodes.Item(4).InnerText);

            child.NomalVCC3SET  =  Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(1).InnerText);
            child.LowperVCC3VOL =  Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(3).InnerText);
            child.UperVCC3VOL   =  Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(2).InnerText);
            child.LowperVCC3MA  =  Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(5).InnerText);
            child.UperVCC3MA    =  Convert.ToUInt16(alarm.Item(2).ChildNodes.Item(4).InnerText);

            child.NomalVCC4SET  =  Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(1).InnerText);
            child.LowperVCC4VOL =  Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(3).InnerText);
            child.UperVCC4VOL   =  Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(2).InnerText);
            child.LowperVCC4MA  =  Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(5).InnerText);
            child.UperVCC4MA    =  Convert.ToUInt16(alarm.Item(3).ChildNodes.Item(4).InnerText);

            child.NomalVCC5SET  = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(1).InnerText);
            child.LowperVCC5VOL = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(3).InnerText);
            child.UperVCC5VOL   = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(2).InnerText);
            child.LowperVCC5MA  = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(5).InnerText);
            child.UperVCC5MA    = Convert.ToUInt16(alarm.Item(4).ChildNodes.Item(4).InnerText);

            child.NomalVCC6SET  =  Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(1).InnerText);
            child.LowperVCC6VOL =  Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(3).InnerText);
            child.UperVCC6VOL   =  Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(2).InnerText);
            child.LowperVCC6MA  =  Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(5).InnerText);
            child.UperVCC6MA    =  Convert.ToUInt16(alarm.Item(5).ChildNodes.Item(4).InnerText);

            child.NomalVSPSET   = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(1).InnerText);
            child.LowperVSPVOL  = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(3).InnerText);
            child.UperVSPVOL    = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(2).InnerText);
            child.LowperVSPMA   = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(5).InnerText);
            child.UperVSPMA     = Convert.ToUInt16(alarm.Item(6).ChildNodes.Item(4).InnerText);

            child.NomalVSNSET   =  Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(1).InnerText);
            child.LowperVSNVOL  =  Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(3).InnerText);
            child.UperVSNVOL    =  Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(2).InnerText);
            child.LowperVSNMA   =  Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(5).InnerText);
            child.UperVSNMA     =  Convert.ToUInt16(alarm.Item(7).ChildNodes.Item(4).InnerText);

            child.Low_Delay = 5000;
            child.SIZE_OF_SHOW_MODE = Convert.ToUInt16(ddaa.Item(0).ChildNodes.Item(15).InnerText);
            child.PicIndex1 = 1;
            child.PicIndex2 = 2;
            child.MIPI_MODE =0;
            child.DW1_EN = Convert.ToByte( (Convert.ToBoolean( ddaa.Item(0).ChildNodes.Item(13).InnerText)==true)?1:0) ;
            child.DW2_EN = Convert.ToByte((Convert.ToBoolean(ddaa.Item(0).ChildNodes.Item(14).InnerText) == true) ? 1 : 0); ;

            parent.flag = 0x01;
            

            
            
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
            this.scintilla1.Styles[Style.Default].BackColor = IntToColor(0x212121);
            this.scintilla1.Styles[Style.Default].ForeColor = IntToColor(0xFFFFFF);
            this.scintilla1.StyleClearAll();

            // Configure the CPP (C) lexer styles
            this.scintilla1.Styles[Style.Cpp.Identifier].ForeColor = IntToColor(0xD0DAE2);
            this.scintilla1.Styles[Style.Cpp.Comment].ForeColor = IntToColor(0xBD758B);
            this.scintilla1.Styles[Style.Cpp.CommentLine].ForeColor = IntToColor(0x40BF57);
            this.scintilla1.Styles[Style.Cpp.CommentDoc].ForeColor = IntToColor(0x2FAE35);
            this.scintilla1.Styles[Style.Cpp.Number].ForeColor = IntToColor(0xFFFF00);
            this.scintilla1.Styles[Style.Cpp.String].ForeColor = IntToColor(0xFFFF00);
            this.scintilla1.Styles[Style.Cpp.Character].ForeColor = IntToColor(0xE95454);
            this.scintilla1.Styles[Style.Cpp.Preprocessor].ForeColor = IntToColor(0x8AAFEE);
            this.scintilla1.Styles[Style.Cpp.Operator].ForeColor = IntToColor(0xE0E0E0);
            this.scintilla1.Styles[Style.Cpp.Regex].ForeColor = IntToColor(0xff00ff);
            this.scintilla1.Styles[Style.Cpp.CommentLineDoc].ForeColor = IntToColor(0x77A7DB);
            this.scintilla1.Styles[Style.Cpp.Word].ForeColor = IntToColor(0x48A8EE);
            this.scintilla1.Styles[Style.Cpp.Word2].ForeColor = IntToColor(0xF98906);
            this.scintilla1.Styles[Style.Cpp.CommentDocKeyword].ForeColor = IntToColor(0xB3D991);
            this.scintilla1.Styles[Style.Cpp.CommentDocKeywordError].ForeColor = IntToColor(0xFF0000);
            this.scintilla1.Styles[Style.Cpp.GlobalClass].ForeColor = IntToColor(0x48A8EE);
            this.scintilla1.Lexer = Lexer.Cpp;
            ContextMenu contextMenu = this.scintilla1.ContextMenu;
            this.scintilla1.SetKeywords(0, "bsp_DelayMS SSD2828_WritePackageSize SSD2828_SPI_Write_Data SPI_WriteCmd SPI_WriteData set_tim_vcc set_tim_iovcc set_tim_vsp set_tim_vsn set_vcc set_iovcc set_vspvol set_vsnvol set_eniovcc set_envcc set_envsp set_envsn Ssd2828ON O_LCD_RESET O_SSD2828_RESET  GPU_BL KeyUp_Process void");
            this.scintilla1.SetKeywords(1, "bsp_DelayMS SSD2828_WritePackageSize SSD2828_SPI_Write_Data SPI_WriteCmd SPI_WriteData set_tim_vcc set_tim_iovcc set_tim_vsp set_tim_vsn set_vcc set_iovcc set_vspvol set_vsnvol set_eniovcc set_envcc set_envsp set_envsn Ssd2828ON O_LCD_RESET O_SSD2828_RESET  GPU_BL KeyUp_Process void");
        }


        #endregion
        private const int NUMBER_MARGIN = 1;
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

        // Token: 0x060000DC RID: 220 RVA: 0x0000FCFC File Offset: 0x0000DEFC
        private void Uppercase()
        {
            int selectionStart = this.scintilla1.SelectionStart;
            int selectionEnd = this.scintilla1.SelectionEnd;
            this.scintilla1.ReplaceSelection(this.scintilla1.GetTextRange(selectionStart, selectionEnd - selectionStart).ToUpper());
            this.scintilla1.SetSelection(selectionStart, selectionEnd);
        }

        // Token: 0x060000DD RID: 221 RVA: 0x0000F3EF File Offset: 0x0000D5EF
        private void OpenFindDialog()
        {
            // this.MyFindReplace.ShowFind();
        }

        // Token: 0x060000DE RID: 222 RVA: 0x0000FD50 File Offset: 0x0000DF50
        private void OpenReplaceDialog()
        {
            //this.MyFindReplace.ShowReplace();
        }

        // Token: 0x060000DF RID: 223 RVA: 0x0000FD5F File Offset: 0x0000DF5F
        private void ZoomIn()
        {
            this.scintilla1.ZoomIn();
        }

        // Token: 0x060000E0 RID: 224 RVA: 0x0000FD6E File Offset: 0x0000DF6E
        private void ZoomOut()
        {
            this.scintilla1.ZoomOut();
        }

        // Token: 0x060000E1 RID: 225 RVA: 0x0000FD7D File Offset: 0x0000DF7D
        private void ZoomDefault()
        {
            this.scintilla1.Zoom = 0;
        }
        private void InitNumberMargin()
        {

            scintilla1.Styles[Style.LineNumber].BackColor = Color.FromArgb(0x2A211C); ;
            scintilla1.Styles[Style.LineNumber].ForeColor = IntToColor(0xB7B7B7);
            scintilla1.Styles[Style.IndentGuide].ForeColor = IntToColor(0xB7B7B7);
            scintilla1.Styles[Style.IndentGuide].BackColor = IntToColor(0x2A211C);

            var nums = scintilla1.Margins[NUMBER_MARGIN];
            nums.Width = 30;
            nums.Type = MarginType.Number;
            nums.Sensitive = true;
            nums.Mask = 0;

            scintilla1.MarginClick += TextArea_MarginClick;
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
                    InvokeIfNeeded(delegate () {
                    PanelSearch.Visible = true;
                    TxtSearch.Text = SearchManager.LastSearch;
                    TxtSearch.Focus();
                    TxtSearch.SelectAll();
                });
            }
            else
            {
                    InvokeIfNeeded(delegate () {
                    TxtSearch.Focus();
                    TxtSearch.SelectAll();
                });
            }
        }


        private void CloseSearch()
        {
            if (SearchIsOpen)
            {
                SearchIsOpen = false;
                InvokeIfNeeded(delegate () {
                    PanelSearch.Visible = false;
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

        /// <summary>
        /// 文件拖拽
        /// 
        /// </summary>
        public void InitDragDropFile()
        {

            scintilla1.AllowDrop = true;
            scintilla1.DragEnter += delegate (object sender, DragEventArgs e) {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                    e.Effect = DragDropEffects.Copy;
                else
                    e.Effect = DragDropEffects.None;
            };
            scintilla1.DragDrop += delegate (object sender, DragEventArgs e) {

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
                this.Text ="CX900_Tools   "+ fileDir + "\\" + Path.GetFileName(path);
                scintilla1.Text = File.ReadAllText(path);
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
            if (prjfilepath.ShowDialog() == DialogResult.OK)
            {
                prjfilepath.Filter = "CXKJ|*.CXKJ";
                File.Delete(configpath);
                File.Delete(pixpath);
                File.Delete(codepath);
                SharpZip.UnpackFiles(prjfilepath.FileName, @"./");
                DataInit();
                DoloadParamter();
                LoadDataFromFile(codepath);
                openfile.Dispose();
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            CloseSearch();
            Thread thcheckserial = new Thread(checkserial);
            thcheckserial.IsBackground = true;
            thcheckserial.Start();
        }

        public string prjpath = @"./Template.rar";
        private void 保存ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bt_saveconfig_Click_1(sender,e);
            DirectoryInfo prjdir = Directory.CreateDirectory(@"./prj");
            SaveFileDialog save = new SaveFileDialog();
            save.Title = "保存工程";
            save.Filter = "CXKJ|*.CXKJ";// 默认的文件格式
            save.InitialDirectory = @"./prj";// AppDomain.CurrentDomain.BaseDirectory; // 默认的保存路径
            save.FileName = "CX_"+ DateTime.Now.ToString().Replace("/", "").Replace(":", "").Replace(" ", "");
            if (save.FileName != string.Empty)
            {
                
                save.ShowDialog();
                string path = save.FileName ;
                string.Format(@"./prj", path);
                if (!File.Exists(path)) // 判断文件是否存在，不存在就保存，存在就提示
                {
                    DirectoryInfo dd = Directory.CreateDirectory(@"./Template");
                    foreach (var item in dd.GetFiles())
                    {
                        File.Delete(item.FullName);
                    }

                    File.Copy(configpath, @"./Template/config.xml");
                    File.Copy(pixpath, @"./Template/pix_config.xml");
                    File.Copy(codepath, @"./Template/code.c");
                    File.Delete(path);
                    SharpZip.PackFiles(path, @"./Template");
                }
                else
                {
                    File.Delete(path);
                    DirectoryInfo dd = Directory.CreateDirectory(@"./Template");
                    foreach (var item in dd.GetFiles())
                    {
                        File.Delete(item.FullName);
                    }

                    File.Copy(configpath, @"./Template/config.xml");
                    File.Copy(pixpath, @"./Template/pix_config.xml");
                    File.Copy(codepath, @"./Template/code.c");
                    File.Delete(path);
                    SharpZip.PackFiles(path, @"./Template");
                    
                }

            }

            


        }

     

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
            DataSet TT1 = (DataSet)dataGridView1.DataSource;
            TT1.WriteXml(configpath);
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
            row["ALLMODE"] = cb_allmode.Text.ToString();
            row["DESET"] = cb_deset.Text.ToString();
            row["VSSET"] = cb_vsset.Text.ToString();
            row["HSSET"] = cb_hsset.Text.ToString();
            row["MIPISWAP"] = check_mipiswap.Checked.ToString();
            row["ODLR"] = check_odlr.Checked.ToString();
            row["MIPIMODE"] = cb_mipimode.Text.ToString();
            row["DUALPORT"] = check_dualport.Checked.ToString();

            dataSet.Rows.Add(row);
            dataSet.WriteXml(@"./pix_config.xml");
            File.WriteAllText(codepath, scintilla1.Text);
           
            
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
            tabControl1.SelectTab(tabPage2);
            bt_saveconfig_Click_1(sender, e);
            lb_display.ForeColor = Color.Black;
            lb_display.Text = "正在编译.....";
            File.Delete(APPPath);
            CodeCompile.lis.Clear();
            DoloadParamter();
            build();
           
        }
        private List<string> codeStrs = new List<string>();
        private void build()
        {
            Scintilla scintilla1 = this.scintilla1;
            int count = scintilla1.Lines.Count;
            this.codeStrs.Clear();
            for (int index = 0; index < count; ++index)
                this.codeStrs.Add(scintilla1.Lines[index].Text);
            new Thread(new ParameterizedThreadStart(this.CheckCode)).Start((object)scintilla1.Text);
        }

        private void CheckCode(object sender)
        {

            CodeCompile codecompile = new CodeCompile();
            if (CodeCompile.buildRunning == 1)
            {
                int num = (int)MessageBox.Show("正在编译中,请稍后重试!");
            }
            else
            {
               codecompile.DataReceived += new CodeCompile.EventHandle(this.Cb_DataReceived);
                codecompile.IinitCode(this.codeStrs);
                Console.WriteLine("编译完成");
            }
        }

        private void Cb_DataReceived(int what, object obj)
        {
                Invoke(new Action(() =>
                {
                    DataTable dataTable = new DataTable();
                    dataTable.Columns.Add("行号");
                    dataTable.Columns.Add("错误信息");
                    dataTable.Columns.Add("备注");
                    int count = CodeCompile.report.Count;
                    for (int index = 0; index < count; ++index)
                    {
                        DataRow row = dataTable.NewRow();
                        row["行号"] = (object)(CodeCompile.report[index].lines > 2 ? CodeCompile.report[index].lines+1 : CodeCompile.report[index].lines);
                        row["错误信息"] = (object)CodeCompile.report[index].reports;
                        this.scintilla1.Lines[CodeCompile.report[index].lines > 2 ? CodeCompile.report[index].lines-1  : CodeCompile.report[index].lines].MarkerAdd(0);
                        dataTable.Rows.Add(row);
                    }
                    this.dataGridView2.DataSource = (object)dataTable;
                    dataGridView2.RowHeadersVisible = false;
                    //禁止用户添加行
                    dataGridView2.AllowUserToAddRows = false;
                    //关闭自动排序
                    foreach (DataGridViewColumn column in dataGridView2.Columns)
                    {
                        //设置自动排序
                        column.SortMode = DataGridViewColumnSortMode.NotSortable;
                    }
                    if (dataGridView2.RowCount > 0)
                    {
                        int i = dataGridView2.RowCount ;
                        lb_display.ForeColor = Color.Red;
                        lb_display.Text = "编译错误" + i + "处";
                    }
                    else
                    {
                        lb_display.ForeColor = Color.Green;
                        lb_display.Text = "编译成功";
                        parent.pranum = (UInt16)CodeCompile.lis.Count;
                        parent.funclist = CodeCompile.lis;
                        CodeBuild codeBuild = new CodeBuild();
                        codeBuild.ParameterMake(child);
                        codeBuild.WriteFlag(parent);
                    }
                }));
        }
        #endregion

        private void 下载APPToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
        }

        private void tb_vfw_TextChanged(object sender, EventArgs e)
        {

        }

        private void bt_pwon_Click(object sender, EventArgs e)
        {
            int timeout = 0;
            byte[] receivebuf = new byte[20];
            if (!serialHelper.serial.IsOpen)
            {
                MessageBox.Show("串口没有打开");
            }
            else
            {
                byte[] temp = new byte[10];
                serialHelper.serial.DataReceived += new SerialDataReceivedEventHandler(_dataReceive);
                serialHelper.Order = (byte)SendType.COMMD;
                serialHelper.Devnum = 0x01;
                Array.Clear(receivebuf, 0, receivebuf.Length);
                serialHelper.SendPake(serialHelper.SendCommand(command.OPWER_ON, temp), temp.Length + 1);
                do
                    {
                        timeout++;
                        int i = serialHelper.serial.Read(receivebuf, 0, serialHelper.serial.BytesToRead);
                         if (receivebuf[0] == 0x55 && receivebuf[1] == 0xaa )
                        {
                            if (receivebuf[4] == 0x01) continue;
                            else if (receivebuf[4] == 0x02)
                            {
                                serialHelper.SendPake(serialHelper.SendCommand(command.OPWER_ON, temp), temp.Length + 1);
                                break ;
                            }
                        }
                    if (timeout > 500)
                    {
                        return;                       
                    }
                    } while (receivebuf[4] != 0x01);
            }
        }

        private void bt_pwoff_Click(object sender, EventArgs e)
        {
            int timeout = 0;
            byte[] receivebuf = new byte[20];
            if (!serialHelper.serial.IsOpen)
            {
                MessageBox.Show("串口没有打开");
            }
            else
            {
                byte[] temp = new byte[10];
               // serialHelper.serial.DataReceived += new SerialDataReceivedEventHandler(_dataReceive);
                serialHelper.Order = (byte)SendType.COMMD;
                serialHelper.Devnum = 0x01;
                Array.Clear(receivebuf, 0, receivebuf.Length);
                serialHelper.SendPake(serialHelper.SendCommand(command.OPWER_OFF, temp), temp.Length + 1);
                do
                {
                    timeout++;
                    int i = serialHelper.serial.Read(receivebuf, 0, serialHelper.serial.BytesToRead);
                    if (receivebuf[0] == 0x55 && receivebuf[1] == 0xaa)
                    {
                        if (receivebuf[4] == 0x01) continue;
                        else if (receivebuf[4] == 0x02)
                        {
                            serialHelper.SendPake(serialHelper.SendCommand(command.OPWER_OFF, temp), temp.Length + 1);
                            break;
                        }
                    }
                    if (timeout > 500)
                    {
                        return;
                    }
                } while (receivebuf[4] != 0x01);
            }
        }
        private void button1_Click_1(object sender, EventArgs e)
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
                MessageBox.Show("此串口拒绝访问");
                //throw;
            }

        }

        private void bt_up_Click(object sender, EventArgs e)
        {
            int timeout = 0;

            byte[] receivebuf = new byte[20];
            if (!serialHelper.serial.IsOpen)
            {
                MessageBox.Show("请打开串口");
            }
            else
            {
                byte[] temp = new byte[10];
                serialHelper.Order = (byte)SendType.COMMD;
                serialHelper.Devnum = 0x01;
                Array.Clear(receivebuf, 0, receivebuf.Length);
                serialHelper.SendPake(serialHelper.SendCommand(command.TURN_UP, temp), temp.Length + 1);
                do
                {
                    timeout++;
                    int i = serialHelper.serial.Read(receivebuf, 0, serialHelper.serial.BytesToRead);
                    if (receivebuf[0] == 0x55 && receivebuf[1] == 0xaa)
                    {
                        if (receivebuf[4] == 0x01) continue;
                        else if (receivebuf[4] == 0x02)
                        {
                            serialHelper.serial.Read(receivebuf, 0, serialHelper.serial.BytesToRead);
                            return;
                        }
                    }
                    if (timeout > 500)
                    {
                        return;
                    }
                } while (receivebuf[4] != 0x01);
            }

        }

        private void bt_down_Click(object sender, EventArgs e)
        {
            int timeout = 0;
            byte[] receivebuf = new byte[20];
            if (!serialHelper.serial.IsOpen)
            {
                MessageBox.Show("请打开串口");
            }
            else
            {
                byte[] temp = new byte[10];
                serialHelper.Order = (byte)SendType.COMMD;
                serialHelper.Devnum = 0x01;
                Array.Clear(receivebuf, 0, receivebuf.Length);
                serialHelper.SendPake(serialHelper.SendCommand(command.TURN_DOWN, temp), temp.Length + 1);
                do
                {
                    timeout++;
                    int i = serialHelper.serial.Read(receivebuf, 0, serialHelper.serial.BytesToRead);
                    if (receivebuf[0] == 0x55 && receivebuf[1] == 0xaa)
                    {
                        if (receivebuf[4] == 0x01) continue;
                        else if (receivebuf[4] == 0x02)
                        {
                            serialHelper.SendPake(serialHelper.SendCommand(command.TURN_DOWN, temp), temp.Length + 1);
                            return;
                        }
                    }
                    if (timeout > 500)
                    {
                        return;
                    }
                } while (receivebuf[4] != 0x01);
            }
        }

        private void bt_auto_Click(object sender, EventArgs e)
        {
            int timeout = 0;
            byte[] receivebuf = new byte[20];
            if (!serialHelper.serial.IsOpen)
            {
                MessageBox.Show("请打开串口");
            }
            else
            {

                byte[] temp = new byte[10];
                serialHelper.Order = (byte)SendType.COMMD;
                serialHelper.Devnum = 0x01;
                Array.Clear(receivebuf, 0, receivebuf.Length);
                serialHelper.SendPake(serialHelper.SendCommand(command.AUTO, temp), temp.Length + 1);
                do
                {
                    timeout++;
                    int i = serialHelper.serial.Read(receivebuf, 0, serialHelper.serial.BytesToRead);
                    if (receivebuf[0] == 0x55 && receivebuf[1] == 0xaa)
                    {
                        if (receivebuf[4] == 0x01) continue;
                        else if (receivebuf[4] == 0x02)
                        {
                            serialHelper.SendPake(serialHelper.SendCommand(command.AUTO, temp), temp.Length + 1);
                            return;
                        }
                    }
                    if (timeout > 500)
                    {
                        return;
                    }
                } while (receivebuf[4] != 0x01);
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
                //MessageBox.Show("此串口拒绝访问");
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

        private void 下载配置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bt_downloadapp_Click(sender, e);

        }
        public string APPPath = @"./test.bin";
        private void bt_downloadapp_Click(object sender, EventArgs e)
        {
            if (serialHelper.serial.IsOpen)
            {
                byte[] receivebuf = new byte[20];
                progressBar1.Visible = true;
                byte[] temp = new byte[10];
                temp = GetFilelenToByet(APPPath);


                serialHelper.Order = (byte)SendType.COMMD;
                serialHelper.Devnum = 0x01;
                Array.Clear(receivebuf, 0, receivebuf.Length);
                serialHelper.SendPake(serialHelper.SendCommand(command.SET_FLLE_LEN, temp), temp.Length + 1);
                do
                {
                    int i = serialHelper.serial.Read(receivebuf, 0, serialHelper.serial.BytesToRead);
                    if (receivebuf[0] == 0x55 && receivebuf[1] == 0xaa)
                    {
                        if (receivebuf[4] == 0x01) continue;
                        else if (receivebuf[4] == 0x02)
                        {
                            serialHelper.SendPake(serialHelper.SendCommand(command.SET_FLLE_LEN, temp), temp.Length + 1);
                            break;
                        }
                    }
                } while (receivebuf[4] != 0x01);
                Array.Clear(receivebuf, 0, receivebuf.Length);
                serialHelper.SendPake(serialHelper.SendCommand(command.SET_APP_FLAG, temp), temp.Length + 1);
                do
                {
                    int i = serialHelper.serial.Read(receivebuf, 0, serialHelper.serial.BytesToRead);
                    if (receivebuf[0] == 0x55 && receivebuf[1] == 0xaa)
                    {
                        if (receivebuf[4] == 0x01) continue;
                        else if (receivebuf[4] == 0x02)
                        {
                            serialHelper.SendPake(serialHelper.SendCommand(command.SET_APP_FLAG, temp), temp.Length + 1);
                            break;
                        }
                    }
                } while (receivebuf[4] != 0x01);
                Array.Clear(receivebuf, 0, receivebuf.Length);
                varclass.Ask = 0;
                Thread thsendapp = new Thread(sendapp);
                thsendapp.IsBackground = true;
                thsendapp.Start();

            }
            else
            {
                MessageBox.Show("请打开串口");
            }
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
            SharpZip.UnpackFiles(@"./Template.rar", @"./");
            DataInit();
            DoloadParamter();
            LoadDataFromFile(codepath);
            openfile.Dispose();
        }

        private void 另存为ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog save = new SaveFileDialog();
            save.Title = "工程另存为";
            save.Filter = "CXKJ|*.CXKJ";// 默认的文件格式
            save.InitialDirectory = @"./prj";// AppDomain.CurrentDomain.BaseDirectory; // 默认的保存路径
            save.FileName = "CX" + DateTime.Now.ToString().Replace("/", "").Replace(":", "").Replace(" ", "");
            save.ShowDialog();
            if (save.FileName != string.Empty)
            {
                string path = save.FileName;
                string.Format(@"./prj", path);
                if (!File.Exists(path)) // 判断文件是否存在，不存在就保存，存在就提示
                {
                    DirectoryInfo dd = Directory.CreateDirectory(@"./Template");
                    foreach (var item in dd.GetFiles())
                    {
                        File.Delete(item.FullName);
                    }

                    File.Copy(configpath, @"./Template/config.xml");
                    File.Copy(pixpath, @"./Template/pix_config.xml");
                    File.Copy(codepath, @"./Template/code.c");
                    File.Delete(path);
                    SharpZip.PackFiles(path, @"./Template");
                }
                else
                {
                    File.Delete(path);
                    File.Create(path);
                    // MessageBox.Show($"已经存在{path}文件了");
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
        public ColorPickerDialog colorPickerDialog;
        public ColorPickerDialog colorkuan ;
        public ColorPickerDialog colorback;
        private void textBox1_Click(object sender, EventArgs e)
        {
           
        }
      
        private void button1_Click_2(object sender, EventArgs e)
        {
           
        }
        #region lb_list_Click
        private void lb_list_Click(object sender, EventArgs e)
        {
            switch (lb_list.SelectedIndex)
            {
                case 0:
                    for (int i = 0; i < gb_imgset.Controls.Count; i++)
                    {
                        gb_imgset.Controls.RemoveAt(i);
                    }
                    gb_imgset.Text = "Color Seting";
                        lb_colorset = new Label();
                        lb_colorset.Location = new Point(50, 30);
                        lb_colorset.Text = "";
                        lb_colorset.BorderStyle = BorderStyle.FixedSingle;
                        lb_colorset.Width = 60;
                        lb_colorset.Height = 20;
                        lb_colorset.Visible = true;
                        lb_colorset.Enabled = true;

                        lb_colorset.Click += Lb_colorset_Click;
                        gb_imgset.Controls.Add(lb_colorset);
                     
                       
                    break;
                case 1:
                    for (int i = 0; i < gb_imgset.Controls.Count; i++)
                    {
                        gb_imgset.Controls.RemoveAt(i);
                    }
                        gb_imgset.Text = "frame Seting";
                        lb_kuancolor = new Label();
                        lb_kuancolor.Location = new Point(50, 30);
                        lb_kuancolor.Text = "";
                        lb_kuancolor.BorderStyle = BorderStyle.FixedSingle;
                        lb_kuancolor.Width = 60;
                        lb_kuancolor.Height = 20;
                        lb_kuancolor.Visible = true;
                        lb_kuancolor.Enabled = true;
                        lb_kuancolor.Name = "22";
                        lb_kuancolor.Click += Lb_kuancolor_Click;
                        gb_imgset.Controls.Add(lb_kuancolor);

                        lb_backcolor = new Label();
                        lb_backcolor.Location = new Point(200, 30);
                        lb_backcolor.Text = "";
                        lb_backcolor.BorderStyle = BorderStyle.FixedSingle;
                        lb_backcolor.Width = 60;
                        lb_backcolor.Height = 20;
                        lb_backcolor.Visible = true;
                        lb_backcolor.Enabled = true;
                        lb_backcolor.Name = "33";
                        lb_backcolor.Click += Lb_backcolor_Click;
                        gb_imgset.Controls.Add(lb_backcolor);         
                    break;

                case 2:
                    for (int i = 0; i < gb_imgset.Controls.Count; i++)
                    {
                        gb_imgset.Controls.RemoveAt(i);
                    }


                    gb_imgset.Text = "frame Seting";
                    lb_kuancolor = new Label();
                    lb_kuancolor.Location = new Point(50, 30);
                    lb_kuancolor.Text = "";
                    lb_kuancolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_kuancolor.Width = 60;
                    lb_kuancolor.Height = 20;
                    lb_kuancolor.Visible = true;
                    lb_kuancolor.Enabled = true;
                    lb_kuancolor.Name = "22";
                    lb_kuancolor.Click += Lb_kuancolor_Click;
                    gb_imgset.Controls.Add(lb_kuancolor);

                    lb_backcolor = new Label();
                    lb_backcolor.Location = new Point(200, 30);
                    lb_backcolor.Text = "";
                    lb_backcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_backcolor.Width = 60;
                    lb_backcolor.Height = 20;
                    lb_backcolor.Visible = true;
                    lb_backcolor.Enabled = true;
                    lb_backcolor.Name = "22";
                    lb_backcolor.Click += Lb_backcolor_Click;
                    gb_imgset.Controls.Add(lb_backcolor);
                    break;
                case 3:
                    for (int i = 0; i < gb_imgset.Controls.Count; i++)
                    {
                        gb_imgset.Controls.RemoveAt(i);
                    }

                    gb_imgset.Text = "Color Seting";
                    lb_kuancolor = new Label();
                    lb_kuancolor.Location = new Point(50, 30);
                    lb_kuancolor.Text = "";
                    lb_kuancolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_kuancolor.Width = 60;
                    lb_kuancolor.Height = 20;
                    lb_kuancolor.Visible = true;
                    lb_kuancolor.Enabled = true;
                    lb_kuancolor.Name = "22";
                    lb_kuancolor.Click += Lb_kuancolor_Click;
                    gb_imgset.Controls.Add(lb_kuancolor);

                    lb_backcolor = new Label();
                    lb_backcolor.Location = new Point(200, 30);
                    lb_backcolor.Text = "";
                    lb_backcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_backcolor.Width = 60;
                    lb_backcolor.Height = 20;
                    lb_backcolor.Visible = true;
                    lb_backcolor.Enabled = true;
                    lb_backcolor.Name = "22";
                    lb_backcolor.Click += Lb_backcolor_Click;
                    gb_imgset.Controls.Add(lb_backcolor);
                    break;
                case 4:

                    for (int i = 0; i < gb_imgset.Controls.Count; i++)
                    {
                        gb_imgset.Controls.RemoveAt(i);
                    }

                    gb_imgset.Text = "Color Seting";
                    lb_kuancolor = new Label();
                    lb_kuancolor.Location = new Point(50, 30);
                    lb_kuancolor.Text = "";
                    lb_kuancolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_kuancolor.Width = 60;
                    lb_kuancolor.Height = 20;
                    lb_kuancolor.Visible = true;
                    lb_kuancolor.Enabled = true;
                    lb_kuancolor.Name = "22";
                    lb_kuancolor.Click += Lb_kuancolor_Click;
                    gb_imgset.Controls.Add(lb_kuancolor);

                    lb_backcolor = new Label();
                    lb_backcolor.Location = new Point(200, 30);
                    lb_backcolor.Text = "";
                    lb_backcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_backcolor.Width = 60;
                    lb_backcolor.Height = 20;
                    lb_backcolor.Visible = true;
                    lb_backcolor.Enabled = true;
                    lb_backcolor.Name = "33";
                    lb_backcolor.Click += Lb_backcolor_Click;
                    gb_imgset.Controls.Add(lb_backcolor);
                    break;
                case 5:

                    for (int i = 0; i < gb_imgset.Controls.Count; i++)
                    {
                        gb_imgset.Controls.RemoveAt(i);
                    }
                    gb_imgset.Controls.Remove(lb_colorset);
                    gb_imgset.Text = "Color Seting";
                    lb_kuancolor = new Label();
                    lb_kuancolor.Location = new Point(50, 30);
                    lb_kuancolor.Text = "";
                    lb_kuancolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_kuancolor.Width = 60;
                    lb_kuancolor.Height = 20;
                    lb_kuancolor.Visible = true;
                    lb_kuancolor.Enabled = true;
                    lb_kuancolor.Name = "22";
                    lb_kuancolor.Click += Lb_kuancolor_Click;
                    gb_imgset.Controls.Add(lb_kuancolor);

                    lb_backcolor = new Label();
                    lb_backcolor.Location = new Point(200, 30);
                    lb_backcolor.Text = "";
                    lb_backcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_backcolor.Width = 60;
                    lb_backcolor.Height = 20;
                    lb_backcolor.Visible = true;
                    lb_backcolor.Enabled = true;
                    lb_backcolor.Name = "33";
                    lb_backcolor.Click += Lb_backcolor_Click;
                    gb_imgset.Controls.Add(lb_backcolor);
                    break;
                case 6:

                    for (int i = 0; i < gb_imgset.Controls.Count; i++)
                    {
                        gb_imgset.Controls.RemoveAt(i);
                    }
                    gb_imgset.Controls.Remove(lb_colorset);
                    gb_imgset.Text = "Color Seting";
                    lb_kuancolor = new Label();
                    lb_kuancolor.Location = new Point(50, 30);
                    lb_kuancolor.Text = "";
                    lb_kuancolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_kuancolor.Width = 60;
                    lb_kuancolor.Height = 20;
                    lb_kuancolor.Visible = true;
                    lb_kuancolor.Enabled = true;
                    lb_kuancolor.Name = "22";
                    lb_kuancolor.Click += Lb_kuancolor_Click;
                    gb_imgset.Controls.Add(lb_kuancolor);

                    lb_backcolor = new Label();
                    lb_backcolor.Location = new Point(200, 30);
                    lb_backcolor.Text = "";
                    lb_backcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_backcolor.Width = 60;
                    lb_backcolor.Height = 20;
                    lb_backcolor.Visible = true;
                    lb_backcolor.Enabled = true;
                    lb_backcolor.Name = "33";
                    lb_backcolor.Click += Lb_backcolor_Click;
                    gb_imgset.Controls.Add(lb_backcolor);
                    break;
                case 7:
                    for (int i = 0; i < gb_imgset.Controls.Count; i++)
                    {
                        gb_imgset.Controls.RemoveAt(i);
                    }

                    gb_imgset.Controls.Remove(lb_colorset);
                    gb_imgset.Text = "Color Seting";
                    lb_kuancolor = new Label();
                    lb_kuancolor.Location = new Point(50, 30);
                    lb_kuancolor.Text = "";
                    lb_kuancolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_kuancolor.Width = 60;
                    lb_kuancolor.Height = 20;
                    lb_kuancolor.Visible = true;
                    lb_kuancolor.Enabled = true;
                    lb_kuancolor.Name = "22";
                    lb_kuancolor.Click += Lb_kuancolor_Click;
                    gb_imgset.Controls.Add(lb_kuancolor);

                    lb_backcolor = new Label();
                    lb_backcolor.Location = new Point(200, 30);
                    lb_backcolor.Text = "";
                    lb_backcolor.BorderStyle = BorderStyle.FixedSingle;
                    lb_backcolor.Width = 60;
                    lb_backcolor.Height = 20;
                    lb_backcolor.Visible = true;
                    lb_backcolor.Enabled = true;
                    lb_backcolor.Name = "33";
                    lb_backcolor.Click += Lb_backcolor_Click;
                    gb_imgset.Controls.Add(lb_backcolor);
                    break;
               // default:  break; 
            }
        }

        #endregion
    }
}
