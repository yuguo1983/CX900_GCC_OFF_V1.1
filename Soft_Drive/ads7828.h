/*

Library for the TI ADS7828 12bits i2C ADC
12 bit A/D converter 3.3 volt

I2C-ADS ADS7828 Device Adress 0x48

SD: 0b0 --> differential 
SD: 0b1 --> single ended

Power Down: (PD1=0b1 + PD0=0b1) --> A2D=ON, Int Volt Ref=ON

(SD=0b1) + (1000) + 11 + xx --> single-ended channel 0

Channel 0+ =(1000) + 11 + xx = single ended mode
Channel 1+ =(1100) + 11 + xx = single ended mode
Channel 2+ =(1010) + 11 + xx = single ended mode
Channel 3+ =(1110) + 11 + xx = single ended mode
Channel 4+ =(1001) + 11 + xx = single ended mode
Channel 5+ =(1101) + 11 + xx = single ended mode
Channel 6+ =(1011) + 11 + xx = single ended mode

(SD=0b0) + (1000) + 11 + xx --> differential channel 0-1
Channel 0-1 =(1000) + 11 + xx = differential mode
Channel 2-3 =(1010) + 11 + xx = differential mode
Channel 4-5 =(1100) + 11 + xx = differential mode
Channel 6-7 =(1110) + 11 + xx = differential mode

*/


#include "stdint.h"
#include "ina220.h"

#ifndef ADS7828_H
#define ADS7828_H


	#ifndef bool
		#define bool uint8_t
		#define true 1
		#define false 0
	#endif


#define EXT 0; // External voltage reference
#define INT 1; // Internal voltage reference
#define SD 1; // Single ended mode
#define DF 0; // Differential mode



typedef struct  {
    uint8_t ads7828_address; // ADS7828 address
    
}ads7828_t;

// ads7828 functions

// set the ADS7828 address
void ads7828_set_address( ads7828_t *ads7828, unsigned char address);

// initialize the ads7828
void ads7828_init(ads7828_t *ads7828);

// overload the ads7828_init function to set the channel
void ads7828_init_vref( ads7828_t *ads7828, bool _vref);

// read the ads7828
unsigned int read(unsigned char channel, bool mode);




#endif
