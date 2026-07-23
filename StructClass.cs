using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace CX900
{
    public static class StructClass
    {

        public static pMIPI_Para_Table pMIPItable;
        public static all_paramter all_Paramter;
        public static List<_symble> funclist;
       // [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public static DisModule[] Dismode=new DisModule[20];
        static StructClass()
        {

        }


        public struct _symble
        {
            public byte name;
            public byte num;
            public byte[] param;
        }




        public struct pMIPI_Para_Table
        {
            public string bLCDName; //用于记录该MIPI-LCD的分辨率
            public string bICName; //用于记录该MIPI-LCD的分辨率
            public string CodeZip; //用于记录该MIPI-LCD的分辨率
            public byte DUAL_MIPI_LCD;          //--- 声明该LCD是否为双MIPI屏(单MIPI屏时主板会输出两路相同的单MIPI信号以同时驱动两个屏)
            public byte DUAL_MIPI_CHANNEL_SWAP;     //--- 该双MIPI屏的两个通道的数据需要调换一下, 0不做调换, 1做调换
            public byte ODD_EVEN_nLEFT_RIGHT;     //---  声明该双MIPI屏是左右通道模式还是奇偶通道模式, 0表示左右通道(Left-Right Division), 1表示奇偶通道(Odd-Even Division)
            public UInt16 PCLK_Freq;     //PCLK Frequecy, 4~400的整数, 单位MHz
            public byte LANE_CNT;   // 4:4Lane, 8:8Lane, Others Reserved
            public byte V_DE;       // 1:DE 高电平有效, 0:DE 低电平有效
            public byte V_VS;       // 1:VS 高电平有效, 0:VS 低电平有效
            public byte V_HS;   // 1:HS 高电平有效, 0:HS 低电平有效
            public byte V_CLK;      // 1:clk 上升沿, 0:clk 下降沿,
            public byte Display_Mode;   // 显示模式 0:Non burst mode with sync pulses  1:Non burst mode with sync events 2:Burst mode 
            public UInt16 HACT_WIDTH;    //宽度
            public UInt16 VACT_WIDTH;    //高度
            public UInt16 HFP_WIDTH; //宽前肩
            public UInt16 HBP_WIDTH; //宽后肩
            public UInt16 HSW_WIDTH; //宽同步
            public UInt16 VFP_WIDTH; //高前肩
            public UInt16 VBP_WIDTH; //高后肩
            public UInt16 VSW_WIDTH;     //高同步
            public UInt16 NomalVCC1SET;
            public UInt16 LowperVCC1VOL;
            public UInt16 UperVCC1VOL;
            public UInt16 LowperVCC1MA;
            public UInt16 UperVCC1MA;

            public UInt16 NomalVCC2SET;
            public UInt16 LowperVCC2VOL;
            public UInt16 UperVCC2VOL;
            public UInt16 LowperVCC2MA;
            public UInt16 UperVCC2MA;

            public UInt16 NomalVCC3SET;
            public UInt16 LowperVCC3VOL;
            public UInt16 UperVCC3VOL;
            public UInt16 LowperVCC3MA;
            public UInt16 UperVCC3MA;


            public UInt16 NomalVCC4SET;
            public UInt16 LowperVCC4VOL;
            public UInt16 UperVCC4VOL;
            public UInt16 LowperVCC4MA;
            public UInt16 UperVCC4MA;

            public UInt16 NomalVCC5SET;
            public UInt16 LowperVCC5VOL;
            public UInt16 UperVCC5VOL;
            public UInt16 LowperVCC5MA;
            public UInt16 UperVCC5MA;

            public UInt16 NomalVCC6SET;
            public UInt16 LowperVCC6VOL;
            public UInt16 UperVCC6VOL;
            public UInt16 LowperVCC6MA;
            public UInt16 UperVCC6MA;

            public UInt16 NomalVSPSET;
            public UInt16 LowperVSPVOL;
            public UInt16 UperVSPVOL;
            public UInt16 LowperVSPMA;
            public UInt16 UperVSPMA;

            public UInt16 NomalVSNSET;
            public UInt16 LowperVSNVOL;
            public UInt16 UperVSNVOL;
            public UInt16 LowperVSNMA;
            public UInt16 UperVSNMA;

            public UInt16 NomalBLSET;
            public UInt16 LowperBLVOL;
            public UInt16 UperBLVOL;
            public UInt16 LowperBLMA;
            public UInt16 UperBLMA;
            public UInt16 BLMASET;






            public UInt32 VCC1Time;
            public UInt32 VCC2Time;
            public UInt32 VCC3Time;
            public UInt32 VCC4Time;
            public UInt32 VCC5Time;
            public UInt32 VCC6Time;
            public UInt32 VSPTime;
            public UInt32 VSNTime;
 
            public UInt16 Low_Delay;
            public UInt16 SIZE_OF_SHOW_MODE;     //显示的总画面个数
            public byte   AlarmFlag;
            public UInt16 TimeLock;
            public UInt16 Reserve1;
            public UInt16 Reserve2;
            public UInt16 Reserve3;
            public UInt16 Reserve4;
            public UInt16 Reserve5;
            public byte   MIPI_MODE;
            public byte   DW1_EN;
            public byte   DW2_EN;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
            public DisModule[] Dismode;
        }

        public struct DisModule
        {
            public UInt32 FuncName;
            public UInt32 Parameter1;
            public UInt32 Parameter2;
        }
            public  struct all_paramter
        {

            public pMIPI_Para_Table pMIPItable;
            public byte    flag;
            public UInt16  pranum;
            public UInt32 SleepPint;
            public UInt32 Sleepcount;
            public List<_symble> funclist;
            public List<_symble> SleepCODE;
        }
    }


   

}
