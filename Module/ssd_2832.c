#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include "ssd_2832.h"
#include "common.h"
#include "log.h"
#include "malloc.h"
#include "user_config.h"

#define  SSD2832_CS_PIN    GPIO_PIN_4
#define  SSD2832_CS_PORT   GPIOA

#define  SSD2832_SCK_PIN    GPIO_PIN_5
#define  SSD2832_SCK_PORT   GPIOA

#define  SSD2832_MOSI_PIN    GPIO_PIN_7
#define  SSD2832_MOSI_PORT   GPIOA

#define  SSD2832_MISO_PIN    GPIO_PIN_6
#define  SSD2832_MISO_PORT   GPIOA

#define  SSD2832_RST_PIN    GPIO_PIN_2
#define  SSD2832_RST_PORT   GPIOC

#define  SSD2832_CDPHYSEL_PIN    GPIO_PIN_1
#define  SSD2832_CDPHYSEL_PORT   GPIOB

#define  SSD2832_8B24B_PIN    GPIO_PIN_12
#define  SSD2832_8B24B_PORT   GPIOB



#define  SSD2832_CS_L()   	GPIO_BC(SSD2832_CS_PORT) = (uint32_t)SSD2832_CS_PIN;
#define  SSD2832_CS_H()    	GPIO_BOP(SSD2832_CS_PORT) = (uint32_t)SSD2832_CS_PIN;

#define  SSD2832_SCK_L()   	GPIO_BC(SSD2832_SCK_PORT) = (uint32_t)SSD2832_SCK_PIN;
#define  SSD2832_SCK_H()   	GPIO_BOP(SSD2832_SCK_PORT) = (uint32_t)SSD2832_SCK_PIN;

#define  SSD2832_MOSI_L()   	GPIO_BC(SSD2832_MOSI_PORT) = (uint32_t)SSD2832_MOSI_PIN;
#define  SSD2832_MOSI_H()   	GPIO_BOP(SSD2832_MOSI_PORT) = (uint32_t)SSD2832_MOSI_PIN;

#define  SSD2832_RST_L()   	GPIO_BC(SSD2832_RST_PORT) = (uint32_t)SSD2832_RST_PIN;
#define  SSD2832_RST_H()   	GPIO_BOP(SSD2832_RST_PORT) = (uint32_t)SSD2832_RST_PIN;

#define  SSD2832_CDPHYSEL_L()   	GPIO_BC(SSD2832_CDPHYSEL_PORT) = (uint32_t)SSD2832_CDPHYSEL_PIN;
#define  SSD2832_CDPHYSEL_H()   	GPIO_BOP(SSD2832_CDPHYSEL_PORT) = (uint32_t)SSD2832_CDPHYSEL_PIN;

#define  SSD2832_8B24B_L()   	GPIO_BC(SSD2832_8B24B_PORT) = (uint32_t)SSD2832_8B24B_PIN;
#define  SSD2832_8B24B_H()   	GPIO_BOP(SSD2832_8B24B_PORT) = (uint32_t)SSD2832_8B24B_PIN;


#define  SSD2832_MOSI_READ()   gpio_input_bit_get(SSD2832_MISO_PORT,SSD2832_MISO_PIN)

#define SDD2828_SPI_WR_DELAY  {bsp_DelayUS(8);}

int mipi_write_regs(struct mipi_port *port, uint8_t *frame,uint32_t len);
int mipi_read_regs(struct mipi_port *port, uint8_t *frame,uint32_t len);


#define SSD_SPI_BUFF_LEN (256)

static unsigned char bridge_write_buff[SSD_SPI_BUFF_LEN] = {0};
static uint32_t bridge_mem_reg_b6[BRIDGE_PORT_COUNT] = {0,0};
static uint32_t bridge_mem_reg_b7[BRIDGE_PORT_COUNT] = {0,0};
static uint32_t bridge_mem_reg_bd[BRIDGE_PORT_COUNT] = {0,0};
static uint32_t bridge_mem_reg_de[BRIDGE_PORT_COUNT] = {0,0};

volatile uint8_t vblank_changeFrom = 0;

void SSD2832_GPIO_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	
	gpio_init(SSD2832_CS_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SSD2832_CS_PIN);
	gpio_init(SSD2832_SCK_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SSD2832_SCK_PIN);
	gpio_init(SSD2832_MOSI_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SSD2832_MOSI_PIN);
	gpio_init(SSD2832_RST_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SSD2832_RST_PIN);
	gpio_init(SSD2832_CDPHYSEL_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SSD2832_CDPHYSEL_PIN);
	gpio_init(SSD2832_8B24B_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SSD2832_8B24B_PIN);
	gpio_init(SSD2832_MISO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, SSD2832_MISO_PIN);
	gpio_bit_set(SSD2832_RST_PORT, SSD2832_RST_PIN);
	gpio_bit_reset(SSD2832_8B24B_PORT, SSD2832_8B24B_PIN); // 0:SPI-24BIT  1:SPI-8BIT
	
	gpio_bit_reset(SSD2832_CDPHYSEL_PORT, SSD2832_CDPHYSEL_PIN);//0:C PHY  1:D PHY 
	
	gpio_bit_set(SSD2832_CS_PORT, SSD2832_CS_PIN);
	gpio_bit_set(SSD2832_SCK_PORT, SSD2832_SCK_PIN);
	gpio_bit_set(SSD2832_MOSI_PORT, SSD2832_MOSI_PIN);	

	
}




void *malloc(uint32_t size)
{
	return	mymalloc(SRAMIN, size);	
}

void free(void * buff)
{
	myfree(SRAMIN,buff);
}

void usleep(uint32_t us)
{
	bsp_DelayUS(us);
}

void bridge_select_phy(uint8_t value)
{
if(value==0)
{
	SSD2832_CDPHYSEL_L();
}else 
{
	SSD2832_CDPHYSEL_H();
}
}


void SSD2832_Write_Command(uint8_t cmd)
{
    uint8_t i;
//    SSD2832_CS_H();
//    SSD2832_MOSI_H();
//    SSD2832_SCK_H();
//    SDD2828_SPI_WR_DELAY;

//    SSD2832_CS_L();
//    SDD2828_SPI_WR_DELAY;
//    SSD2832_MOSI_L(); 
//    SDD2828_SPI_WR_DELAY;
//    SSD2832_SCK_L();
//    SDD2828_SPI_WR_DELAY;
//    SSD2832_SCK_H(); 
    for (i = 0; i < 8; i++)
    {
        if (cmd & 0x80)
        {
            SSD2832_MOSI_H();
        }
        else
        {
            SSD2832_MOSI_L();
        }
        cmd <<= 1;
        SSD2832_SCK_L();
        SDD2828_SPI_WR_DELAY;
        SSD2832_SCK_H();
        SDD2828_SPI_WR_DELAY;
    }
    SSD2832_MOSI_H();
    SDD2828_SPI_WR_DELAY;
//    SSD2832_CS_H();
}



void SSD2832_Write_Data(uint8_t data)
{
    uint8_t i;
//    SSD2832_CS_H();
//    SSD2832_MOSI_H();
//    SSD2832_SCK_H();
//    SDD2828_SPI_WR_DELAY;

//    SSD2832_CS_L();
//    SDD2828_SPI_WR_DELAY;
//    SSD2832_MOSI_H(); 
//    SDD2828_SPI_WR_DELAY;
//    SSD2832_SCK_L();
//    SDD2828_SPI_WR_DELAY;
//    SSD2832_SCK_H(); 
    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            SSD2832_MOSI_H();
        }
        else
        {
            SSD2832_MOSI_L();
        }
        data <<= 1;
        SSD2832_SCK_L();
        SDD2828_SPI_WR_DELAY;
        SSD2832_SCK_H();
        SDD2828_SPI_WR_DELAY;
    }
    SSD2832_MOSI_H();
    SDD2828_SPI_WR_DELAY;
//    SSD2832_CS_H();
}

uint8_t  SSD2832_Read(void)
{
		uint8_t i;
    uint8_t tmp = 0;
    SSD2832_CS_L();
    SDD2828_SPI_WR_DELAY;
    for (i = 0; i < 8; i++)
    {
        SSD2832_SCK_L();
        SDD2828_SPI_WR_DELAY;
        SSD2832_SCK_H();
        SDD2828_SPI_WR_DELAY;
        tmp <<= 1;
        if (SSD2832_MOSI_READ())
        {
            tmp |= 0x01;
        } 
    }
    SSD2832_CS_H();
    return tmp;
}


int bridge_a_spi_read(unsigned char *frame,int len)
{
	if((len>0)&&(frame!=NULL))
	{
  for(int i=0;i<len;i++)
	{
	   frame[i]=SSD2832_Read();
	}
	 return 1;
	}
	return -1;
}

int bridge_a_spi_write(unsigned char *frame,int len)
{
	if((len>0)&&(frame!=NULL))
	{
		for(int i=0;i<len;i++)
		{
			SSD2832_Write_Data(frame[i]);
		}
		return 1;
	}
	return -1;  
}




/******************************************************************************/
/// Description:return bridge reg buffer
/// @note:
/// @param reg address
/// @param output:reg buffer value
/// @return
/******************************************************************************/
uint32_t bridge_read_mem_reg(unsigned char reg)
{
    if(reg == 0xB6)
        return bridge_mem_reg_b6[0];
	
    if(reg == 0xB7)
        return bridge_mem_reg_b7[0];
	
    if(reg == 0xBD)
        return bridge_mem_reg_bd[0];
	
    if(reg == 0xDE)
        return bridge_mem_reg_de[0];
	
    return 0;
}



/******************************************************************************/
/// Description:static spi read from ssd2829
/// @note:
/// @param input:len,opt
/// @param output:data
/// @return
/******************************************************************************/
static int bridge_spi_read(unsigned char *frame,uint32_t len)
{
    int ret = 0;
		ret = bridge_a_spi_read(frame,len);
    if(ret > 0)
    {
        return 1;
    }

    log_err("fail\n");
    return -1;
}
/******************************************************************************/
/// Description:ssd2829 write start
/// @note:
/// @param input:data,len
/// @param output:null
/// @return
/******************************************************************************/
static int bridge_spi_write(unsigned char *frame,uint32_t len)
{
    int ret = 0;


		SSD2832_CS_L();		
		ret = bridge_a_spi_write(frame,len);
		SSD2832_CS_H();		
    if(ret > 0)
    {
        return 1;
    }

    log_err("fail\n");
    return -1;
}
/******************************************************************************/
/// Description:ssd2829 read data
/// @note:ssd2829 read data
/// @param input:data,len
/// @param output:null
/// @return value
/******************************************************************************/
static int bridge_spi_read_data(unsigned char *frame,uint32_t len)
{
    int i = 0;
    int ret = 0;
    unsigned char* data_buffer =(unsigned char*)malloc(len + 1);

    for(i = 0; i < len; i += 2)
    {
        bridge_write_buff[0] = 0x73;
        ret = bridge_spi_write(bridge_write_buff,1);		
        ret = bridge_spi_read(frame + i,2);
    }
    return ret;
}
/******************************************************************************/
/// Description:ssd2829 write command
/// @note:ssd2829 write command,use 24Bit mode
/// @param input:addr
/// @param output:null
/// @return value
/******************************************************************************/
static int bridge_write_cmd(unsigned char addr)
{
    int i = 0;

    bridge_write_buff[i++] = 0x70;
    bridge_write_buff[i++] = 0x00;
    bridge_write_buff[i++] = addr;

    return bridge_spi_write(bridge_write_buff,i);
}
/******************************************************************************/
/// Description:ssd2829 write data
/// @note:ssd2829 write data,use 24Bit mode,MSB First
/// @param input:data,len
/// @param output:null
/// @return value
/******************************************************************************/
static int bridge_write_data(unsigned char *frame,uint32_t len)
{
    int i = 0;
    int ret = 0;
    int count = 0;

    count = len % 2;   
    for(i = 0; i < len - count; i += 2)
    {
        bridge_write_buff[0] = 0x72;
    	bridge_write_buff[1] = *frame++;
        bridge_write_buff[2] = *frame++;

        ret = bridge_spi_write(bridge_write_buff,3);
    }

	if(count)
	{
        bridge_write_buff[0] = 0x72;
    	bridge_write_buff[1] = 0x00;
        bridge_write_buff[2] = *frame;

        ret = bridge_spi_write(bridge_write_buff,3);
	}
    return ret;
}


void Read_SSD2832_Id(void)
{
	uint8_t temp_buf[4];
	temp_buf[0]=0x00;
	temp_buf[1]=0xfa;
	bridge_write_cmd(0xd4);
	bridge_write_data(temp_buf,2);
	bridge_write_cmd(0xb0);
	bridge_write_cmd(0xfa);
	bridge_spi_read(temp_buf,4);
	for(int i=0;i<4;i++)
	log_info("ID: 0x%x",temp_buf[i]);
	
}


/******************************************************************************/
/// Description:ssd2829 write data
/// @note:ssd2829 write data,use 24Bit mode,LSB First
/// @param input:data,len
/// @param output:null
/// @return value
/******************************************************************************/
static int bridge_write_lsb_data(unsigned char *frame,uint32_t len)
{
    int i = 0;
    int ret = 0;
    int count = 0;

    count = len % 2;

    for(i = 0; i < len - count; i += 2)
    {
        bridge_write_buff[0] = 0x72;
        bridge_write_buff[2] = *frame++;
    	bridge_write_buff[1] = *frame++;

        ret = bridge_spi_write(bridge_write_buff,3);
    }

	if(count)
	{
        bridge_write_buff[0] = 0x72;
        bridge_write_buff[2] = *frame;
    	bridge_write_buff[1] = 0x00;

        ret = bridge_spi_write(bridge_write_buff,3);
	}
    return ret;
}
/******************************************************************************/
/// Description:ssd2829 write register
/// @note:ssd2829 write register(32BIT)
/// @param input:data,len
/// @param output:null
/// @return value
/******************************************************************************/
int bridge_write_reg_32bit(unsigned char addr,uint32_t tmp)
{
    int ret = 0;
    unsigned char tmp_buff[4] = {0};

    if(addr == 0xB6)
        bridge_mem_reg_b6[0] = tmp;

    if(addr == 0xB7)
        bridge_mem_reg_b7[0] = tmp;

    if(addr == 0xDE)
        bridge_mem_reg_de[0] = tmp;

	tmp_buff[2] = (tmp >> 24) & 0xFF;
	tmp_buff[3] = (tmp >> 16) & 0xFF;
	tmp_buff[0] = (tmp >> 8) & 0xFF;
	tmp_buff[1] = (tmp >> 0) & 0xFF;
	
	ret = bridge_write_cmd(addr);
	ret = bridge_write_data(tmp_buff,sizeof(tmp_buff));

    return ret;
}
/******************************************************************************/
/// Description:ssd2829 write register
/// @note:ssd2829 write register(16BIT)
/// @param input:data,len
/// @param output:null
/// @return value
/******************************************************************************/
int bridge_write_reg_16bit(unsigned char addr,uint16_t tmp)
{
    int ret = 0;
    unsigned char tmp_buff[2] = {0};

    if(addr == 0xB6)
    {
        bridge_mem_reg_b6[0] &= ~0xFFFF;
        bridge_mem_reg_b6[0] |= tmp;
    }

    if(addr == 0xB7)
    {
        bridge_mem_reg_b7[0] &= ~0xFFFF;
        bridge_mem_reg_b7[0] |= tmp;
    }

    if(addr == 0xBD)
    {
        bridge_mem_reg_bd[0] &= ~0xFFFF;
        bridge_mem_reg_bd[0] |= tmp;
    }

    if(addr == 0xDE)
    {
        bridge_mem_reg_de[0] &= ~0xFFFF;
        bridge_mem_reg_de[0] |= tmp;
    }

	tmp_buff[0] = (tmp >> 8) & 0xFF;
	tmp_buff[1] = (tmp >> 0) & 0xFF;
	ret = bridge_write_cmd(addr);
	ret = bridge_write_data(tmp_buff,sizeof(tmp_buff));
    
    return ret;
}
/******************************************************************************/
/// Description:ssd2829 write frame register
/// @note:ssd2829 write register(fram)
/// @param input:addr,data,len
/// @param output:null
/// @return value
/******************************************************************************/
static int bridge_write_regs(unsigned char addr,unsigned char *frame, uint32_t len)
{
    int ret = 0;

	ret = bridge_write_cmd(addr);
	ret = bridge_write_lsb_data(frame, len);

    return ret;
}

/******************************************************************************/
/// Description:ssd2829 read register
/// @note:ssd2829 read register data
/// @param input:addr
/// @param output:data
/// @return value
/******************************************************************************/
int bridge_read_reg(unsigned char addr,uint32_t *temp)
{
    int ret = 0;
    unsigned char tmp_buff[4] = {0};

	ret = bridge_write_cmd(addr);
	ret = bridge_spi_read_data(tmp_buff,sizeof(tmp_buff));

	*temp = tmp_buff[2];
	*temp <<= 8;
	*temp |= tmp_buff[3];
	*temp <<= 8;
	*temp |= tmp_buff[0];
	*temp <<= 8;
	*temp |= tmp_buff[1];
    
    if(ret > 0)
    {
        if(addr == 0xB6)
            bridge_mem_reg_b6[0] = *temp;

        if(addr == 0xB7)
            bridge_mem_reg_b7[0] = *temp;
		
        if(addr == 0xDE)
            bridge_mem_reg_de[0] = *temp;

        return 1;
    }

    return -1;
}
/******************************************************************************/
/// Description:ssd2829 read register frame
/// @note:ssd2829 read register data
/// 24-bit,
/// 1st XX XX BYTE1 BYTE0
/// 2st XX XX BYTE3 BYTE2
/// @param input:addr
/// @param output:data
/// @return value
/******************************************************************************/
int bridge_read_regs(unsigned char addr,unsigned char *frame,uint32_t len)
{
    int i = 0;
    int ret = 0;

    unsigned char* data_buffer =(unsigned char*)malloc(len + 1);

	ret = bridge_write_cmd(addr);
	ret = bridge_spi_read_data(data_buffer,len);
	if(ret > 0)
	{
		for(i = 0; i < len; i++)
		{
			if((i % 2) == 0)
				frame[i] = data_buffer[i + 1];
			else
				frame[i] = data_buffer[i - 1];
		}
	}

   	free(data_buffer);

	if(ret > 0)
		return 1;

    return -1;
}
/******************************************************************************/
/// Description:ssd2829 read apb register
/// @note:ssd2829 read register data
/// ssd2829 read APB register,APB Register are accessed by 0xE0
///	The content of 0xE0 are 2 bytes APB Register addr
///	0xE1 storage APB Register data
///	24-bit,
///	1st XX XX BYTE1 BYTE0
///	2st XX XX BYTE3 BYTE2
/// @param input:addr
/// @param output:data
/// @return value
/******************************************************************************/
int bridge_read_apb_reg(uint16_t addr,uint32_t *temp)
{
    int ret = 0;
    unsigned char tmp_buff[4] = {0};

	ret = bridge_write_cmd(0xE0);
	ret = bridge_write_reg_16bit(0xE1,addr);
	ret = bridge_spi_read_data(tmp_buff,sizeof(tmp_buff));
	*temp = tmp_buff[2];
	*temp <<= 8;
	*temp |= tmp_buff[3];
	*temp <<= 8;
	*temp |= tmp_buff[0];
	*temp <<= 8;
	*temp |= tmp_buff[1];

    if(ret > 0)
    {
        return 1;
    }

    log_err("fail\n");
    return -1;
}

/*!*********************************************************************************************
    Function           :int bridge_write_apb_reg(uint16_t addr,uint32_t data)
    Description        :ssd 2829 apb  write register
                        data 31-24
                        data 23-16
                        data 15-8
                        data 7-0
                        addr 15-8
                        addr 7-0
    Input Parameter    :
    Output Parameter   :
    Who Make it ?      :
    History            :                            Date/Time:12-03-2013
**********************************************************************************************/
int bridge_write_apb_reg(uint16_t addr,uint32_t data)
{
    int ret = 0;
    unsigned char tmp_buff[6] = {0};

	ret = bridge_write_cmd(0xE0);

	tmp_buff[4] = (data >> 24) & 0xFF;
	tmp_buff[5] = (data >> 16) & 0xFF;
	tmp_buff[2] = (data >> 8) & 0xFF;
	tmp_buff[3] = (data >> 0) & 0xFF;
	tmp_buff[0] = (addr >> 8) & 0xFF;
	tmp_buff[1] = (addr >> 0) & 0xFF;

	ret = bridge_write_data(tmp_buff, sizeof(tmp_buff));
    return ret;
}
/*!*********************************************************************************************
    Function           :int bridge_setbistmode(int enable)
    Description        :
    Input Parameter    :
    Output Parameter   :
    Who Make it ?      :
    History            :                            Date/Time:12-03-2013
**********************************************************************************************/
int bridge_setbistmode(int enable)
{
    int ret = 0;
    uint32_t tmp = 0;

   //tmp = 0x00600001;  //100025;single port
		tmp = 0x000c0010;  //100025;single port
    //tmp = 0x0060000b; //60 Frames/Image  Dual data buffer mode (Broadcast)

    bridge_write_apb_reg(0x5000,tmp);
    if(enable > 0)
    {
        log_info("bridge bist mode enabled\n");
    }
    else
    {
        log_info("bridge bist mode disabled\n");
    }

	usleep(10000);
    return ret;
}

int bridge_hw_reset(void);

/*!*********************************************************************************************
    Function           :int bridge_check_id(int port)
    Description        :ssd2832 check id
    Input Parameter    :
    Output Parameter   :
    Who Make it ?      :
    History            :                            Date/Time:12-03-2013
*!*********************************************************************************************/
int bridge_check_id(void)
{
    int i = 0;
	int retry = 3;
    uint32_t device_id = 0;


	usleep(10000);
    bridge_hw_reset();
    for(i = 0; i < retry; i++)
    {
        bridge_read_reg(0xB0,&device_id);
		log_info("|--mipi bridge,0x%04X\n",device_id);

		bridge_read_apb_reg(0x0000,&device_id);
		log_info("|--mipi bridge, APB,0x%08X\n",device_id);
        if(device_id == 0x00002830)
        {
            break;
        }
    }

    if(i >= retry)
    {
		log_err("fail\n");
        return -1;
	}
	return 1;
}


static struct bridge gsrt_bridge[BRIDGE_PORT_COUNT];

/******************************************************************************/
/// Description:bridge_get
/// @note:get bridge config  information
/// @param input:none
/// @param output:struct bridge information
/// @return
///@author :
///@date : 2019-06-24
/******************************************************************************/
struct bridge *bridge_get()
{
	return &gsrt_bridge[0];
}
/******************************************************************************/
/// Description:ssd2829 inition td4320 , video mode screen
/// @note:
/// @param input:null
/// @param output:null
/// @return value
///@author : liufeng
///@date : 2019-06-24
/******************************************************************************/
static void msleep(uint32_t tick)
{
	usleep(1000 * tick);
}

/******************************************************************************/
/// Description:SSD2829 inition
/// @note:
/// @param input:null
/// @param output:null
/// @return
/******************************************************************************/
int bridge_hw_reset(void)
{
    SSD2832_RST_H() ;
		msleep(50);
    SSD2832_RST_L();
    msleep(100);
    SSD2832_RST_H() ;
    msleep(50);
	return 1;
}

int bridge_RSTPIN_reset(void)
{

    SSD2832_RST_L();

	return 1;
}


/******************************************************************************/
/// Description:ssd2829 inition td4320 , video mode screen
/// @note:
/// @param input:null
/// @param output:null
/// @return value
///@author : liufeng
///@date : 2019-06-24
/******************************************************************************/
int bridge_init(void)
{
    uint32_t tmp_lo = 0;
    uint32_t tmp_hi = 0;
	uint32_t value = 0;
	uint32_t hs = 0, lp = 0, m = 0, n = 0;
	uint32_t rba = 0;
	uint32_t is_cphy = 0;
    struct bridge *pbridge;	
	

	pbridge = bridge_get();
	pbridge->hsw = ptr_MIPI_TABLE[gMipiTableIndex]->HSW_WIDTH;  		//H Sync Width
	pbridge->vsw = ptr_MIPI_TABLE[gMipiTableIndex]->VSW_WIDTH; 		//V Sync Width
	pbridge->hbp = ptr_MIPI_TABLE[gMipiTableIndex]->HBP_WIDTH;//64 ; 		//H Back Porch
	pbridge->vbp = ptr_MIPI_TABLE[gMipiTableIndex]->VBP_WIDTH; 		//V Back Porch
	pbridge->hfp = ptr_MIPI_TABLE[gMipiTableIndex]->HFP_WIDTH;//64; 		//H Front Porch
	pbridge->vfp = ptr_MIPI_TABLE[gMipiTableIndex]->VFP_WIDTH; 		//V Front Porch
	pbridge->hact = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH; 	//H Active
	pbridge->vact  = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH; 	//V Active

	pbridge->hzd = 0;
	pbridge->hpd = 0;
	pbridge->czd = 0;
	pbridge->cpd = 0;
	pbridge->cped = 0;
	pbridge->cptd = 0;
	pbridge->ctd = 0;
	pbridge->htd = 0;

	pbridge->dual = 1;           //0,single,1,dual
	pbridge->lane = ptr_MIPI_TABLE[gMipiTableIndex]->LANE_CNT-1;           //4lane
	pbridge->video_or_cmd = 0;   //video,command
	pbridge->bits = 3;           //24,18,16
	pbridge->rgb_or_bgr = 0;     //RGB,BGR
	
	pbridge->pclk_polarity=0;
	pbridge->de_polarity = 1;    //DE Polarity;0,active low
	pbridge->vsync_polarity =0; //V Sync Polarity;0,Vsync pulse is active low  关键参数
	pbridge->hsync_polarity = 0; //H Sync Polarity;0,Hsync pulse is active low
	pbridge->sync_mode = ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode;      //Video mode,0,non burst mode with sync pulse
							//1,non burst mode with sync events
							//burst mode

	pbridge->split_mode = 2;     //split_mode, 0 - odd/even, 1 - Left/Right, 2 - broadcast
	pbridge->video_msb_lsb_swap	=	0;	//0 – No Swap 1 –Swap RGB pixel upper and lower
	
	
	pbridge->clk_lp = 7;         //LP Speed(MHz);low speed
	pbridge->clk_hs = 720 ;  //952       //HS Speed(MHz);High speed

	pbridge->init_by_hs_mode = 0; //Initialize By HS Mode;
	pbridge->always_keep_hs = 0;  //Always Keep HS Clock
	pbridge->send_eot_in_hs = 1;  //Send EOT Packet in HS Mode
	pbridge->start_video_before_init = 1; //Start Video before Initialzation

	pbridge->virtual_channel = 0;  //virtual channel;
	pbridge->dphy_or_cphy = 1;     //0 - MIPI DPHY, 1 - MIPI CPHY

	pbridge->driver_output_res_ctl = 0x00FF0000 | 14;  //Analog Control Register,BIT28-25,Driver output resistance control
	pbridge->low_power_tx_drive_strength = 0x00FF0000|0 ; //Analog Control Register,BIT24-22,Low Power Transmitter Drive Strength
	pbridge->post_len = 0x00FF0000 |31;          //CPHY Transmit Global Register 1,BIT20-16,The number of symbol in the Post field is:(post_length+1)*7
	pbridge->Voltage_trimming_bits=3;

    log_info("start");

   if(pbridge->dphy_or_cphy > 0)
    {
        //CPHY
        log_info("MIPI CPHY Detected\n");
        is_cphy = 1;
        bridge_select_phy(0);
    }
    else
    {
        //DPHY
        log_info("MIPI DPHY Detected\n");
        is_cphy = 0;
        bridge_select_phy(1);
    }
    msleep(50);

    bridge_hw_reset();

	//Set Virtual Channel:
	uint32_t virtual_channel = pbridge->virtual_channel;
	bridge_write_reg_16bit(0xB8,virtual_channel | (virtual_channel << 2) | (virtual_channel << 4) | (virtual_channel << 6));

	//PLL power down
	bridge_write_reg_16bit(0xB9,0x0000);

	//Set PLL, HS=1000Mbps
    if(is_cphy)
    {
        //byp_bit_div = 1, dual symbol clock
        double sps = (double)(pbridge->clk_hs)/1.0f;
        hs = (uint32_t)(ceil(sps));
    }
    else
    {
        double sps = (double)(pbridge->clk_hs)/1.0f;
        hs = (uint32_t)(ceil(sps));
    }
    //XTRAL 25MHZ
    lp = pbridge->clk_lp;
	n = (hs + 4) / 5;
	m = 5 * n;
	hs = m;

	if(is_cphy)
    {
        double x = m*1.0/2.0;
    	n = (uint32_t)(x / (7 * lp));
    	if ((x - n*7.0f*lp)>0)
    		n += 1;
    	lp = (uint32_t)(x / (7 * n));
    	n -= 1;
    }
    else
    {
        double x = m*1.0;
    	n = (uint32_t)(x / (8 * lp));
    	if ((x - n*8.0f*lp)>0)
    		n += 1;
    	lp = (uint32_t)(x / (8 * n));
    	n -= 1;
    }

	if (m<125)
		rba = 0x0200;
	else if (m<250)
		rba = 0x4200;
	else if (m<500)
		rba = 0x8200;
	else
		rba = 0xC200;
	rba |= (m / 5) & 0xFF;


    rba &= 0xf0ff;
	rba |= 0x500;

    bridge_write_reg_16bit(0xBA,rba);

	if(is_cphy)
	{
	    //BYP_BIT_DIV  set default to 1 will result with read error
	    bridge_write_reg_32bit(0xBB, n & 0x3F | 0x07050000);//Reference Code
	}
	else
	{
	    bridge_write_reg_16bit(0xBB,n & 0x3F);
	}
	bridge_write_reg_16bit(0xB9,0x0001);
	msleep(20);

	//RGB Interface Control
    tmp_hi = pbridge->vsw;
    tmp_hi <<= 8;
    tmp_hi |= pbridge->hsw;
    bridge_write_reg_16bit(0xB1,tmp_hi);

    if (0 == pbridge->sync_mode)
    {
        //non burst mode with sync pulse
        bridge_write_reg_32bit(0xB2,
                              (0xFF000000&((pbridge->vbp)>>8<<24)) |
                              (0xFF0000&((pbridge->hbp)>>8<<16)) |
                              (0xFF00&((pbridge->vbp)<<8)) |
                              (0xFF&(pbridge->hbp)));
    }
    else
    {
        bridge_write_reg_32bit(0xB2,
                              (0xFF000000&((pbridge->vbp + pbridge->vsw)>>8<<24)) |
                              (0xFF0000&((pbridge->hbp + pbridge->hsw)>>8<<16)) |
                              (0xFF00&((pbridge->vbp + pbridge->vsw)<<8)) |
                              (0xFF&(pbridge->hbp + pbridge->hsw)));
    }

    //VFP[15:8],HFP[15:8]
    tmp_hi = pbridge->vfp;
    tmp_hi &= 0xFF00;
    tmp_hi <<= 16;
    tmp_lo = pbridge->hfp;
    tmp_lo &= 0xFF00;
    tmp_lo <<= 8;
    tmp_hi |= tmp_lo;

    //VBP[7:0],HBP[7:0]
    tmp_lo = pbridge->vfp;
    tmp_lo &= 0xFF;
    tmp_lo <<= 8;
    tmp_hi |= tmp_lo;
    tmp_lo = pbridge->hfp;
    tmp_lo &= 0xFF;
    tmp_hi |= tmp_lo;
	bridge_write_reg_32bit(0xB3,tmp_hi);

    tmp_hi = pbridge->hact;
    tmp_hi &= 0xFFFF;
	bridge_write_reg_32bit(0xB4,tmp_hi);

    tmp_hi = pbridge->vact;
    tmp_hi &= 0xFFFF;
	bridge_write_reg_32bit(0xB5,tmp_hi);

	//HS TX Timer
	tmp_hi = 0;
	bridge_write_reg_32bit(0xCF,tmp_hi);
	tmp_hi = 0x10;
	bridge_write_reg_32bit(0xD0,tmp_hi);

	tmp_hi = 0x40;
	bridge_write_reg_32bit(0xD3,tmp_hi);

	//Test Register
    tmp_hi = 0x10000104; //DEFAULT
    if (pbridge->rgb_or_bgr > 0)
    {
        tmp_hi |= 0x01;
    }
	bridge_write_reg_32bit(0xD6,tmp_hi);

	int default_analog_control = 0x2A1C8719;

	//Analog Control Register
	if(is_cphy)
    {
		default_analog_control = 0x3E7C8F39;

		if(pbridge->driver_output_res_ctl & 0x00FF0000)
		{
			//have set driver out resistence control
		    default_analog_control = 0x201C8F39;
			value = pbridge->driver_output_res_ctl;
			value &= 0xFF00FFFF;
		    default_analog_control |= (value << 25)	;
		}
		if(pbridge->Voltage_trimming_bits){
		
			default_analog_control |= (pbridge->Voltage_trimming_bits << 19)	;
		}
		if(pbridge->low_power_tx_drive_strength & 0x00FF0000)
		{
			value = pbridge->low_power_tx_drive_strength;
			value &= 0xFF00FFFF;
			default_analog_control &= 0xFE3FFFFF;
		    default_analog_control |= (value << 22)	;
		}

	    bridge_write_reg_32bit(0xD8,default_analog_control);

	    int default_tran_global = 0x1B121E40; //0x1B081E40--ic reset default
		if(pbridge->post_len & 0x00FF0000)
		{
			default_tran_global = 0x1B001E40;

			value = pbridge->post_len;
			value &= 0xFF00FFFF;
		    default_tran_global |= (value << 16)	;
		}
		//CPHY Analog Front End Registers Descriptions,0
		bridge_write_apb_reg(0x1000,default_tran_global); //Set CPHY Post len requested by himax
//		bridge_write_apb_reg(0x100C,0x4E200C0C); //Set CPHY Post len requested by himax
//		bridge_write_apb_reg(0x1010,0x00000110); //Set CPHY Post len requested by himax
		
		//CPHY Analog Front End Registers Descriptions,1
    bridge_write_apb_reg(0x2000,default_tran_global); //Set CPHY Post len requested by himax
//		bridge_write_apb_reg(0x200C,0x4E200C0C); //Set CPHY Post len requested by himax
//		bridge_write_apb_reg(0x2010,0x00000110); //Set CPHY Post len requested by himax
		
    }
    else
    {
		default_analog_control = 0x2B1C8519;

		if(pbridge->driver_output_res_ctl & 0x00FF0000)
		{
			//have set driver out resistence control
		    default_analog_control = 0x211C8519;
			value = pbridge->driver_output_res_ctl;
			value &= 0xFF00FFFF;
		    default_analog_control |= (value << 25)	;
		}

		if(pbridge->low_power_tx_drive_strength & 0x00FF0000)
		{
			value = pbridge->low_power_tx_drive_strength;
			value &= 0xFF00FFFF;
			default_analog_control &= 0xFE3FFFFF;
		    default_analog_control |= (value << 22)	;
		}

        //LPTX_DS ?C Low Power Transmitter Drive Strength
	    //Default //2A1C8719
	    bridge_write_reg_32bit(0xD8,default_analog_control);
	    //Increase Low Power Transmitter Drive Strength, some time can not light on, not sure the reason
    }

	//INOUT Configuration
    //tmp_hi = 0x50020; //READ TX0,WRITE TX0,SINGLE MODE,TX1 1LANE, TX0 1LANE
	tmp_hi = 0;
    if(0 == pbridge->dual) //PORT,single
	{
	    tmp_hi |= (0x01 << 5);
	    tmp_hi |= pbridge->lane;
	}
	else if(1 == pbridge->dual) //PORT,dual
	{
	    tmp_hi |= (0x01 << 4);
        tmp_hi |= (0x01 << 5);
        tmp_hi |= (0x01 << 6);
        tmp_hi |= pbridge->lane;
        tmp_hi |= ((pbridge->lane) << 2);
	}
	if(pbridge->video_or_cmd==0)
	{
		if(pbridge->video_msb_lsb_swap)
		{
			tmp_hi |= 0x01<<21;
		}
	}
	if(pbridge->video_or_cmd==1)
	{
		if(pbridge->mcu_msb_lsb_swap)
		{
			tmp_hi |= 0x01<<25;
		}
	}	
	bridge_write_reg_32bit(0xDE,tmp_hi);

	//RGB Interface Control Register 6
    tmp_hi = 0x00021020; //DEFAULT

    if(pbridge->always_keep_hs)
    {
        tmp_hi = 0x00021080; //DEFAULT 0x00021080
    }
    else
    {
        tmp_hi = 0x000210A0; //DEFAULT 0x00021020
    }

    if (pbridge->vsync_polarity > 0) //0,Vsync Pulse is active low
    {
        tmp_hi |= (0x01 << 15);
    }

    if (pbridge->hsync_polarity > 0)
    {
        tmp_hi |= (0x01 << 14);
    }
    if(pbridge->pclk_polarity)
		{
			tmp_hi |= (0x01 << 13);
		}
    //split mode, 0 - odd/even, 1 - Left/Right, 2 - broadcast
    if (pbridge->split_mode == 1)
    {
        //Left/right
        tmp_hi |= (0x01 << 10);
    }
    if (pbridge->split_mode == 2)
    {
        //broadcast
        tmp_hi |= (0x02 << 10);
    }

    //video mode
    if (0 == pbridge->sync_mode)
    {
        //non burst mode with sync pulse
    }
    else    if (1 == pbridge->sync_mode)
    {
        //non burst mode with sync event
        tmp_hi |= (0x01 << 2);
    }
    else    if (2 == pbridge->sync_mode)
    {
        //burst mode
        tmp_hi |= (0x01 << 3);
    }

    //video pixel format
    if (0 == pbridge->bits)
    {
        //16bit
    }
    else     if (1 == pbridge->bits)
    {
        //18bit
        tmp_hi |= (0x01 << 0);
    }
    else     if (2 == pbridge->bits)
    {
        //18-bit loosely
        tmp_hi |= (0x01 << 1);
    }
    else     if (3 == pbridge->bits)
    {
        //24bit
        tmp_hi |= (0x01 << 1);
        tmp_hi |= (0x01 << 0);
//				tmp_hi |= (0x01 << 9);
				tmp_hi |= (0x01 << 8);
    }
	bridge_write_reg_32bit(0xB6,tmp_hi);
	msleep(1);

    //Delay Adjustment
	double ui = 1000.0f / hs;
	double nibble = 4 * ui;
	uint32_t hs_prepare = (uint32_t)(ceil((53 + 5 * ui) / nibble));
	uint32_t hs_zero = (uint32_t)(ceil((126 + 8 * ui) / nibble));
	uint32_t hs_trail = (uint32_t)(ceil((72 + 5 * ui) / nibble));
	uint32_t hs_exit = (uint32_t)(ceil(120 / nibble));
	uint32_t clk_post = (uint32_t)(ceil((72 + 63 * ui) / nibble));
	uint32_t clk_pre = (uint32_t)(ceil(11 / nibble));
	uint32_t clk_prepare = (uint32_t)(ceil(66 / nibble));
	uint32_t clk_zero = (uint32_t)(ceil(315 / nibble));
	uint32_t clk_trail = (uint32_t)(ceil(72 / nibble));
	uint32_t rc9 = (hs_zero << 8) + (hs_prepare - 4);
	uint32_t rca = (clk_zero << 8) + clk_prepare - 3;
	uint32_t rcb = (clk_pre << 8) + clk_post;
	uint32_t rcc = (clk_trail << 8) + hs_trail;
	uint32_t rdf = hs_exit;

	////Delay Adjustment overloaded
    tmp_hi = pbridge->hzd;
    tmp_hi <<= 8;
    tmp_hi |= pbridge->hpd;
    if (tmp_hi > 0)
    {
        rc9 = tmp_hi;
        //bridge_write_reg_16bit(port,0xC9,tmp_hi);
    }

    tmp_hi = pbridge->czd;
    tmp_hi <<= 8;
    tmp_hi |= pbridge->cpd;
    if (tmp_hi > 0)
    {
        rca = tmp_hi;
        //bridge_write_reg_16bit(port,0xCA,tmp_hi);
    }

    tmp_hi = pbridge->cped;
    tmp_hi <<= 8;
    tmp_hi |= pbridge->cptd;
    if (tmp_hi > 0)
	{
	    rcb = tmp_hi;
    }

    tmp_hi = pbridge->ctd;
    tmp_hi <<= 8;
    tmp_hi |= pbridge->htd;
    if (tmp_hi > 0)
	{
	    rcc = tmp_hi;
    }

	//Configuration Register
	tmp_hi = 0x0100;
	if (pbridge->send_eot_in_hs > 0)
	{
		tmp_hi |= 0x0200;
	}
	//Start video mode if video before init
	if (pbridge->start_video_before_init)
	{
		tmp_hi |= 0x09;
	}
    log_info("------0xB7 = tmp_hi%x\r\n" , tmp_hi);
	bridge_write_reg_16bit(0xB7,tmp_hi);
	
	
	usleep(100000);
	bridge_reg_test();
	
	return 1;
}

/******************************************************************************/
/// Description:bridge_stop_video
/// @note:
/// @param input:null
/// @param output:null
/// @return value
///@author : liufeng
///@date : 2019-06-24
/******************************************************************************/
int bridge_stop_video(void)
{
	bridge_write_reg_16bit(0xB7, bridge_mem_reg_b7[0] & 0xFFF6);
	return 1;
}

/******************************************************************************/
/// Description:bridge_enter_sleep
/// @note: Sleep mode is enabled
/// @param input:null
/// @param output:null
/// @return value
///@author : liufeng
///@date : 2019-06-24
/******************************************************************************/
int bridge_enter_sleep(void)
{
	bridge_write_reg_16bit(0xB7, bridge_mem_reg_b7[0] | 0x04);
	return 1;
}

/******************************************************************************/
/// Description:bridge_send_hs_nop_package
/// @note:
/// @param input:null
/// @param output:null
/// @return value
///@author : tor shi
///@date : 2019-08-26
/******************************************************************************/
int bridge_send_hs_nop_package(void)
{
    unsigned char data_buff[4] = {0};
    struct mipi_port mipi;
    struct bridge *pbridge;
	
    pbridge = bridge_get();

    mipi.port = 0;
    if(0 == pbridge->dual) //PORT,single
	{
        mipi.dual = 1;
	}
	else if(1 == pbridge->dual) //PORT,dual
	{
	    mipi.dual = 3;
	}

    //Send Packet:0x39,0x00,0x00
    mipi.video_or_cmd = 0;
    mipi.data_type    = 0x39;
    mipi.hs_or_lp     = 1;
	
    data_buff[0] = 0x00;
    mipi_write_regs(&mipi,data_buff,1);

    return 1;
}

int bridge_send_ls_nop_package(void)
{
    unsigned char data_buff[4] = {0};
    struct mipi_port mipi;
    struct bridge *pbridge;
	
    pbridge = bridge_get();
    mipi.port = 0;

    if(0 == pbridge->dual) //PORT,single
	{
        mipi.dual = 1;
	}
	else if(1 == pbridge->dual) //PORT,dual
	{
	    mipi.dual = 3;
	}

    //Send Packet:0x39,0x00,0x00
    mipi.video_or_cmd = 0;
    mipi.data_type    = 0x39;
    mipi.hs_or_lp     = 0;
    data_buff[0]      = 0x00;
    mipi_write_regs(&mipi,data_buff,1);
    return 1;
}


/******************************************************************************/
/// Description:bridge_send_cmd_image refresh pic ,  CMD screen
/// @note:
/// @param input:null
/// @param output:null
/// @return value
///@author : liuzhiheng
///@date : 2019-07-17

/******************************************************************************/
int bridge_send_cmd_image(void)
{
	unsigned int tmp = 0 , time_tick = 0;
	uint32_t reg_status = 0;
		
	//Test If is LS NOP Package helps
	bridge_send_ls_nop_package();
	bridge_send_hs_nop_package();

	bridge_write_reg_32bit(0xCF,0X00000000); //SET HS TX TIMER1,L
	bridge_write_reg_32bit(0xD0,0X00009000); //SET HS TX TIMER2,H
	bridge_write_apb_reg(0X0010,0X1C910E00); //ENABLE V2C

	bridge_write_reg_16bit(0xB7,0x030b);
	
	time_tick = 0;
	do
	{
		bridge_read_reg(0xC6, &reg_status);
		if((reg_status & 0x100) == 0)
		{
			// mcu long buffer is not available
			log_info("Err state %x, Reset 2829 inti 4330 \r\n" , reg_status);
			break;
		}
		if((reg_status & 0x200) == 0)
		{
			break;
		}
		msleep(1);
		time_tick++;
		if(time_tick > 34)
		{
			break;
		}
	}while(1);

	bridge_write_reg_16bit(0xB7,0x0300);
	
	time_tick = 0;
	do
	{
		bridge_read_reg(0xC6, &reg_status);
		if((reg_status & 0x200) != 0)
		{//bit9
			break;
		}
		if(time_tick > 100)
		{//10s
			break;
		}
		msleep(1);
		time_tick++;
	}while(1);
	bridge_write_apb_reg(0X0010,0X1C900E00); //DISABLE V2C

	bridge_read_reg(0xC7,&tmp);
	
	if(tmp != 0)
	{
		log_info("Err state %x, Reset init \r\n" , reg_status);
	}
	
	return 1;
}

int bridge_v2c(unsigned char stage, unsigned int delay)
{
    msleep(delay);
	
    if(stage > 0)
    {
        if(stage == 1)
        {
            bridge_send_hs_nop_package();
            bridge_write_reg_32bit(0xCF,0x00000000); //SET HS TX TIMER1,L
            bridge_write_reg_32bit(0xD0,0x00009000); //SET HS TX TIMER2,H
            bridge_write_reg_16bit(0xB7,0x430B);
        }

        if(stage == 2)
        {
            bridge_write_apb_reg(0x0010,0x1C910E00); //ENABLE V2C
        }

        if(stage == 3)
        {
            bridge_send_hs_nop_package();
            bridge_write_reg_32bit(0xCF,0x00000000); //SET HS TX TIMER1,L
            bridge_write_reg_32bit(0xD0,0x00009000); //SET HS TX TIMER2,H
            bridge_write_reg_16bit(0xB7,0x430B);
            msleep(10);
            bridge_write_apb_reg(0x0010,0x1C910E00); //ENABLE V2C
        }

        if(stage == 4)
        {
            bridge_write_reg_16bit(0xB7,0x4300);
            bridge_write_apb_reg(0x0010,0x1C900E00); //DISABLE V2C
        }

        if(stage == 5)
        {}
    }

    log_info("stage = %d \n" , stage);
	return 1;
}

/*!*********************************************************************************************
    Function           :int bridge_reg_test(void)
    Description        :ssd2829 write and read register test
    Input Parameter    :
    Outp
    ut Parameter   :
    Who Make it ?      :
    History            :                            Date/Time:12-03-2013
**********************************************************************************************/
int bridge_reg_test()
{
    uint32_t tmp = 0;

    bridge_read_reg(0xB1,&tmp);
    log_info("0xB1,0x%08X\n",tmp);

    bridge_read_reg(0xB2,&tmp);
    log_info("0xB2,0x%08X\n",tmp);

    bridge_read_reg(0xB3,&tmp);
    log_info("0xB3,0x%08X\n",tmp);

    bridge_read_reg(0xB4,&tmp);
    log_info("0xB4,0x%08X\n",tmp);

    bridge_read_reg(0xB5,&tmp);
    log_info("0xB5,0x%08X\n",tmp);

    bridge_read_reg(0xB6,&tmp);
    log_info("0xB6,0x%08X\n",tmp);

    bridge_read_reg(0xB7,&tmp);
    log_info("0xB7,0x%08X\n",tmp);

    bridge_read_reg(0xB8,&tmp);
    log_info("0xB8,0x%08X\n",tmp);

    bridge_read_reg(0xB9,&tmp);
    log_info("0xB9,0x%08X\n",tmp);

    bridge_read_reg(0xBA,&tmp);
    log_info("0xBA,0x%08X\n",tmp);

    bridge_read_reg(0xBB,&tmp);
    log_info("0xBB,0x%08X\n",tmp);

    bridge_read_reg(0xC6,&tmp);
    log_info("0xC6,0x%08X\n",tmp);

    bridge_read_reg(0xC7,&tmp);
    log_info("0xC7,0x%08X\n",tmp);

    bridge_read_reg(0xC9,&tmp);
    log_info("0xC9,0x%08X\n",tmp);

    bridge_read_reg(0xCA,&tmp);
    log_info("0xCA,0x%08X\n",tmp);

    bridge_read_reg(0xCB,&tmp);
    log_info("0xCB,0x%08X\n",tmp);

    bridge_read_reg(0xCC,&tmp);
    log_info("0xCC,0x%08X\n",tmp);

    bridge_read_reg(0xD6,&tmp);
    log_info("0xD6,0x%08X\n",tmp);

    bridge_read_reg(0xDE,&tmp);
    log_info("0xDE,0x%08X\n",tmp);

    bridge_read_reg(0xDF,&tmp);
    log_info("0xDF,0x%08X\n",tmp);

    return 1;
}

/******************************************************************************/
/// Description:mipi_write_regs
/// @note:
/// @param input:port,data,len
/// @param output:null
/// @return value
/******************************************************************************/
int mipi_write_regs(struct mipi_port *pmipi, uint8_t *frame,uint32_t len)
{
	uint16_t rb6 = 0;
	uint16_t rb7=0x0100;
	uint32_t tmp = 0;
	uint32_t tmp_mem_b6 = 0;
	uint32_t tmp_mem_b7 = 0;
	uint32_t tmp_mem_de = 0;
    int port = 0;
	
	port = pmipi->port;

	//Set MIPITX
	tmp_mem_de = bridge_read_mem_reg(0xDE);
	tmp_mem_de &= 0xFFFFFF9F;
	
    if(pmipi->dual & 0x01)//MIPI TX0
    {
        tmp_mem_de |= (0x01 << 5);
    }
	
    if(pmipi->dual & 0x02)//MIPI TX1
    {
        tmp_mem_de |= (0x01 << 6);
    }

    if(tmp_mem_de != bridge_read_mem_reg(0xDE))
    {
        bridge_write_reg_32bit(0xDE,tmp_mem_de);
    }

    //Transmit Data Count High
	if(bridge_read_mem_reg(0xBD) != 0)
	{
	    bridge_write_reg_16bit(0xBD, 0);
	}

	tmp_mem_b6 = bridge_read_mem_reg(0xB6);
	tmp_mem_b7 = bridge_read_mem_reg(0xB7);

	rb6 = (tmp_mem_b6 & 0x0000FFFF);
	rb7 = (tmp_mem_b7 & 0x0000FFFF);

	//Clear REN bit, Set to Write
	rb7 &= ~0x0080;

	//1. Set Transmit Data Count (TDC)
	tmp = len;
	bridge_write_reg_16bit(0xBC,tmp);

	//2. Check dataType
	switch(pmipi->data_type)
	{
		//DCS SHORT WRITE
		case 0x05:
		case 0x15:
		{
			//Clear LPE(bit10) - Long Packet Enable, Set to short
			rb7 &= ~0x0400;
			//Clear OTHER_CMD(bit12) - Other Command, set to DCS or Generic
			rb7 &= ~0x1000;
			//Set DCS(bit 6) - DCS or Generic, set to DCS
			rb7 |= 0x0040;
		}
		break;
		//DCS LONG WRITE
		case 0x39:
		{
			//Set LPE(bit10) - Long Packet Enable, Set to Long
			rb7 |= 0x0400;
			//Clear OTHER_CMD(bit12) - Other Command, set to DCS or Generic
			rb7 &= ~0x1000;
			//Set DCS(bit 6) - DCS or Generic, set to DCS
			rb7 |= 0x0040;
		}
		break;
		//Generic short WRITE
		case 0x13:
		case 0x23:
		{
			//Clear LPE(bit10) - Long Packet Enable, Set to short
			rb7 &= ~0x0400;
			//Clear OTHER_CMD(bit12) - Other Command, set to DCS or Generic
			rb7 &= ~0x1000;
			//Set DCS(bit 6) - DCS or Generic, set to Generic
			rb7 &= ~0x0040;
		}
		break;
		//Generic Long WRITE
		case 0x29:
		{
			//Set LPE(bit10) - Long Packet Enable, Set to Long
			rb7 |= 0x0400;
			//Clear OTHER_CMD(bit12) - Other Command, set to DCS or Generic
			rb7 &= ~0x1000;
			//Set DCS(bit 6) - DCS or Generic, set to Generic
			rb7 &= ~0x0040;
		}
		break;
		//Compression Mode Command, Short Write
		case 0x07:
		{
			//Clear LPE(bit10) - Long Packet Enable, Set to short
			rb7 &= ~0x0400;
			//Set OTHER_CMD(bit12) - Other Command, set to DCS bit defines PPS or Compression mode packet.
			rb7 |= 0x1000;
			//Set DCS(bit 6) - DCS or Generic, 0 ?C Picture Parameter Setting Packet 1 ?C Compress Mode Packet
			rb7 |= 0x0040;
		}//break;
		//Picture Parameter Set, Long Write
		case 0x0A:
		{
			//Set LPE(bit10) - Long Packet Enable, Set to Long
			rb7 |= 0x0400;
			//Set OTHER_CMD(bit12) - Other Command, set to DCS bit defines PPS or Compression mode packet.
			rb7 |= 0x1000;
			//Set DCS(bit 6) - DCS or Generic, 0 ?C Picture Parameter Setting Packet 1 ?C Compress Mode Packet
			rb7 &= ~0x0040;
		}	//break;
		default:
		{
			return -1;
		}
	}

	//4. HS Mode
	if(pmipi->hs_or_lp)
	{
		rb6 &= ~0x0040;//Non video data will be transmitted using HS mode.
		rb7 |= 0x0001;
	}
	else
	{
		rb6 |= 0x0040; //Non video data will be transmitted using LP mode.
		rb7 &= ~0x0001;
	}

	//6. Check if Video Mode is ON
	if(rb7 & 0x0008)
	{
		//1  - Video mode is enabled
		rb7 |= 0x0009; //Control SSD2828 use HS mode to send data.
	}
	//7. Write rb6, rb7
	tmp_mem_b6 &= 0xFFFF0000;
	tmp_mem_b6 |= rb6;
	bridge_write_reg_16bit(0xB6,tmp_mem_b6);

	tmp_mem_b7 &= 0xFFFF0000;
	tmp_mem_b7 |= rb7;
	bridge_write_reg_16bit(0xB7,tmp_mem_b7);
	//8. Generic Packet Drop Register
	bridge_write_regs(0xBF, frame, len);
	return 0;
}

/******************************************************************************/
/// Description:mipi read
/// @note:
/// @param input:port,len
/// @param output:data
/// @return value
/******************************************************************************/
int mipi_read_regs(struct mipi_port *pmipi, uint8_t *frame,uint32_t len)
{
	uint16_t rb6 = 0;
	uint16_t rb7 = 0;
    uint32_t video_is_enable = 0;

    uint32_t tmp = 0;
	uint32_t tmp_mem_b6 = 0;
	uint32_t tmp_last_b6 = 0;
	uint32_t tmp_mem_b7 = 0;
	uint32_t tmp_last_b7 = 0;
	uint32_t tmp_mem_de = 0;

    int port = 0;
	
	port = pmipi->port;

	if(len > 0)
	{
		//Set MIPITX
		tmp_mem_de = bridge_read_mem_reg(0xDE);
		if(pmipi->dual & 0x02)//MIPI TX1
		{
			tmp_mem_de |= (0x01 << 7);
		}

		if(pmipi->dual & 0x01)//MIPI TX0
		{
			tmp_mem_de &= 0xFFFFFF7F;
		}

		if(tmp_mem_de != bridge_read_mem_reg(0xDE))
		{
			bridge_write_reg_32bit(0xDE,tmp_mem_de);
		}

		tmp = 0;

		tmp_mem_b6 = bridge_read_mem_reg(0xB6);
		tmp_last_b6 = tmp_mem_b6;

		tmp_mem_b7 = bridge_read_mem_reg(0xB7);
		tmp_last_b7 = tmp_mem_b7;
		rb6 = (tmp_mem_b6 & 0xFFFFFFFF);
		rb7 = (tmp_mem_b7 & 0xFFFF);
		//Set REN bit, Set to READ
		rb7 |= 0x0080;
		if(rb7 & 0x0008)
		{
			video_is_enable = 1;
		}
		//2. Check dataType
		switch(pmipi->data_type)
		{
			case 0x06:
			{
				//GenericRead
				if(video_is_enable)
				{
					rb7 = (0x03<<8) |(0xC2 & 0xEF) | 0x0B;    //original settings
				}
				else if(pmipi->hs_or_lp)
				{
					rb7 = (0x03<<8) | (0xC2 & 0xEF) | 0X03;
				}
				else
				{
					rb7 = 0x03C2; //LP DCS read
				}
			}
			break;
			case 0x04:
			case 0x14:
			case 0x24:
			{
				//GenericRead
				if(video_is_enable)
				{
					rb7 = (0x03 << 8)|(0x82 & 0xEF) | 0x0B; //original settings
				}
				else if(pmipi->hs_or_lp)
				{
					rb7 = (0x03 << 8)|(0x82 & 0xEF) | 0X03;
				}
				else
				{
					rb7 = 0x0382; //LP generic read
				}
			}
			break;
			default:return -1;
		}

		//4. HS Mode
		if(pmipi->hs_or_lp)
		{
			rb7 |= 0x0001;
			rb6 &= ~0x0040;//Non video data will be transmitted using HS mode.
		}
		else
		{
			rb7 &= ~0x0001;
			rb6 |= 0x0040; //Non video data will be transmitted using LP mode.
		}

		 //Clock lane will enter HS mode for all the cases
		rb7 |= 0x0002;

		//7. Write rb6, rb7
		tmp_mem_b6 &= 0xFFFF0000;
		tmp_mem_b6 |= rb6;
		if(tmp_last_b6 != tmp_mem_b6)
		{
			bridge_write_reg_16bit(0xB6,tmp_mem_b6);
		}

		tmp_mem_b7 &= 0xFFFF0000;
		tmp_mem_b7 |= rb7;
		if(tmp_last_b7 != tmp_mem_b7)
		{
			bridge_write_reg_16bit(0xB7,tmp_mem_b7);
		}

		//Set 0xC1 Maximum Return Size Register
		tmp = len;
		bridge_write_reg_16bit(0xC1,tmp);

		//cancel operation to clear data in the buffer, some delay may required for CPHY panel
		bridge_write_reg_16bit(0xC0,0x0001);

		//SET Packet Size Control Register 1 (Transmit Data Count, TDC)
		tmp = 0x0001;
		bridge_write_reg_16bit(0xBC,tmp);//Transmit Data Count Low

		//4. Generic Packet Drop Register
		tmp = pmipi->addr;

		bridge_write_reg_16bit(0xBF,tmp);

		msleep(30);
		
		bridge_read_reg(0xC6,&tmp);

		if(pmipi->dual & 0x02)//MIPI TX1
		{
			tmp = tmp >> 16;
		}

		if((( tmp & 0x0001) == 0))
		{
			//FAILED, RETRY
			log_err("check reg 0xC6,fail1,0x%08X\n",tmp);
			msleep(30);
			bridge_read_reg(0xC6,&tmp);

			if(pmipi->dual & 0x02)//MIPI TX1
			{
				tmp =  tmp >> 16;
			}

			if((( tmp & 0x0001) == 0))
			{
				//FAILED, RETRY
				log_info("check reg 0xC6,fail2,0x%08X\n",tmp);
				return -1;
			}
		}

		//5.Read
		bridge_read_regs(0xFF,frame,len);
		return len;
	}
	return 0;
}

#define	SSD2832_WRITE_COMMAND_BYTE 	(uint8_t)0x70		
#define	SSD2832_READ_COMMAND_BYTE 		(uint8_t)0x71		
#define	SSD2832_WRITE_DATA_BYTE 		(uint8_t)0x72		
#define	SSD2832_READ_DATA_BYTE 		(uint8_t)0x73	
void buffer_ssd2832_data2spi4(uint8_t cmd,uint16_t value);
int spi_write_ssd2832_reg_len( uint16_t  reg,  uint16_t *data, int len)
{
	int i;

	if (data == NULL)
	{
		return -1;
	}


	
	buffer_ssd2832_data2spi4(SSD2832_WRITE_COMMAND_BYTE, reg);

	for (i=0; i<len; i++)
	{
		buffer_ssd2832_data2spi4(SSD2832_WRITE_DATA_BYTE, data[i]);
	}
	


	return 0;
}


void buffer_ssd2832_data2spi4(uint8_t cmd,uint16_t value)
{
	uint8_t tempbuf[4];
	tempbuf[0]=cmd;
	tempbuf[1]=value>>8;
	tempbuf[2]=value&0xff;
	bridge_spi_write(tempbuf,sizeof(uint8_t)+sizeof(uint16_t));
	
}



void write_ssd2832_reg(uint16_t reg, uint16_t value)
{
	buffer_ssd2832_data2spi4(SSD2832_WRITE_COMMAND_BYTE, reg);
	buffer_ssd2832_data2spi4(SSD2832_WRITE_DATA_BYTE, value);
}

void dsc_write(uint16_t *data,uint16_t len)
{
   write_ssd2832_reg(0x00b7,0x000342);
	 write_ssd2832_reg(0x00bd,len>>16);
		write_ssd2832_reg(0x00bc,len);
	spi_write_ssd2832_reg_len( 0xbf, data,len);
}



/******************************************************************************/
/// Description:mipi_read_mult_data
/// @note:
/// @param input: pmipi, frame, len
/// @param output:null
/// @return value
/******************************************************************************/

/*
int mipi_read_mult_data(struct mipi_port *pmipi, uint8_t *frame,uint32_t len)
{
	uint16_t rb6 = 0;
	uint16_t rb7 = 0;
    uint32_t video_is_enable = 0;

    uint32_t tmp = 0;
	uint32_t tmp_mem_b6 = 0;
	uint32_t tmp_last_b6 = 0;
	uint32_t tmp_mem_b7 = 0;
	uint32_t tmp_last_b7 = 0;
	uint32_t tmp_mem_de = 0;
	uint32_t i = 0;
    int port = 0;
	
	port = pmipi->port;

	if(len > 0)
	{
		//Set MIPITX
		r16_ssd2832reg_cmd(0xDE,1, &tmp_mem_de);

		if(pmipi->dual & 0x02)//MIPI TX1
		{
			tmp_mem_de |= (0x01 << 7);
		}

		if(pmipi->dual & 0x01)//MIPI TX0
		{
			tmp_mem_de &= 0xFFFFFF7F;
		}

		r16_ssd2832reg_cmd( 0xDE, 1, &tmp);
		if(tmp_mem_de != tmp)
		{
			w16_WriteSSD2832Reg(0xDE,tmp_mem_de);
		}

		r16_ssd2832reg_cmd( 0xB6, 1, &tmp_mem_b6);
		tmp_last_b6 = tmp_mem_b6;
		r16_ssd2832reg_cmd( 0xB7, 1, &tmp_mem_b7);
		tmp_last_b7 = tmp_mem_b7;

		rb6 = (tmp_mem_b6 & 0xFFFFFFFF);
		rb7 = (tmp_mem_b7 & 0xFFFF);
		//Set REN bit, Set to READ
		rb7 |= 0x0080;

		if(rb7 & 0x0008)
		{
			video_is_enable = 1;
		}
		//2. Check dataType
		switch(pmipi->data_type)
		{
			case 0x06:
			{
				//GenericRead
				if(video_is_enable)
				{
					rb7 = (0x03<<8) |(0xC2 & 0xEF) | 0x0B;    //original settings
				}
				else if(pmipi->hs_or_lp)
				{
					rb7 = (0x03<<8) | (0xC2 & 0xEF) | 0X03;
				}
				else
				{
					rb7 = 0x03C2; //LP DCS read
				}
			}
			break;
			case 0x04:
			case 0x14:
			case 0x24:
			{
				//GenericRead
				if(video_is_enable)
				{
					rb7 = (0x03 << 8)|(0x82 & 0xEF) | 0x0B; //original settings
				}
				else if(pmipi->hs_or_lp)
				{
					rb7 = (0x03 << 8)|(0x82 & 0xEF) | 0X03;
				}
				else
				{
					rb7 = 0x0382; //LP generic read
				}
			}
			break;
			default:return -1;
		}

		//4. HS Mode
		if(pmipi->hs_or_lp)
		{
			rb7 |= 0x0001;
			rb6 &= ~0x0040;//Non video data will be transmitted using HS mode.
		}
		else
		{
			rb7 &= ~0x0001;
			rb6 |= 0x0040; //Non video data will be transmitted using LP mode.
		}

		 //Clock lane will enter HS mode for all the cases
		rb7 |= 0x0002;

		//7. Write rb6, rb7
		tmp_mem_b6 &= 0xFFFF0000;
		tmp_mem_b6 |= rb6;
		if(tmp_last_b6 != tmp_mem_b6)
		{
			w16_WriteSSD2832Reg(0xB6,tmp_mem_b6);			
		}

		tmp_mem_b7 &= 0xFFFF0000;
		tmp_mem_b7 |= rb7;
		if(tmp_last_b7 != tmp_mem_b7)
		{
			w16_WriteSSD2832Reg(0xB7,tmp_mem_b7);	
		}

		//Set 0xC1 Maximum Return Size Register
		tmp = len;
		w16_WriteSSD2832Reg(0xC1,tmp);

		//cancel operation to clear data in the buffer, some delay may required for CPHY panel
		w16_WriteSSD2832Reg(0xC0,0x0001);

		//SET Packet Size Control Register 1 (Transmit Data Count, TDC)
		tmp = 0x0001;
		w16_WriteSSD2832Reg(0xBC,tmp);	//Transmit Data Count Low

		//4. Generic Packet Drop Register
		tmp = pmipi->addr;

		w16_WriteSSD2832Reg(0xBF,tmp);

		msleep(50);
		
	
		r16_ssd2832reg_cmd(port,0xC6,1,&tmp);

			if(pmipi->dual & 0x02)//MIPI TX1
			{
				tmp = tmp >> 16;
			}

			if((( tmp & 0x0001) == 0))
			{
				//FAILED, RETRY
				log_info("check reg 0xC6,fail1,0x%08X\n",tmp);
				msleep(30);

				r16_ssd2832reg_cmd(port,0xC6,1,&tmp);

				if(pmipi->dual & 0x02)//MIPI TX1
				{
					tmp =  tmp >> 16;
				}

				if((( tmp & 0x0001) == 0))
				{
					//FAILED, RETRY
					log_info("check reg 0xC6,fail2,0x%08X\n",tmp);				
					return -1;

				}
			
			}
			*//*
		//5.Read
		msleep(50);
		r_ssd2832_mipi_data(0xFF,frame,len);
		return len;
	}
	return 0;
}
*/

/******************************************************************************/
/// Description:mipi_write_mult_data
/// @note:
/// @param input: pmipi, frame, len
/// @param output:null
/// @return value
/******************************************************************************/
/*
int mipi_write_mult_data(struct mipi_port *pmipi, uint8_t *frame,uint32_t len)
{
	uint16_t rb6 = 0;
	uint16_t rb7=0x0100;
	uint32_t tmp = 0;
	uint32_t tmp_mem_b6 = 0;
	uint32_t tmp_mem_b7 = 0;
	uint32_t tmp_mem_de = 0;
    int port = 0;
	
	port = pmipi->port;

	// //Set MIPITX
	// r16_ssd2832reg_cmd(port, 0xDE, 1, &tmp_mem_de);
	// tmp_mem_de &= 0xFFFFFF9F;
	
    // if(pmipi->dual & 0x01)//MIPI TX0
    // {
    //     tmp_mem_de |= (0x01 << 5);
    // }
	
    // if(pmipi->dual & 0x02)//MIPI TX1
    // {
    //     tmp_mem_de |= (0x01 << 6);
    // }

	int temp = 0;
	// r16_ssd2832reg_cmd(port, 0xDE, 1, &temp);
    // if(tmp_mem_de != temp)
    // {
	// 	w16_WriteSSD2832Reg(port,0xDE,tmp_mem_de);
    // }
	// w16_WriteSSD2832Reg(port,0xDE,tmp_mem_de);

    //Transmit Data Count High
	r16_ssd2832reg_cmd( 0xBD, 1, &temp);
	if(temp != 0)
	{
		w16_WriteSSD2832Reg(0xBD,0);
	}
/////////////////////////////////////////////////////////////////////////////
	r16_ssd2832reg_cmd( 0xB6, 1, &tmp_mem_b6);
	r16_ssd2832reg_cmd( 0xB7, 1, &tmp_mem_b7);

	rb6 = (tmp_mem_b6 & 0x0000FFFF);
	rb7 = (tmp_mem_b7 & 0x0000FFFF);

	//Clear REN bit, Set to Write
	rb7 &= ~0x0080;

	//1. Set Transmit Data Count (TDC)
	w16_WriteSSD2832Reg(0xBC,len);

	//2. Check dataType
	switch(pmipi->data_type)
	{
		//DCS SHORT WRITE
		case 0x05:
		case 0x15:
		{
			//Clear LPE(bit10) - Long Packet Enable, Set to short
			rb7 &= ~0x0400;
			//Clear OTHER_CMD(bit12) - Other Command, set to DCS or Generic
			rb7 &= ~0x1000;
			//Set DCS(bit 6) - DCS or Generic, set to DCS
			rb7 |= 0x0040;
		}
		break;
		//DCS LONG WRITE
		case 0x39:
		{
			//Set LPE(bit10) - Long Packet Enable, Set to Long
			rb7 |= 0x0400;
			//Clear OTHER_CMD(bit12) - Other Command, set to DCS or Generic
			rb7 &= ~0x1000;
			//Set DCS(bit 6) - DCS or Generic, set to DCS
			rb7 |= 0x0040;
		}
		break;
		//Generic short WRITE
		case 0x13:
		case 0x23:
		{
			//Clear LPE(bit10) - Long Packet Enable, Set to short
			rb7 &= ~0x0400;
			//Clear OTHER_CMD(bit12) - Other Command, set to DCS or Generic
			rb7 &= ~0x1000;
			//Set DCS(bit 6) - DCS or Generic, set to Generic
			rb7 &= ~0x0040;
		}
		break;
		//Generic Long WRITE
		case 0x29:
		{
			//Set LPE(bit10) - Long Packet Enable, Set to Long
			rb7 |= 0x0400;
			//Clear OTHER_CMD(bit12) - Other Command, set to DCS or Generic
			rb7 &= ~0x1000;
			//Set DCS(bit 6) - DCS or Generic, set to Generic
			rb7 &= ~0x0040;
		}
		break;
		//Compression Mode Command, Short Write
		case 0x07:
		{
			//Clear LPE(bit10) - Long Packet Enable, Set to short
			rb7 &= ~0x0400;
			//Set OTHER_CMD(bit12) - Other Command, set to DCS bit defines PPS or Compression mode packet.
			rb7 |= 0x1000;
			//Set DCS(bit 6) - DCS or Generic, 0 ?C Picture Parameter Setting Packet 1 ?C Compress Mode Packet
			rb7 |= 0x0040;
		}
		//Picture Parameter Set, Long Write
		case 0x0A:
		{
			//Set LPE(bit10) - Long Packet Enable, Set to Long
			rb7 |= 0x0400;
			//Set OTHER_CMD(bit12) - Other Command, set to DCS bit defines PPS or Compression mode packet.
			rb7 |= 0x1000;
			//Set DCS(bit 6) - DCS or Generic, 0 ?C Picture Parameter Setting Packet 1 ?C Compress Mode Packet
			rb7 &= ~0x0040;
		}
		default:
		{
			return -1;
		}
	}

	//4. HS Mode
	if(pmipi->hs_or_lp)
	{
		rb6 &= ~0x0040;//Non video data will be transmitted using HS mode.
		rb7 |= 0x0001;
	}
	else
	{
		rb6 |= 0x0040; //Non video data will be transmitted using LP mode.
		rb7 &= ~0x0001;
	}

	//6. Check if Video Mode is ON
	if(rb7 & 0x0008)
	{
		//1  - Video mode is enabled
		rb7 |= 0x0009; //Control SSD2828 use HS mode to send data.
	}
	//7. Write rb6, rb7
	tmp_mem_b6 &= 0xFFFF0000;
	tmp_mem_b6 |= rb6;

	w16_WriteSSD2832Reg(port,0xB6,tmp_mem_b6);

	tmp_mem_b7 &= 0xFFFF0000;
	tmp_mem_b7 |= rb7;
	w16_WriteSSD2832Reg(port,0xB7,tmp_mem_b7);

	//8. Generic Packet Drop Register
	w_ssd2832_mipi_data( port, 0xBF, frame, len);
 
	return 0;
}



/////////////////////////////////////////////////////////////////////////////
int r_ssd2832_mipi_data(uint8_t addr, uint8_t *data, uint32_t len)
{
	uint32_t i = 0;
	int count = 0, ssd_cmd_len = 0;
	unsigned char read_16byte[4] = {0}, read_32byte[4] = {0};

	//�ѧE�r?
    count = len % MIPI_PACKAGE_LEN;
	//ssd write len 
	// ssd_cmd_len = (len + MIPI_PACKAGE_LEN)/MIPI_PACKAGE_LEN;
	ssd_cmd_len = len/MIPI_PACKAGE_LEN;
    if (count > 0)
	{
		ssd_cmd_len++;
	}
	
	//cmd_total
	fpga_w_cmd_total(ssd_cmd_len);
	//cmd_len
	fpga_w_cmd_len(ssd_cmd_len);

	if(port > 0)  	//bridge B = 1
	{
		//cmd_addr
		fpga_w_msb_regaddr(addr);	
		usleep(100);
		//�ԧCbridge��CS
		bridge_spi_cs_enable(0);
		usleep(2000);
		//?cmd_start?0x02�M�Z?buffer_dat�H�s��
		fpga_w_cmd_start(0x02);
		usleep(2000);
		//?�u?��
		for(i = 0; i< ssd_cmd_len; i++)
		{
			memset(read_16byte,0,4);
			memset(read_32byte,0,4);

			fpga_r_spi_dout_msb_data(read_16byte);
			fpga_r_spi_dout_msb32_data(read_32byte);

			data[i*MIPI_PACKAGE_LEN+0] = read_16byte[0];
			data[i*MIPI_PACKAGE_LEN+1] = read_16byte[1];
			data[i*MIPI_PACKAGE_LEN+2] = read_32byte[0];
			data[i*MIPI_PACKAGE_LEN+3] = read_32byte[1];
			data[i*MIPI_PACKAGE_LEN+4] = read_32byte[2];
			data[i*MIPI_PACKAGE_LEN+5] = read_32byte[3];
			usleep(100);
		}	
		bridge_spi_cs_enable(1);
		usleep(100);
	}
	else			//bridge A = 0
	{
		//cmd_addr
 		fpga_w_lsb_regaddr(addr);   
		usleep(100);
		//�ԧCbridge��CS
		bridge_spi_cs_enable(0);
		usleep(2000);
		//?cmd_start?0x02�M�Z?buffer_dat�H�s��
		fpga_w_cmd_start(0x02);
		usleep(2000);
		//?�u?��	
		for(i = 0; i < ssd_cmd_len; i++)
		{
			memset(read_16byte,0,4);
			memset(read_32byte,0,4);

			fpga_r_spi_dout_lsb_data(read_16byte);
			printf("\r\n%s,lsb,%02X,%02X,%02X,%02X",__func__,read_16byte[0],read_16byte[1],read_16byte[2],read_16byte[3]);
			fpga_r_spi_dout_lsb32_data(read_32byte);
			printf("\r\n%s,lsb32,%02X,%02X,%02X,%02X",__func__,read_32byte[0],read_32byte[1],read_32byte[2],read_32byte[3]);

			data[i*MIPI_PACKAGE_LEN+0] = read_16byte[3];
			data[i*MIPI_PACKAGE_LEN+1] = read_16byte[2];
			data[i*MIPI_PACKAGE_LEN+2] = read_32byte[3];
			data[i*MIPI_PACKAGE_LEN+3] = read_32byte[2];
			data[i*MIPI_PACKAGE_LEN+4] = read_32byte[1];
			data[i*MIPI_PACKAGE_LEN+5] = read_32byte[0];

			printf("\r\n%s,data[0-5],%02X,%02X,%02X,%02X,%02X,%02X\r\n",__func__, \
			                         read_16byte[0],read_16byte[1], \
									 read_32byte[0],read_32byte[1],read_32byte[2],read_32byte[3]);
			usleep(100);
		}	
		usleep(1000);
		bridge_spi_cs_enable(1);
		usleep(100);
	}

    return 1;
}



/////////////////////////////////////////////////////////////////////////////
int w_ssd2832_mipi_data( uint8_t addr, uint8_t *data, uint32_t len)
{
  	int i = 0;
    int count = 0, ssd_cmd_len = 0;
	uint32_t bridge_write_data16_l = 0, bridge_write_data32_h  = 0;

	if(len == 0)
	{
		printf("w_ssd2832_mipi_data len = 0 \r\n");
		return -1;
	}

	//�ѧE�r?
    count = len % MIPI_PACKAGE_LEN;
	//ssd write len 
	ssd_cmd_len = (len + MIPI_PACKAGE_LEN)/MIPI_PACKAGE_LEN;

	//printf("count = %d,  ssd_cmd_len = %d \r\n",count, ssd_cmd_len);

	//cmd_total 	
	fpga_w_cmd_total(ssd_cmd_len);
	//cmd_len
	fpga_w_cmd_len(ssd_cmd_len);

	if(port > 0)  	//bridge B = 1
	{
		//cmd_clr
		fpga_w_msb_clear(1);
		//cmd_addr
		fpga_w_msb_regaddr(addr);
		usleep(100);
		//data
		for(i = 0; i < len - count; i += MIPI_PACKAGE_LEN)
		{
			bridge_write_data16_l = (data[i+1]<<8) | data[i];
			fpga_w_buffer_msbdat(bridge_write_data16_l);		
			bridge_write_data32_h = (data[i+5]<<24) | (data[i+4]<<16) | (data[i+3]<<8) | (data[i+2]);
			fpga_w_buffer_msbdat_32(bridge_write_data32_h);

			// printf(" i = %d, addr = %02x, bridge_write_data16_l = %04x \r\n", i, addr, bridge_write_data16_l); 
			// printf(" i = %d, addr = %02x, bridge_write_data32_h = %08x \r\n", i, addr, bridge_write_data32_h); 
		}

		if(count)
		{
			bridge_write_data16_l = (count >= 1) ? data[i] : 0;
			bridge_write_data16_l |= ((count >= 2) ? (data[i+1]<<8) : 0);	
			fpga_w_buffer_msbdat(bridge_write_data16_l);	
			
			bridge_write_data32_h = (count >= 3) ? data[i+2] : 0;
			bridge_write_data32_h |= (count>=4) ? (data[i+3]<<8) : 0;
			bridge_write_data32_h |= (count>=5) ? (data[i+4]<<16) : 0;
		//	bridge_write_data16_h | = (count>=2) ? (data[i+5]<<24) : 0;			
			fpga_w_buffer_msbdat_32(bridge_write_data32_h);

			// printf(" count = %d, addr = %02x, bridge_write_data16_l = %04x \r\n", count, addr, bridge_write_data16_l); 
			// printf(" count = %d, addr = %02x, bridge_write_data32_h = %08x \r\n", count, addr, bridge_write_data32_h); 
		}
		usleep(100);		
		//�ԧCbridge��CS
		bridge_spi_cs_enable(0);
		//cmd_start?0x01
		fpga_w_cmd_start(0x01);
		usleep(2000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(1);
		usleep(100);
	}	
	else     //bridge A = 0
	{
		//cmd_clr
		fpga_w_lsb_clear(1);
		//cmd_addr
		fpga_w_lsb_regaddr(addr);
		usleep(100);
		//data
		for(i = 0; i < len - count; i += MIPI_PACKAGE_LEN)
		{
			bridge_write_data16_l = (data[i+1]<<8) | data[i];
			fpga_w_buffer_lsbdat(bridge_write_data16_l);		
			bridge_write_data32_h = (data[i+5]<<24) | (data[i+4]<<16) | (data[i+3]<<8) | (data[i+2]);
			fpga_w_buffer_lsbdat_32(bridge_write_data32_h);

			// printf(" i = %d, addr = %02x, bridge_write_data16_l = %04x \r\n", i, addr, bridge_write_data16_l); 
			// printf(" i = %d, addr = %02x, bridge_write_data32_h = %08x \r\n", i, addr, bridge_write_data32_h); 
		}

		if(count)
		{
			bridge_write_data16_l = (count >= 1) ? data[i] : 0;
			bridge_write_data16_l |= ((count >= 2) ? (data[i+1]<<8) : 0);	
			fpga_w_buffer_lsbdat(bridge_write_data16_l);	
			
			bridge_write_data32_h = (count >= 3) ? data[i+2] : 0;
			bridge_write_data32_h |= (count>=4) ? (data[i+3]<<8) : 0;
			bridge_write_data32_h |= (count>=5) ? (data[i+4]<<16) : 0;
		//	bridge_write_data16_h |= (count>=2) ? (data[i+5]<<24) : 0;			
			fpga_w_buffer_lsbdat_32(bridge_write_data32_h);

			// printf(" count = %d, addr = %02x, bridge_write_data16_l = %04x \r\n", count, addr, bridge_write_data16_l); 
			// printf(" count = %d, addr = %02x, bridge_write_data32_h = %08x \r\n", count, addr, bridge_write_data32_h); 
		}

		usleep(100);			
		//�ԧCbridge��CS
		bridge_spi_cs_enable(0);
		//cmd_start?0x01
		fpga_w_cmd_start(0x01);
		usleep(2000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(1);
		usleep(100);
	}

	return 1;
}

/////////////////////////////////////////////////////////////////////////////
void w16_ssd2832reg_cmd(uint8_t port, uint32_t addr, uint32_t len, uint32_t* data)
{	
	uint32_t i = 0;

 	//cmd_total 
	fpga_w_cmd_total(len);
	//cmd_len
	fpga_w_cmd_len(len);

	if(port > 0)  	//bridge B = 1
	{
		//cmd_clr
		fpga_w_msb_clear(1);
		//cmd_addr
		fpga_w_msb_regaddr(addr);
		usleep(100);
		//data
		for(i = 0; i< len; i++)
		{
			fpga_w_buffer_msbdat(data[i]);
			printf("w16_ssd2832reg_cmd write addr=%0x, data =%0x\r\n", addr, data[i]);
		}
		usleep(100);		
		//�ԧCbridge��CS
		bridge_spi_cs_enable(port,0);
		//cmd_start?0x01
		fpga_w_cmd_start(0x01);
		usleep(2000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(port,1);
		usleep(100);
	}	
	else			//bridge A = 0
	{
		//cmd_clr
		fpga_w_lsb_clear(1);
		//cmd_addr
		fpga_w_lsb_regaddr(addr);
		usleep(100);
		//data
		for(i = 0; i< len; i++)
		{
			fpga_w_buffer_lsbdat(data[i]);
			printf("w16_ssd2832reg_cmd write addr=%0x, data =%0x\r\n", addr, data[i]);
		}
		usleep(100);			
		//�ԧCbridge��CS
		bridge_spi_cs_enable(0);
		//cmd_start?0x01
		fpga_w_cmd_start(0x01);
		usleep(2000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(1);
		usleep(100);
	}

}



void w16_WriteSSD2832Reg(uint32_t addr, uint32_t data)
{	
	uint32_t i = 0;

 	//cmd_total 
	fpga_w_cmd_total(1);
	//cmd_len
	fpga_w_cmd_len(1);

	if(port > 0)  	//bridge B = 1
	{
		//cmd_clr
		fpga_w_msb_clear(1);
		//cmd_addr - before
		fpga_w_msb_regaddr(addr);
		usleep(100);
		//data - after
		fpga_w_buffer_msbdat(data);
		usleep(100);
		//�ԧCbridge��CS
		bridge_spi_cs_enable(0);
		//cmd_start?0x01
		fpga_w_cmd_start(0x01);
		usleep(2000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(1);
		usleep(100);
	}	
	else			//bridge A = 0
	{
		//cmd_clr
		fpga_w_lsb_clear(1);		
		//cmd_addr
		fpga_w_lsb_regaddr(addr);
		usleep(100);	
		//data
		fpga_w_buffer_lsbdat(data);
		usleep(100);
		//�ԧCbridge��CS
		bridge_spi_cs_enable(0);
		//cmd_start?0x01
		fpga_w_cmd_start(0x01);
		usleep(2000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(1);	
	}
	usleep(100);	
	printf("w16_WriteSSD2832Reg(%0x, %0x);\r\n", addr, data);
}

//read SSD2832 Register, return U32 data
uint32_t r_SSD2832_LocalReg( uint32_t addr)
{
	int len = 1;
	uint8_t temp_arr[4] = {0};
	int i;
	//cmd_total 
	fpga_w_cmd_total(len);
	//cmd_len
	fpga_w_cmd_len(len);

	uint32_t data = 0;

	if(port > 0)  	//bridge B = 1
	{
		//cmd_addr
		fpga_w_msb_regaddr(addr);	
		//�ԧCbridge��CS
		bridge_spi_cs_enable(port,0);
		usleep(100);
		//?cmd_start?0x02�M�Z?buffer_dat�H�s��
		fpga_w_cmd_start(0x02);
		usleep(2000);
		//?�u?��
		for(i = 0; i < len; i++)
		{
			fpga_r_spi_dout_msb_data(temp_arr);//local register, 16bit wide
			//data[i] = (temp_arr[0]<<24) | (temp_arr[1]<<16) | (temp_arr[2]<<8) | (temp_arr[3]);
			printf("cmd read addr = %x, value [%d] = [%02x,%02x,%02x,%02x]\r\n", addr,i, temp_arr[0],temp_arr[1],temp_arr[2],temp_arr[3]);
		}		
		bridge_spi_cs_enable(port,1);
		usleep(100);
	}
	else			//bridge A = 0
	{
		//cmd_addr
 		fpga_w_lsb_regaddr(addr);   
		usleep(100);
		//�ԧCbridge��CS
		bridge_spi_cs_enable(port,0);
		usleep(1000);
		//?cmd_start?0x02�M�Z?buffer_dat�H�s��
		fpga_w_cmd_start(0x02);
		usleep(2000);
		//?�u?��
		for(i = 0; i < len; i++)
		{
			fpga_r_spi_dout_lsb_data(temp_arr);
			//data[i] = (temp_arr[0]<<24) | (temp_arr[1]<<16) | (temp_arr[2]<<8) | (temp_arr[3]);
			printf("cmd read addr = %x, value[%d] = [%02x,%02x,%02x,%02x]\r\n", addr,i, temp_arr[0],temp_arr[1],temp_arr[2],temp_arr[3]);
		}
		usleep(1000);
		bridge_spi_cs_enable(port,1);
		usleep(100);
	}
	//?�]
	data = ((temp_arr[0]<<24)|(temp_arr[1]<<16)|(temp_arr[2]<<8)|temp_arr[3]);
	  
	return data;
}
/////////////////////////////////////////////////////////////////////////////
void r16_ssd2832reg_cmd(uint8_t port, uint32_t addr, uint32_t len, uint32_t* data)
{	
	uint8_t temp_arr[4] = {0};
	uint32_t i = 0;

	//cmd_total 
	fpga_w_cmd_total(len);
	//cmd_len
	fpga_w_cmd_len(len);

	if(port > 0)  	//bridge B = 1
	{
		//cmd_addr
		fpga_w_msb_regaddr(addr);	
		usleep(100);
		//�ԧCbridge��CS
		bridge_spi_cs_enable(port,0);
		usleep(1000);
		//?cmd_start?0x02�M�Z?buffer_dat�H�s��
		fpga_w_cmd_start(0x02);
		usleep(2000);
		//?�u?��
		for(i = 0; i< len; i++)
		{
			fpga_r_spi_dout_msb_data(temp_arr);
			data[i] = (temp_arr[0]<<24) | (temp_arr[1]<<16) | (temp_arr[2]<<8) | (temp_arr[3]);
			printf("cmd read addr = %x, value= %08x\r\n", addr,data[i]);
			usleep(100);
		}		
		bridge_spi_cs_enable(port,1);
		usleep(100);
	}
	else			//bridge A = 0
	{
		//cmd_addr
 		fpga_w_lsb_regaddr(addr);   
		usleep(100);
		//�ԧCbridge��CS
		bridge_spi_cs_enable(port,0);
		usleep(1000);
		//?cmd_start?0x02�M�Z?buffer_dat�H�s��
		fpga_w_cmd_start(0x02);
		usleep(2000);
		//?�u?��
		for(i = 0; i < len; i++)
		{
			fpga_r_spi_dout_lsb_data(temp_arr);
			data[i] = (temp_arr[0]<<24) | (temp_arr[1]<<16) | (temp_arr[2]<<8) | (temp_arr[3]);
			printf("cmd read addr = %x,value= %08x\r\n", addr,data[i]);
		}
		usleep(1000);
		bridge_spi_cs_enable(port,1);
		usleep(100);
	}
}




int dcs_read_mipi_data(uint8_t port,uint16_t addr, uint16_t len, char *out)
{
	int value;
	int try_num = 0;
	uint32_t b7_reg;
    printf("\r\n%s,start\r\n",__func__);

	b7_reg = r_SSD2832_LocalReg(port,0x00B7);
	
	w16_WriteSSD2832Reg(port,0x00c1, len);
	w16_WriteSSD2832Reg(port,0x00c0, 0x01);
	w16_WriteSSD2832Reg(port,0x00B7, 0x03c2);
	w16_WriteSSD2832Reg(port,0x00BD, 0x00);
	w16_WriteSSD2832Reg(port,0x00bc, 0x01);
	w16_WriteSSD2832Reg(port,0x00bf, addr);
	usleep(10000);
	
	value = r_SSD2832_LocalReg(port,0x00c6);

	while (((value & 0x01) == 0) && (try_num < 100))
	{
		usleep(1000);
		value = r_SSD2832_LocalReg(port,0x00c6);	
		try_num ++;
	}
		
	if (try_num >= 100)
	{
		w16_WriteSSD2832Reg(port,0x00B7, b7_reg);
		printf("%s, timetout, try_num = %d\r\n", __func__, try_num);
		return -1;
	}

	//?�h??�u
	r_ssd2832_mipi_data(port,0x00ff, out,len);

	w16_WriteSSD2832Reg(port,0x00B7, b7_reg);

	return 0;
}




int generic_read_mipi_data(uint8_t port, uint16_t addr, uint16_t len, char *out)
{
	int value;
	int try_num = 0;
	uint32_t b7_reg;

	b7_reg = r_SSD2832_LocalReg(port,0x00B7);
	
	w16_WriteSSD2832Reg(port,0x00c1, len);
	w16_WriteSSD2832Reg(port,0x00c0, 0x01);
	w16_WriteSSD2832Reg(port,0x00B7, 0x0382);
	w16_WriteSSD2832Reg(port,0x00BD, 0x00);
	w16_WriteSSD2832Reg(port,0x00bc, 0x01);
	w16_WriteSSD2832Reg(port,0x00bf, addr);
	usleep(10000);
	
	value = r_SSD2832_LocalReg(port,0x00c6);

	while (((value & 0x01) == 0) && (try_num < 100))
	{
		usleep(1000);
		value = r_SSD2832_LocalReg(port,0x00c6);	
		try_num ++;
	}
		
	if (try_num >= 100)
	{
		w16_WriteSSD2832Reg(port,0x00B7, b7_reg);
		printf("%s, timetout, try_num = %d\r\n", __func__, try_num);
		return -1;
	}

	//?�h??�u
	r_ssd2832_mipi_data(port,0x00ff, out,len);

	w16_WriteSSD2832Reg(port,0x00B7, b7_reg);

	return 0;
}
*/

/*
*��?�W : SSD2832_GenericLongWrite
*�y�z   : DT = 0x29��?�ާ@?�m
*??   : n - ?���r??
*��^   : ?
*//*
void SSD2832_GenericLongWrite(unsigned char *arr, int len)
{ 
	w16_WriteSSD2832Reg(0,0xB7,0x0610);	
	usleep(100000);
	w16_WriteSSD2832Reg(0,0xBc,len&0xffff);	
	w16_WriteSSD2832Reg(0,0xbd,len>>16);
	w_ssd2832_mipi_data(0, 0xBF, arr, len);
}
//05/15

void SSD2832_DcsShortWrite(unsigned char *arr, int len)
{ 
   	w16_WriteSSD2832Reg(0,0x00b7,0x0250);	  //EOT Packet Enable,ECC CRC Check Enable, DCS, Short packer, LP	
	usleep(100000);
	w16_WriteSSD2832Reg(0,0xbc,len);
	w16_WriteSSD2832Reg(0,0xbd,0x00);
    w_ssd2832_mipi_data(0, 0xBF, arr, len);
    
}


void SSD2832_CMD_SEND_IMAGE_LINE_MODE(uint8_t port, uint32_t W, uint32_t H, uint32_t addr)
{	
	uint32_t i = 0;

	w16_WriteSSD2832Reg(port,0xbc,W * 3);
	w16_WriteSSD2832Reg(port,0xbd,0);
	w16_WriteSSD2832Reg(port,0xbe,W * 3);
	fpga_w_cmd_delay(200);
 	//cmd_total 
	fpga_w_cmd_total(W*H/2);
	//cmd_len
	fpga_w_cmd_len(W/2);

	if(port > 0)  	//bridge B = 1
	{
		//cmd_clr
		fpga_w_msb_clear(1);
		//cmd_addr - before
		fpga_w_mipi_rd_addr(addr);
		usleep(100);
		//�ԧCbridge��CS
		bridge_spi_cs_enable(port,0);
		//cmd_start?0x04
		fpga_w_cmd_start(0x04);
		usleep(1000000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(port,1);
		usleep(100);
	}	
	else			//bridge A = 0
	{
		//cmd_clr
		fpga_w_lsb_clear(1);		
		//cmd_addr
		fpga_w_mipi_rd_addr(addr);
		usleep(100);	
		//data
		//�ԧCbridge��CS
		bridge_spi_cs_enable(port,0);
		//cmd_start?0x04
		fpga_w_cmd_start(0x04);
		usleep(100000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(port,1);
		usleep(100);
	}

	printf("SSD2832_CMD_SEND_IMAGE_LINE_MODE(%d, %d, %d, %X);\r\n", port, W, H, addr);
}

void SSD2832_CMD_SEND_IMAGE_FRAME_MODE(uint8_t port, uint32_t W, uint32_t H, uint32_t addr)
{	
	uint32_t i = 0;
	uint32_t len = W * H * 3;
	w16_WriteSSD2832Reg(port,0xbc,len&0xffff);
	w16_WriteSSD2832Reg(port,0xbd,len>>16);
	w16_WriteSSD2832Reg(port,0xbe,W * 3);
 	//cmd_total 
	fpga_w_cmd_total(W*H/2);
	//cmd_len
	fpga_w_cmd_len(W/2);


	if(port > 0)  	//bridge B = 1
	{
		//cmd_clr
		fpga_w_msb_clear(1);
		//cmd_addr - before
		fpga_w_mipi_rd_addr(addr);
		usleep(100);
		//�ԧCbridge��CS
		bridge_spi_cs_enable(port,0);
		//cmd_start?0x14
		fpga_w_cmd_start(0x14);
		usleep(1000000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(port,1);
		usleep(100);
	}	
	else			//bridge A = 0
	{
		//cmd_clr
		fpga_w_lsb_clear(1);		
		//cmd_addr
		fpga_w_mipi_rd_addr(addr);
		usleep(100);	
		//data
		//�ԧCbridge��CS
		bridge_spi_cs_enable(port,0);
		//cmd_start?0x14
		fpga_w_cmd_start(0x14); 
		usleep(100000);
		//�԰�bridge��CS
		bridge_spi_cs_enable(port,1);
		usleep(100);
	}
		
	printf("SSD2832_CMD_SEND_IMAGE_PARTITION_MODE(%d, %d, %d, %X);\r\n", port, W, H, addr);
}
*/