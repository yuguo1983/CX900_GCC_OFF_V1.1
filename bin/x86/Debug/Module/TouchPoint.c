#include "TouchPoint.h"

#define HINV 8  //行分屏 max 32
#define VINV 16 //列分屏 max 32
#define PointSize 4
#define Delay 40
#define Times 12

extern uint32_t XYCheck[8];
extern uint8_t KeyPowerPressed;
extern uint8_t KeyDownPressed;
extern void bsp_Idle(void);



uint16_t TP_POS_X, TP_POS_Y;
uint16_t TP_POS_X1, TP_POS_Y1;
extern uint8_t setInter;
uint8_t TP_Main(void)
{
    uint8_t i, temp;
    uint16_t Width = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH;
    uint16_t Hight = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH;
    ShowTpUI(Width, Hight, HINV, VINV);
    if(ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode == 3)MCU_CMD_Refresh(7);
    setInter = 0;
    for(i = 0; i < 8; i++)XYCheck[i] = 0;
    TP_POS_X1 = 0xFFFF;
    TP_POS_Y1 = 0xFFFF;
    TP_POS_X = 0xFFFF;
    TP_POS_Y = 0xFFFF;
    TP_Init();
    printf("TP Test Begin");
    while(1)
    {
        if(getInt(0))
        {
            temp = TP_Read(0, 0);
            if(temp == 1)
            {
                //				TP_POS_X = TP_POS_X%Width;
                //				TP_POS_Y = TP_POS_Y%Hight;
                TP_POS_X1 = (TP_POS_X1 == 0xFFFF) ? TP_POS_X : TP_POS_X1;
                TP_POS_Y1 = (TP_POS_Y1 == 0xFFFF) ? TP_POS_Y : TP_POS_Y1;
                ShowTpFill(Width, Hight, TP_POS_X, TP_POS_Y, HINV, VINV, 0xff00);
                GPU_DrawLine(TP_POS_X1, TP_POS_Y1, TP_POS_X, TP_POS_Y, PointSize, 0x000000ff);
                if(ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode == 3)MCU_CMD_Refresh(7);
                if(ShowTpCheck(HINV, VINV))
                {
                    KeyDownPressed = 1;
                    break;
                }
                TP_POS_X1 = TP_POS_X;
                TP_POS_Y1 = TP_POS_Y;
            }
            else if(temp == 0)
            {
                TP_POS_X1 = 0xFFFF;
                TP_POS_Y1 = 0xFFFF;
            }
						
        }
        if(KeyPowerPressed==1) break;
				bsp_Idle();
    }
    return 1;
}

void TP_Drow(void)
{
    uint16_t Width = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH;
    uint16_t Hight = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH;

    if(getInt(1))
    {
        if(TP_Read(0, 0) == 1)
        {
            TP_POS_X = TP_POS_X % Width;
            TP_POS_Y = TP_POS_Y % Hight;
            TP_POS_X1 = (TP_POS_X1 == 0xFFFF) ? TP_POS_X : TP_POS_X1;
            TP_POS_Y1 = (TP_POS_Y1 == 0xFFFF) ? TP_POS_Y : TP_POS_Y1;
            UG_DrawLine(TP_POS_X1, TP_POS_Y1, TP_POS_X, TP_POS_Y, PointSize, 0x000000ff);
            if(ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode == 3)MCU_CMD_Refresh(7);
            TP_POS_X1 = TP_POS_X;
            TP_POS_Y1 = TP_POS_Y;
        }
        else if(TP_Read(0, 0) == 0)
        {
            TP_POS_X1 = 0xFFFF;
            TP_POS_Y1 = 0xFFFF;
        }
    }
}

void TP_Init(void)
{
    uint8_t dataBuff[64];

    setInt(0);
    O_TP_VCC(1,3300);
    bsp_DelayMS(100);
    O_TP_VCC(0,0);
    bsp_DelayMS(100);
    O_TP_VCC(1,3300);
    setInt(1);
    bsp_DelayMS(100);
//    while(1)
//    {
//        if(I2C_Find(Delay) < 248)break;
//    }
//   if(I2C_Find(Delay) < 248)
//			printf("\r\n I2C TP have a address");
//	 else 
//			printf("\r\n I2C TP have not a address");
//    ///init tp
//    dataBuff[0] = 0x0F;
//    dataBuff[1] = 0x00;
//    dataBuff[2] = 0x80;
//    dataBuff[3] = 0x00;
//    I2C_Write(0xA6, dataBuff, 4, Delay);
//    I2C_Read(0xA6, dataBuff, 10, Delay);

}
#define addr  0x70
uint8_t TP_Read(uint8_t ts_x, uint8_t ts_y)
{
    	uint8_t data[64];
	uint16_t new_x0,new_y0;
	/////read tp data
data[0] = 0x01;
  I2C_Write(0x70,data,1,Delay);
  data[0] = 0x02;
  I2C_Write(0x70,data,1,Delay);
	I2C_Read(0x70,data,1,Delay);
	data[0] = 0x03;
	I2C_Write(0x70,data,1,Delay);
	I2C_Read(0x70,data,16,Delay);
		bsp_DelayMS(5);
	//printf(" data[0] = %x %x %x %x %x %x %x %x %x %x %x %x %x %x \n",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10],data[11],data[12],data[13]);
	if(data[1]&0x80 )
  {
//		printf(" data[0] = %x %x %x %x %x %x %x %x %x %x \n",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[60],data[61]);
		/*
				new_x0 = data[1];
				new_x0 = new_x0*16;
				new_x0 = new_x0+((data[3]&0xf0)>>4);   
			 
							
				new_y0 = data[2];
				new_y0 = new_y0*16;
				new_y0 = new_y0+(data[3]&0x0f);
		*/

//				    new_x0 = data[2];
//            new_x0 = new_x0+(data[1]&0xf0)*16;   //????X?标
//						//new_x0 = new_x0+((data[3]&0xf0)/16*256);
////						new_x0 = 1080 - new_x0;//???
//           
//            new_y0 = data[3];
//            new_y0 = new_y0+(data[1]&0xf)*256;   //????X?标    

				new_x0 = data[1]&0x0f;
			new_x0 = new_x0*256;
			new_x0 = new_x0+data[2];
						
			new_y0 = data[3];
			new_y0 = new_y0*256;
			new_y0 = new_y0+data[4];
		//	new_y0 = (new_y0-15)*ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH/1415;
//			printf("X = %d, Y = %d\n",new_x0,new_y0);
      if(new_x0 >= ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH  || new_y0 >= ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH)return 2; 
//      if(data[2] == 0x0) return 2;
			
			if(new_x0 == TP_POS_X && new_y0 == TP_POS_Y){
				TP_POS_X = 0xFFFF;
				TP_POS_Y = 0xFFFF;
				return 0;
			}else {
				  if(0==ts_x)
					{
						TP_POS_X = new_x0;
					}
					else if(1==ts_x)
					{
						TP_POS_X = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - new_x0;
					}
					else
					{
						TP_POS_X = new_x0;
					}
				
					if(0==ts_y)
					{
						TP_POS_Y = new_y0;
					}
					else if(1==ts_y)
					{
						TP_POS_Y = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH - new_y0;
					}
					else
					{
						TP_POS_Y = new_y0;
					}

					printf("X = %d, Y = %d\n",TP_POS_X,TP_POS_Y);
					return 1;
				}
      }
      else
      {
          TP_POS_X = 0xFFFF;
          TP_POS_Y = 0xFFFF;
            
          return 0;
      }
}

