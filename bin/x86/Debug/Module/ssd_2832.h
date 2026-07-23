#ifndef __Mfun_Mipi_Bridge_H__
#define __Mfun_Mipi_Bridge_H__
#include <stdint.h>

struct bridge
{
    uint32_t hsw; //H Sync Width
    uint32_t vsw; //V Sync Width
    uint32_t hbp; //H Back Porch
    uint32_t vbp; //V Back Porch
    uint32_t hfp; //H Front Porch
    uint32_t vfp; //V Front Porch
    uint32_t hact; //H Active
    uint32_t vact; //V Active

    uint32_t hzd;
    uint32_t hpd;
    uint32_t czd;
    uint32_t cpd;
    uint32_t cped;
    uint32_t cptd;
    uint32_t ctd;
    uint32_t htd;

    uint32_t dual;           //0,single,1,dual
    uint32_t lane;           //4lane
    uint32_t video_or_cmd;   //video,command
    uint32_t bits;           //24,18,16
    uint32_t rgb_or_bgr;     //RGB,BGR

    uint32_t pclk_polarity;
    uint32_t de_polarity;    //DE Polarity;0,active low
    uint32_t vsync_polarity; //V Sync Polarity;0,Vsync pulse is active low
    uint32_t hsync_polarity; //H Sync Polarity;0,Hsync pulse is active low
    uint32_t sync_mode;      //Video mode,0,non burst mode with sync pulse
                             //1,non burst mode with sync events
                             //burst mode

	uint32_t split_mode;     //Right-left,Odd-even
	uint32_t clk_lp;         //LP Speed(MHz);low speed
	uint32_t clk_hs;         //HS Speed(MHz);High speed

	uint32_t init_by_hs_mode; //Initialize By HS Mode;
	uint32_t always_keep_hs;  //Always Keep HS Clock
	uint32_t send_eot_in_hs;  //Send EOT Packet in HS Mode
	uint32_t start_video_before_init; //Start Video before Initialzation

	uint32_t virtual_channel;  //virtual channel;
	uint32_t dphy_or_cphy;     //1 - MIPI DPHY, 7 - MIPI CPHY
	uint32_t	mcu_msb_lsb_swap;
	uint32_t	video_msb_lsb_swap;
	uint32_t driver_output_res_ctl ;       //Analog Control Register,BIT28-25,Driver output resistance control
	uint32_t low_power_tx_drive_strength ; //Analog Control Register,BIT24-22,Low Power Transmitter Drive Strength
	uint32_t Voltage_trimming_bits;
	uint32_t post_len ;                    //CPHY Transmit Global Register 1,BIT20-16,The number of symbol in the Post field is:(post_length+1)*7
};

struct mipi_port
{
	uint32_t video_or_cmd;
	uint32_t hs_or_lp;
	uint32_t data_type; //39/29/15/05/14/06
	uint32_t addr;
	uint32_t port;
  uint32_t dual;           //0,single,1,dual
};

#define BRIDGE_PORT_A     (0)
#define BRIDGE_PORT_B     (1)
#define BRIDGE_PORT_COUNT (2)

#define	MIPI_PACKAGE_LEN  (6)
void Read_SSD2832_Id(void);
void SSD2832_GPIO_Init(void);
struct bridge *bridge_get(void);
int bridge_init(void);
int bridge_reg_test(void);
int mipi_write_regs(struct mipi_port *pmipi, uint8_t *frame,uint32_t len);
int bridge_write_reg_32bit(unsigned char addr,uint32_t tmp);
int bridge_write_reg_16bit(unsigned char addr,uint16_t tmp);
int bridge_write_16bit_regs(unsigned char addr,uint16_t *frame, uint16_t count);
int bridge_read_reg(unsigned char addr,uint32_t *temp);
int bridge_read_regs(unsigned char addr,unsigned char *frame,uint32_t len);

int bridge_write_apb_reg(uint16_t addr,uint32_t data);
int bridge_read_apb_reg(uint16_t addr,uint32_t *temp);
int bridge_check_id(void) ;
int bridge_send_cmd_image(void);


int bridge_send_hs_nop_package(void);
int bridge_send_ls_nop_package(void);
uint32_t bridge_read_mem_reg(unsigned char reg);

int bridge_stop_video(void);
int bridge_enter_sleep(void);
int bridge_v2c(unsigned char stage, unsigned int delay);
int bridge_hw_reset(void);


void r16_ssd2832reg_cmd(uint8_t port, uint32_t addr, uint32_t len, uint32_t* data);
void w16_ssd2832reg_cmd(uint8_t port, uint32_t addr, uint32_t len, uint32_t* data);
void w16_WriteSSD2832Reg(uint8_t port, uint32_t addr, uint32_t data);
uint32_t r_SSD2832_LocalReg(uint8_t port, uint32_t addr);

int w_ssd2832_mipi_data(uint8_t port, uint8_t addr, uint8_t *data, uint32_t len);
int r_ssd2832_mipi_data(uint8_t port, uint8_t addr, uint8_t *data, uint32_t len);

int mipi_write_mult_data(struct mipi_port *pmipi, uint8_t *frame,uint32_t len);

void SSD2832_DcsShortWrite(unsigned char *arr, int len);
void SSD2832_CMD_SEND_IMAGE_LINE_MODE(uint8_t port, uint32_t W, uint32_t H, uint32_t addr);
void SSD2832_CMD_SEND_IMAGE_FRAME_MODE(uint8_t port, uint32_t W, uint32_t H, uint32_t addr);

int generic_read_mipi_data(uint8_t port, uint16_t addr, uint16_t len, char *out);

int spi_write_ssd2832_reg_len( uint16_t  reg,  uint16_t *data, int len);
void write_ssd2832_reg(uint16_t reg, uint16_t value);
void dsc_write(uint16_t *data,uint16_t len);
int bridge_setbistmode(int enable);
void bridge_select_phy(uint8_t value);
int bridge_RSTPIN_reset(void);
#endif
