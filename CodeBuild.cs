using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static CX900.StructClass;
using static ScintillaNET.Style;

namespace CX900
{
    public class CodeBuild
    {
        public CodeBuild()
        {
        }
        ~CodeBuild()
        {

        }
        private string APPPath = @"./app.bin";
        public void ParameterMake( StructClass.pMIPI_Para_Table str)
        {
            byte[] lcdname = new byte[29];
            Array.Clear(lcdname, 0, 29);    
            byte[] icname = new byte[29];      
            byte[] codename = new byte[29];
            lcdname= conventtobyte(str.bLCDName,29);
            icname = conventtobyte(str.bICName,29);
            codename = conventtobyte(str.CodeZip,29);
            byte[] pclk=new byte[2];
            pclk[1]     =Convert.ToByte(str.PCLK_Freq >> 8);
            pclk[0]     = Convert.ToByte(str.PCLK_Freq&0xff);

            byte[] hact= new byte[2];
            hact[1] = Convert.ToByte(str.HACT_WIDTH >> 8);
            hact[0] = Convert.ToByte(str.HACT_WIDTH & 0xff);

            byte[] vact = new byte[2];
            vact[1] = Convert.ToByte(str.VACT_WIDTH >> 8);
            vact[0] = Convert.ToByte(str.VACT_WIDTH & 0xff);

            byte[] hfp = new byte[2];
            hfp[1] = Convert.ToByte(str.HFP_WIDTH >> 8);
            hfp[0] = Convert.ToByte(str.HFP_WIDTH & 0xff);

            byte[] hbp = new byte[2];
            hbp[1] = Convert.ToByte(str.HBP_WIDTH >> 8);
            hbp[0] = Convert.ToByte(str.HBP_WIDTH & 0xff);

            byte[] hsp = new byte[2];
            hsp[1] = Convert.ToByte(str.HSW_WIDTH >> 8);
            hsp[0] = Convert.ToByte(str.HSW_WIDTH & 0xff);

            byte[] vfp = new byte[2];
            vfp[1] = Convert.ToByte(str.VFP_WIDTH >> 8);
            vfp[0] = Convert.ToByte(str.VFP_WIDTH & 0xff);

            byte[] vbp = new byte[2];
            vbp[1] = Convert.ToByte(str.VBP_WIDTH >> 8);
            vbp[0] = Convert.ToByte(str.VBP_WIDTH & 0xff);

            byte[] vsp = new byte[2];
            vsp[1] = Convert.ToByte(str.VSW_WIDTH >> 8);
            vsp[0] = Convert.ToByte(str.VSW_WIDTH & 0xff);

            byte[] nomalvcc1set = new byte[2];
            nomalvcc1set[1] = Convert.ToByte(str.NomalVCC1SET >> 8);
            nomalvcc1set[0] = Convert.ToByte(str.NomalVCC1SET & 0xff);

            byte[] lopervcc1vol = new byte[2];
            lopervcc1vol[1] = Convert.ToByte(str.LowperVCC1VOL >> 8);
            lopervcc1vol[0] = Convert.ToByte(str.LowperVCC1VOL & 0xff);

            byte[] uppervcc1vol = new byte[2];
            uppervcc1vol[1] = Convert.ToByte(str.UperVCC1VOL >> 8);
            uppervcc1vol[0] = Convert.ToByte(str.UperVCC1VOL & 0xff);

            byte[] lowpervcc1ma = new byte[2];
            lowpervcc1ma[1] = Convert.ToByte(str.LowperVCC1MA >> 8);
            lowpervcc1ma[0] = Convert.ToByte(str.LowperVCC1MA & 0xff);

            byte[] uppervcc1ma = new byte[2];
            uppervcc1ma[1] = Convert.ToByte(str.UperVCC1MA >> 8);
            uppervcc1ma[0] = Convert.ToByte(str.UperVCC1MA & 0xff);

            byte[] nomalvcc2set = new byte[2];
            nomalvcc2set[1] = Convert.ToByte(str.NomalVCC2SET >> 8);
            nomalvcc2set[0] = Convert.ToByte(str.NomalVCC2SET & 0xff);

            byte[] lopervcc2vol = new byte[2];
            lopervcc2vol[1] = Convert.ToByte(str.LowperVCC2VOL >> 8);
            lopervcc2vol[0] = Convert.ToByte(str.LowperVCC2VOL & 0xff);

            byte[] uppervcc2vol = new byte[2];
            uppervcc2vol[1] = Convert.ToByte(str.UperVCC2VOL >> 8);
            uppervcc2vol[0] = Convert.ToByte(str.UperVCC2VOL & 0xff);

            byte[] lowpervcc2ma = new byte[2];
            lowpervcc2ma[1] = Convert.ToByte(str.LowperVCC2MA >> 8);
            lowpervcc2ma[0] = Convert.ToByte(str.LowperVCC2MA & 0xff);

            byte[] uppervcc2ma = new byte[2];
            uppervcc2ma[1] = Convert.ToByte(str.UperVCC2MA >> 8);
            uppervcc2ma[0] = Convert.ToByte(str.UperVCC2MA & 0xff);


            byte[] nomalvcc3set = new byte[2];
            nomalvcc3set[1] = Convert.ToByte(str.NomalVCC3SET >> 8);
            nomalvcc3set[0] = Convert.ToByte(str.NomalVCC3SET & 0xff);

            byte[] lopervcc3vol = new byte[2];
            lopervcc3vol[1] = Convert.ToByte(str.LowperVCC3VOL >> 8);
            lopervcc3vol[0] = Convert.ToByte(str.LowperVCC3VOL & 0xff);

            byte[] uppervcc3vol = new byte[2];
            uppervcc3vol[1] = Convert.ToByte(str.UperVCC3VOL >> 8);
            uppervcc3vol[0] = Convert.ToByte(str.UperVCC3VOL & 0xff);

            byte[] lowpervcc3ma = new byte[2];
            lowpervcc3ma[1] = Convert.ToByte(str.LowperVCC3MA >> 8);
            lowpervcc3ma[0] = Convert.ToByte(str.LowperVCC3MA & 0xff);

            byte[] uppervcc3ma = new byte[2];
            uppervcc3ma[1] = Convert.ToByte(str.UperVCC3MA >> 8);
            uppervcc3ma[0] = Convert.ToByte(str.UperVCC3MA & 0xff);

            byte[] nomalvcc4set = new byte[2];
            nomalvcc4set[1] = Convert.ToByte(str.NomalVCC4SET >> 8);
            nomalvcc4set[0] = Convert.ToByte(str.NomalVCC4SET & 0xff);

            byte[] lopervcc4vol = new byte[2];
            lopervcc4vol[1] = Convert.ToByte(str.LowperVCC4VOL >> 8);
            lopervcc4vol[0] = Convert.ToByte(str.LowperVCC4VOL & 0xff);

            byte[] uppervcc4vol = new byte[2];
            uppervcc4vol[1] = Convert.ToByte(str.UperVCC4VOL >> 8);
            uppervcc4vol[0] = Convert.ToByte(str.UperVCC4VOL & 0xff);

            byte[] lowpervcc4ma = new byte[2];
            lowpervcc4ma[1] = Convert.ToByte(str.LowperVCC4MA >> 8);
            lowpervcc4ma[0] = Convert.ToByte(str.LowperVCC4MA & 0xff);

            byte[] uppervcc4ma = new byte[2];
            uppervcc4ma[1] = Convert.ToByte(str.UperVCC4MA >> 8);
            uppervcc4ma[0] = Convert.ToByte(str.UperVCC4MA & 0xff);

            byte[] nomalvcc5set = new byte[2];
            nomalvcc5set[1] = Convert.ToByte(str.NomalVCC5SET >> 8);
            nomalvcc5set[0] = Convert.ToByte(str.NomalVCC5SET & 0xff);

            byte[] lopervcc5vol = new byte[2];
            lopervcc5vol[1] = Convert.ToByte(str.LowperVCC5VOL >> 8);
            lopervcc5vol[0] = Convert.ToByte(str.LowperVCC5VOL & 0xff);

            byte[] uppervcc5vol = new byte[2];
            uppervcc5vol[1] = Convert.ToByte(str.UperVCC5VOL >> 8);
            uppervcc5vol[0] = Convert.ToByte(str.UperVCC5VOL & 0xff);

            byte[] lowpervcc5ma = new byte[2];
            lowpervcc5ma[1] = Convert.ToByte(str.LowperVCC5MA >> 8);
            lowpervcc5ma[0] = Convert.ToByte(str.LowperVCC5MA & 0xff);

            byte[] uppervcc5ma = new byte[2];
            uppervcc5ma[1] = Convert.ToByte(str.UperVCC5MA >> 8);
            uppervcc5ma[0] = Convert.ToByte(str.UperVCC5MA & 0xff);

            byte[] nomalvcc6set = new byte[2];
            nomalvcc6set[1] = Convert.ToByte(str.NomalVCC6SET >> 8);
            nomalvcc6set[0] = Convert.ToByte(str.NomalVCC6SET & 0xff);

            byte[] lopervcc6vol = new byte[2];
            lopervcc6vol[1] = Convert.ToByte(str.LowperVCC6VOL >> 8);
            lopervcc6vol[0] = Convert.ToByte(str.LowperVCC6VOL & 0xff);

            byte[] uppervcc6vol = new byte[2];
            uppervcc6vol[1] = Convert.ToByte(str.UperVCC6VOL >> 8);
            uppervcc6vol[0] = Convert.ToByte(str.UperVCC6VOL & 0xff);

            byte[] lowpervcc6ma = new byte[2];
            lowpervcc6ma[1] = Convert.ToByte(str.LowperVCC6MA >> 8);
            lowpervcc6ma[0] = Convert.ToByte(str.LowperVCC6MA & 0xff);

            byte[] uppervcc6ma = new byte[2];
            uppervcc6ma[1] = Convert.ToByte(str.UperVCC6MA >> 8);
            uppervcc6ma[0] = Convert.ToByte(str.UperVCC6MA & 0xff);

            byte[] nomalvspset = new byte[2];
            nomalvspset[1] = Convert.ToByte(str.NomalVSPSET >> 8);
            nomalvspset[0] = Convert.ToByte(str.NomalVSPSET & 0xff);

            byte[] lopervspvol = new byte[2];
            lopervspvol[1] = Convert.ToByte(str.LowperVSPVOL >> 8);
            lopervspvol[0] = Convert.ToByte(str.LowperVSPVOL & 0xff);

            byte[] uppervspvol = new byte[2];
            uppervspvol[1] = Convert.ToByte(str.UperVSPVOL >> 8);
            uppervspvol[0] = Convert.ToByte(str.UperVSPVOL & 0xff);

            byte[] lowpervspma = new byte[2];
            lowpervspma[1] = Convert.ToByte(str.LowperVSPMA >> 8);
            lowpervspma[0] = Convert.ToByte(str.LowperVSPMA & 0xff);

            byte[] uppervspma = new byte[2];
            uppervspma[1] = Convert.ToByte(str.UperVSPMA >> 8);
            uppervspma[0] = Convert.ToByte(str.UperVSPMA & 0xff);

            byte[] nomalvsnset = new byte[2];
            nomalvsnset[1] = Convert.ToByte(str.NomalVSNSET >> 8);
            nomalvsnset[0] = Convert.ToByte(str.NomalVSNSET & 0xff);

            byte[] lopervsnvol = new byte[2];
            lopervsnvol[1] = Convert.ToByte(str.LowperVSNVOL >> 8);
            lopervsnvol[0] = Convert.ToByte(str.LowperVSNVOL & 0xff);

            byte[] uppervsnvol = new byte[2];
            uppervsnvol[1] = Convert.ToByte(str.UperVSNVOL >> 8);
            uppervsnvol[0] = Convert.ToByte(str.UperVSNVOL & 0xff);

            byte[] lowpervsnma = new byte[2];
            lowpervsnma[1] = Convert.ToByte(str.LowperVSNMA >> 8);
            lowpervsnma[0] = Convert.ToByte(str.LowperVSNMA & 0xff);

            byte[] uppervsnma = new byte[2];
            uppervsnma[1] = Convert.ToByte(str.UperVSNMA >> 8);
            uppervsnma[0] = Convert.ToByte(str.UperVSNMA & 0xff);

            byte[] nomalblset = new byte[2];
            nomalblset[1] = Convert.ToByte(str.NomalBLSET >> 8);
            nomalblset[0] = Convert.ToByte(str.NomalVSNSET & 0xff);

            byte[] loperblvol = new byte[2];
            loperblvol[1] = Convert.ToByte(str.LowperBLVOL >> 8);
            loperblvol[0] = Convert.ToByte(str.LowperBLVOL & 0xff);

            byte[] upperblvol = new byte[2];
            upperblvol[1] = Convert.ToByte(str.UperBLVOL >> 8);
            upperblvol[0] = Convert.ToByte(str.UperBLVOL & 0xff);

            byte[] lowperblma = new byte[2];
            lowperblma[1] = Convert.ToByte(str.LowperBLMA >> 8);
            lowperblma[0] = Convert.ToByte(str.LowperBLMA & 0xff);

            byte[] upperblma = new byte[2];
            upperblma[1] = Convert.ToByte(str.UperBLMA >> 8);
            upperblma[0] = Convert.ToByte(str.UperBLMA & 0xff);

            byte[] blmaset = new byte[2];
            blmaset[1] = Convert.ToByte(str.BLMASET >> 8);
            blmaset[0] = Convert.ToByte(str.BLMASET & 0xff);



            byte[] low_delay = new byte[2];
            low_delay[1] = Convert.ToByte(str.Low_Delay >> 8);
            low_delay[0] = Convert.ToByte(str.Low_Delay & 0xff);


            byte[] sizeofshowdome = new byte[2];//画面总数量
            sizeofshowdome[1] = Convert.ToByte(str.SIZE_OF_SHOW_MODE >> 8);
            sizeofshowdome[0] = Convert.ToByte(str.SIZE_OF_SHOW_MODE & 0xff);
            byte[] dismodule = new byte[240];
            Array.Clear(dismodule,0,dismodule.Length);
            for (int i1 = 0; i1< dismodule.Length;i1++ )
            {
                dismodule[i1] = 0x55;
            }
            try
            {
                FileStream fs = new FileStream(APPPath, FileMode.Create);
                BinaryWriter usre = new BinaryWriter(fs);
                usre.Write(lcdname);
                usre.Write(icname);
                usre.Write(codename);
                usre.Write(str.DUAL_MIPI_LCD);               
                usre.Write(str.DUAL_MIPI_CHANNEL_SWAP);
                usre.Write(str.ODD_EVEN_nLEFT_RIGHT);
                usre.Write(pclk);
                usre.Write(str.LANE_CNT);
                usre.Write(str.V_DE);
                usre.Write(str.V_VS);
                usre.Write(str.V_HS);
                usre.Write(str.V_CLK);
                usre.Write(str.Display_Mode);
                usre.Write(hact);
                usre.Write(vact);
                usre.Write(hfp);
                usre.Write(hbp);
                usre.Write(hsp);
                usre.Write(vfp);
                usre.Write(vbp);
                usre.Write(vsp);
                usre.Write(nomalvcc1set);
                usre.Write(lopervcc1vol);
                usre.Write(uppervcc1vol);
                usre.Write(lowpervcc1ma);
                usre.Write(uppervcc1ma);
                usre.Write(nomalvcc2set);
                usre.Write(lopervcc2vol);
                usre.Write(uppervcc2vol);
                usre.Write(lowpervcc2ma);
                usre.Write(uppervcc2ma);

                usre.Write(nomalvcc3set);
                usre.Write(lopervcc3vol);
                usre.Write(uppervcc3vol);
                usre.Write(lowpervcc3ma);
                usre.Write(uppervcc3ma);

                usre.Write(nomalvcc4set);
                usre.Write(lopervcc4vol);
                usre.Write(uppervcc4vol);
                usre.Write(lowpervcc4ma);
                usre.Write(uppervcc4ma);

                usre.Write(nomalvcc5set);
                usre.Write(lopervcc5vol);
                usre.Write(uppervcc5vol);
                usre.Write(lowpervcc5ma);
                usre.Write(uppervcc5ma);

                usre.Write(nomalvcc6set);
                usre.Write(lopervcc6vol);
                usre.Write(uppervcc6vol);
                usre.Write(lowpervcc6ma);
                usre.Write(uppervcc6ma);

                usre.Write(nomalvspset);
                usre.Write(lopervspvol);
                usre.Write(uppervspvol);
                usre.Write(lowpervspma);
                usre.Write(uppervspma);

                usre.Write(nomalvsnset);
                usre.Write(lopervsnvol);
                usre.Write(uppervsnvol);
                usre.Write(lowpervsnma);
                usre.Write(uppervsnma);

                usre.Write(nomalblset);
                usre.Write(loperblvol);
                usre.Write(upperblvol);
                usre.Write(lowperblma);
                usre.Write(upperblma);
                usre.Write(blmaset);



                byte[] vcc1time = new byte[4];
                byte[] vcc2time = new byte[4];
                byte[] vcc3time = new byte[4];
                byte[] vcc4time = new byte[4];
                byte[] vcc5time = new byte[4];
                byte[] vcc6time = new byte[4];
                byte[] vsptime =  new byte[4];
                byte[] vsntime =  new byte[4];
                vcc1time[3] = Convert.ToByte(str.VCC1Time >> 24 & 0xff);
                vcc1time[2] = Convert.ToByte(str.VCC1Time >> 16 & 0xff);
                vcc1time[1] = Convert.ToByte(str.VCC1Time >> 8 & 0xff);
                vcc1time[0] = Convert.ToByte(str.VCC1Time >> 0  & 0xff);

                vcc2time[3] = Convert.ToByte(str.VCC2Time >> 24 & 0xff);
                vcc2time[2] = Convert.ToByte(str.VCC2Time >> 16 & 0xff);
                vcc2time[1] = Convert.ToByte(str.VCC2Time >> 8 & 0xff);
                vcc2time[0] = Convert.ToByte(str.VCC2Time >> 0 & 0xff);

                vcc3time[3] = Convert.ToByte(str.VCC3Time >> 24 & 0xff);
                vcc3time[2] = Convert.ToByte(str.VCC3Time >> 16 & 0xff);
                vcc3time[1] = Convert.ToByte(str.VCC3Time >> 8 & 0xff);
                vcc3time[0] = Convert.ToByte(str.VCC3Time >> 0 & 0xff);

                vcc4time[3] = Convert.ToByte(str.VCC4Time >> 24 & 0xff);
                vcc4time[2] = Convert.ToByte(str.VCC4Time >> 16 & 0xff);
                vcc4time[1] = Convert.ToByte(str.VCC4Time >> 8 & 0xff);
                vcc4time[0] = Convert.ToByte(str.VCC4Time >> 0 & 0xff);

                vcc5time[3] = Convert.ToByte(str.VCC5Time >> 24 & 0xff);
                vcc5time[2] = Convert.ToByte(str.VCC5Time >> 16 & 0xff);
                vcc5time[1] = Convert.ToByte(str.VCC5Time >> 8 & 0xff);
                vcc5time[0] = Convert.ToByte(str.VCC5Time >> 0 & 0xff);

                vcc6time[3] = Convert.ToByte(str.VCC6Time >> 24 & 0xff);
                vcc6time[2] = Convert.ToByte(str.VCC6Time >> 16 & 0xff);
                vcc6time[1] = Convert.ToByte(str.VCC6Time >> 8 & 0xff);
                vcc6time[0] = Convert.ToByte(str.VCC6Time >> 0 & 0xff);

                vsptime[3] = Convert.ToByte(str.VSPTime >> 24 & 0xff);
                vsptime[2] = Convert.ToByte(str.VSPTime >> 16 & 0xff);
                vsptime[1] = Convert.ToByte(str.VSPTime >> 8 & 0xff);
                vsptime[0] = Convert.ToByte(str.VSPTime >> 0 & 0xff);

                vsntime[3] = Convert.ToByte(str.VSNTime >> 24 & 0xff);
                vsntime[2] = Convert.ToByte(str.VSNTime >> 16 & 0xff);
                vsntime[1] = Convert.ToByte(str.VSNTime >> 8 & 0xff);
                vsntime[0] = Convert.ToByte(str.VSNTime >> 0 & 0xff);
                

                usre.Write(vcc1time);
                usre.Write(vcc2time);
                usre.Write(vcc3time);
                usre.Write(vcc4time);
                usre.Write(vcc5time);
                usre.Write(vcc6time);
                usre.Write(vsptime);
                usre.Write(vsntime);

                usre.Write((byte)0);
                usre.Write((byte)0);
                usre.Write(low_delay);
                
                usre.Write(sizeofshowdome);
                usre.Write(str.AlarmFlag);

                byte[] timelock = new byte[2];
                timelock[1] = Convert.ToByte(str.TimeLock>>  8&  0xff);
                timelock[0] = Convert.ToByte(str.TimeLock >> 0 & 0xff);
                usre.Write((byte)0);
                usre.Write(timelock);
                byte[] reserve1 = new byte[2];
                byte[] reserve2 = new byte[2];
                byte[] reserve3 = new byte[2];
                byte[] reserve4 = new byte[2];
                byte[] reserve5 = new byte[2];
                reserve1[1] = Convert.ToByte(str.Reserve1 >> 8 & 0xff);
                reserve1[0] = Convert.ToByte(str.Reserve1 >> 0 & 0xff);

                reserve2[1] = Convert.ToByte(str.Reserve2 >> 8 & 0xff);
                reserve2[0] = Convert.ToByte(str.Reserve2 >> 0 & 0xff);

                reserve3[1] = Convert.ToByte(str.Reserve3 >> 8 & 0xff);
                reserve3[0] = Convert.ToByte(str.Reserve3 >> 0 & 0xff);

                reserve4[1] = Convert.ToByte(str.Reserve4 >> 8 & 0xff);
                reserve4[0] = Convert.ToByte(str.Reserve4 >> 0 & 0xff);

                reserve5[1] = Convert.ToByte(str.Reserve5 >> 8 & 0xff);
                reserve5[0] = Convert.ToByte(str.Reserve5 >> 0 & 0xff);

                usre.Write(reserve1);
                usre.Write(reserve2);
                usre.Write(reserve3);
                usre.Write(reserve4);
                usre.Write(reserve5);

                usre.Write(str.MIPI_MODE);
                usre.Write(str.DW1_EN);
                usre.Write(str.DW1_EN);
                usre.Write((byte)0);
                usre.Write((byte)0);
                usre.Write((byte)11);
                if (str.Dismode.Length > 20)
                {
                    MessageBox.Show("超出画面最大上限！！！");
                }
                else
                {
                    foreach (var item in str.Dismode)
                    {
                        usre.Write(item.FuncName);
                        usre.Write(item.Parameter1);
                        usre.Write(item.Parameter2);
                    }
                }
                
                
               
                
                usre.Close();
                fs.Close();

            }
            catch (Exception)
            {
                MessageBox.Show("文件正在占用");
            }
        }

        public StructClass._symble FuncBody = new _symble();
       
        public void WriteFlag(all_paramter all_Paramter)
        {
           FileStream fs = new FileStream(APPPath, FileMode.Append);
            BinaryWriter writer = new BinaryWriter(fs);
            writer.Write((byte)all_Paramter.flag); 
            byte[] pram = new byte[2];
            writer.Write((byte)0x00);
            pram[1] = Convert.ToByte( all_Paramter.pranum >> 8);
            pram[0] = Convert.ToByte(all_Paramter.pranum&0xff);
            writer.Write(pram);
            writer.Write(all_Paramter.SleepPint);
            writer.Write(all_Paramter.Sleepcount);
            for(int i=0;i< all_Paramter.funclist.Count;i++)
            {
                writer.Write((byte)all_Paramter.funclist[i].name);
                writer.Write((byte)all_Paramter.funclist[i].num);
                writer.Write((byte)0x00);
                writer.Write((byte)0x00);
                byte[] pr = new byte[4];
                Array.Clear(pr, 0, 4);
                pr = all_Paramter.funclist[i].param;
                writer.Write(pr);     
            }   
            foreach (var item in all_Paramter.SleepCODE)
            {
                writer.Write((byte)item.name);
                writer.Write((byte)item.num);
                writer.Write((byte)0x00);
                writer.Write((byte)0x00);
                byte[] pr = new byte[4];
                Array.Clear(pr, 0, 4);
                pr = item.param;
                writer.Write(pr);
            }
            writer.Close();
            fs.Close();
        }

        public byte[] conventtobyte(string str,int len)
        {
            byte[] temp = new byte[len];

            int length= str.Length;
            byte[] temp1 = new byte[length];
            temp1= Encoding.ASCII.GetBytes(str);
            if (length > len)
            {
                Debug.Write("\r\n字符大于数组！！！");
            }
            for (int i = 0; i < length; i++)
            {
                temp[i] = temp1[i];
            }
            temp[length] = 0x0d;
            for (int i = length+1; i < len-1; i++)
            {
                temp[i] = 0x00;
            }
           
            return temp;
        }


    }
}
