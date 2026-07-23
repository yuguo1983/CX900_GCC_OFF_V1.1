#ifndef __PLL_FREQ_DEF_H
#define __PLL_FREQ_DEF_H

#include "user_config.h"
#include "gd32f30x.h"
#include "GPU_Cfg.h"
#include "timer.h"

#define    FEQ_BASE    0x40 


#define    PLL_EN   	FEQ_BASE+0x13
#define    M_COU_L    FEQ_BASE+0x14
#define    M_COU_H    FEQ_BASE+0x15
#define    N_COU_L    FEQ_BASE+0x16
#define    N_COU_H    FEQ_BASE+0x17
#define    C_COU_L    FEQ_BASE+0x18
#define    C_COU_H    FEQ_BASE+0x19
#define    CH_PU_L    FEQ_BASE+0x1a
#define    CH_PU_H    FEQ_BASE+0x1b
#define    BW_L    		FEQ_BASE+0x1c
#define    BW_H    		FEQ_BASE+0x1d
#define    M_F_L   		FEQ_BASE+0x1e
#define    M_F_H    	FEQ_BASE+0x1f



typedef struct
{
	uint32_t m_counter;
	uint32_t n_counter;
	uint32_t c_counter;
	uint32_t ch_counter;
	uint32_t b_counter;
	uint32_t f_counter;
}pll_type;

extern pll_type  pll_set[200] ;
//--- PLL output Frequency = (((100MHz / PLL_FACTOR_N) * PLL_FACTOR_M) / PLL_FACTOR_C);
extern const uint16_t gPLL_FACTOR_Table[401];

void SetPLL(uint16_t feq);



#endif /* __PLL_FREQ_DEF_H */
