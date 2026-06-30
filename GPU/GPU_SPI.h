#ifndef __GUP_SPI_H
#define __GUP_SPI_H
#include "gd32f30x.h"
#include "systick.h"
#include "bsp_lcd.h"
#include "timer.h"
#include "GPU_Cfg.h"


#define GPU_SPI_BASE   0x70

#define GPU_SPI_CTRLL   0x00
#define GPU_SPI_CTRLH   0x01

#define GPU_SPI_DATAL   0x02
#define GPU_SPI_DATAH   0x03


#define GPU_SPI_RDATAL   0x04
#define GPU_SPI_STATUS   0x05

#define GPU_SPI_DIV   		0x06  //feq=100000000/GPU_SPI_DIV*2  
#define GPU_SPI_MODE   		0x07
// Parameters:  SPI_MODE, can be 0, 1, 2, or 3.  See above.
//              Can be configured in one of 4 modes:
//              Mode | Clock Polarity (CPOL/CKP) | Clock Phase (CPHA)
//               0   |             0             |        0
//               1   |             0             |        1
//               2   |             1             |        0
//               3   |             1             |        1
//              More: https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Mode_numbers
//  			CPOL: Clock Polarity
// 				CPOL=0 means clock idles at 0, leading edge is rising edge.
// 				CPOL=1 means clock idles at 1, leading edge is falling edge.
// 				CPHA: Clock Phase
//				 CPHA=0 means the "out" side changes the data on trailing edge of clock
//              		the "in" side captures data on leading edge of clock
// 				CPHA=1 means the "out" side changes the data on leading edge of clock
//              		the "in" side captures data on the trailing edge of clock
//
//	Note:		CLKS_PER_HALF_BIT must not be less than 1.
void spi_cs(uint8_t lever);
uint8_t spi_send_byte(uint8_t data);
void spi_wr_en(void);	
void setspi(uint8_t spimode,uint8_t hold,uint8_t dir,uint8_t len);
uint8_t spi_read_byte(void);
void spi_write(uint8_t *data,uint8_t len);
void spi_read(uint8_t *wrbuf,uint8_t wlen,uint8_t *rbuf,uint8_t rlen);
void spi_set_spispeed(uint16_t Mhz);
void spi_set_spimode(uint8_t mode);





#endif

