/*!
    \file    msc_mem.c
    \brief   msc memories operation functions

    \version 2021-03-23, V2.0.0, demo for GD32F30x
*/

/*
    Copyright (c) 2021, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "usbd_msc_mem.h"
#include "usbd_conf.h"
#include "bsp_driver_sd.h"
#include "log.h"
#include "cdc_acm_core.h"
#include "ff.h"
/* USB Mass storage Standard Inquiry Data */
const uint8_t mem_inquiry_data[] =
{
    /* LUN 0 */
    0x00,
    0x80,
    0x00,
    0x01,
    (USBD_STD_INQUIRY_LENGTH - 5U),
    0x00,
    0x00,
    0x00,
    'G', 'D', '3', '2', ' ', ' ', ' ', ' ', /* Manufacturer: 8 bytes */
    'I', 'N', 'T', 'E', 'R', 'N', 'A', 'L', /* Product: 16 Bytes */
    ' ', 'F', 'L', 'A', 'S', 'H', ' ', ' ',
    '1', '.', '0','0',                      /* Version: 4 Bytes */
};

/* local function prototypes ('static') */
static int8_t mem_init      (uint8_t lun);
static int8_t mem_ready     (uint8_t lun);
static int8_t mem_protected (uint8_t lun);
static int8_t mem_maxlun    (void);
static int8_t mem_read      (uint8_t lun, uint8_t *buf, uint32_t blkaddr, uint16_t blklen);
static int8_t mem_write     (uint8_t lun, uint8_t *buf, uint32_t blkaddr, uint16_t blklen);

usbd_mem_cb usbd_mem_opera =
{
    .mem_init         = mem_init,
    .mem_ready        = mem_ready,
    .mem_protected    = mem_protected,
    .mem_read         = mem_read,
    .mem_write        = mem_write,
    .mem_maxlun       = mem_maxlun,

    .mem_inquiry_data = {(uint8_t *)mem_inquiry_data},
    .mem_block_size   = {BLOCK_SIZE},
    .mem_block_len    = {BLOCK_NUM},
};

usbd_mem_cb *usbd_mem_fops = &usbd_mem_opera;

/*!
    \brief      initialize the storage medium
    \param[in]  lun: logical unit number
    \param[out] none
    \retval     status
*/
static int8_t mem_init (uint8_t lun)
{
//    flash_init();
    sd_io_init();
    return 0;
}

/*!
    \brief      check whether the medium is ready
    \param[in]  lun: logical unit number
    \param[out] none
    \retval     status
*/
static int8_t mem_ready (uint8_t lun)
{
    return 0;
}

/*!
    \brief      check whether the medium is write-protected
    \param[in]  lun: logical unit number
    \param[out] none
    \retval     status
*/
static int8_t mem_protected (uint8_t Lun)
{
    return 0;
}

/*!
    \brief      read data from the medium
    \param[in]  lun: logical unit number
    \param[in]  buf: pointer to the buffer to save data
    \param[in]  blkaddr: address of 1st block to be read
    \param[in]  blklen: number of blocks to be read
    \param[out] none
    \retval     Status
*/
#include "usbd_core.h"

static int8_t mem_read (uint8_t lun, uint8_t *buf, uint32_t blkaddr, uint16_t blklen)
{
//    flash_read_multi_blocks(buf, blkaddr, BLOCK_SIZE, blklen);
    sd_multiblocks_read((uint32_t*)buf, blkaddr, BLOCK_SIZE, blklen);
    return 0;
}

/*!
    \brief      write data to the medium
    \param[in]  lun: logical unit number
    \param[in]  buf: pointer to the buffer to write
    \param[in]  blkaddr: address of 1st block to be read
    \param[in]  blkaddr: address of blocks to be written
    \param[out] none
    \retval     Status
*/
static int8_t mem_write (uint8_t lun, uint8_t *buf, uint32_t blkaddr, uint16_t blklen)
{
//    flash_write_multi_blocks (buf, blkaddr, BLOCK_SIZE, blklen);
    sd_multiblocks_write((uint32_t *)buf,blkaddr, BLOCK_SIZE,blklen);
    return 0;
}

/*!
    \brief      get number of supported logical unit
    \param[in]  none
    \param[out] none
    \retval     Number of logical unit
*/
static int8_t mem_maxlun (void)
{
    return (MEM_LUN_NUM - 1);
}

#include "usbd_hw.h"
#include "usbd_msc_core.h"
#include "fatfs.h"
#include "file_opration.h"
#include "cdc_acm_core.h"
usb_dev usb_msc;
usb_dev usbd_cdc;

void start_usb(void)
{
    usb_rcu_config();
    /* GPIO configuration */
    usb_gpio_config();

    /* USB device configuration */
//    usbd_init(&usb_msc, &msc_desc, &msc_class);
		usbd_init(&usbd_cdc, &cdc_desc1, &cdc_class1);
    /* NVIC configuration */
    usb_nvic_config();

    /* enabled USB pull-up */
//    usbd_connect(&usb_msc);
	  usbd_connect(&usbd_cdc);
    log_info("CDC MODE!");
}


void dis_usb (void)
{
	FIL fs;
	FRESULT  res;
	Fatfs_init(SDCard);
	usbd_disconnect (&usb_msc);
	res=f_open(&fs,"0:/UPDATA/app.bin",FA_OPEN_EXISTING|FA_READ);
	if(res==FR_OK)
	{
		updata_falg();
    NVIC_SystemReset();
	}
	log_info("%d",res);
	
}











