/*!
    \file  uart_protocol.c
    \brief UART message protocol implementation
*/

#include "uart_protocol.h"
#include "usartfifo.h"
#include "string.h"

#define MSG_BUF_SIZE    512
static uint8_t msg_rx_buf[MSG_BUF_SIZE];
static uint16_t msg_rx_len = 0;

/*!
    \brief      initialize message FIFO
    \param[in]  none
    \param[out] none
    \retval     none
*/
void msgfifo_init(void)
{
    ringbuffer_init();
    msg_rx_len = 0;
    memset(msg_rx_buf, 0, sizeof(msg_rx_buf));
}

/*!
    \brief      initialize message protocol
    \param[in]  none
    \param[out] none
    \retval     none
*/
void msg_init(void)
{
    msgfifo_init();
}

/*!
    \brief      UART interrupt callback for message protocol
    \param[in]  none
    \param[out] none
    \retval     none
*/
void msg_it_cb(void)
{
    uint8_t ch;
    /* try to read one byte from UART buffer */
    if (uart_buf_get(&ch) == 0) {
        /* store received byte */
        if (msg_rx_len < MSG_BUF_SIZE - 1) {
            msg_rx_buf[msg_rx_len++] = ch;
        }
    }
}

/*!
    \brief      read a message from FIFO
    \param[in]  none
    \param[out] none
    \retval     none
*/
void msg_read(void)
{
    uint8_t ch;
    /* read all available data from UART buffer */
    while (uart_buf_get(&ch) == 0) {
        if (msg_rx_len < MSG_BUF_SIZE - 1) {
            msg_rx_buf[msg_rx_len++] = ch;
        }
    }
}
