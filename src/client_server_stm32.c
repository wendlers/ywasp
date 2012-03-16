/*
 * This file is part of the YWasp project.
 *
 * Copyright (C) 2011 Stefan Wendler <sw@kaltpost.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/f1/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/nvic.h>

#include <libemb/serial/serial.h>

#include "ywasp.h"
#include "client_server.h"

/**
 * Memory used for receiving ringbuffer
 */
SERIAL_RB_Q srx_buf[YWASP_SERIAL_RX_BUF];

/**
 * Ringbuffer for receiving from UART
 */
serial_rb srx;

/**
 * Memory used for transmision ringbuffer
 */
SERIAL_RB_Q stx_buf[YWASP_SERIAL_TX_BUF];

/**
 * Ringbuffer for sending to UART
 */
serial_rb stx;

nrf_payload ptx;
nrf_payload prx;

void client_server_board_init(void)
{
#ifdef STM32_100
     rcc_clock_setup_in_hse_8mhz_out_24mhz();
#else
     rcc_clock_setup_in_hse_8mhz_out_72mhz();
#endif
}

void client_server_serialirq_init(void)
{
     serial_rb_init(&srx, &(srx_buf[0]), YWASP_SERIAL_RX_BUF);
     serial_rb_init(&stx, &(stx_buf[0]), YWASP_SERIAL_TX_BUF);

     /* Enable the USART1 interrupt. */
     nvic_enable_irq(NVIC_USART1_IRQ);

     /* Enable USART1 Receive interrupt. */
     USART_CR1(USART1) |= USART_CR1_RXNEIE;
}

void client_server_tx_stx(unsigned char *data, int size)
{
	int i;

   	for(i = 0; i < size; i++) {
   		if(serial_rb_full(&stx)) {
        	break;
        }
        serial_rb_write(&stx, data[i]);
    }

	if(i > 0) {
    	USART_CR1(USART1) |= USART_CR1_TXEIE;
	}
}

void usart1_isr(void)
{
     unsigned char c;

     // Check if we were called because of RXNE
     if (((USART_CR1(USART1) & USART_CR1_RXNEIE) != 0) &&
               ((USART_SR(USART1) & USART_SR_RXNE) != 0) &&
               (!serial_rb_full(&srx))) {
          c = serial_recv();
          serial_rb_write(&srx, c);
     }
     // Check if we were called because of TXE
     else if (((USART_CR1(USART1) & USART_CR1_TXEIE) != 0) &&
               ((USART_SR(USART1) & USART_SR_TXE) != 0)) {

          if(!serial_rb_empty(&stx)) {
               serial_send(serial_rb_read(&stx));
          } else {
               // Disable the TXE interrupt, it's no longer needed
               USART_CR1(USART1) &= ~USART_CR1_TXEIE;
          }
     } else {
          c = serial_recv();
     }
}
