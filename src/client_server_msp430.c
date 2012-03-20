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

#include <msp430.h>
#include <legacymsp430.h>
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
    WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}

void client_server_serialirq_init(void)
{
    serial_rb_init(&srx, &(srx_buf[0]), YWASP_SERIAL_RX_BUF);
    serial_rb_init(&stx, &(stx_buf[0]), YWASP_SERIAL_TX_BUF);

    IE2 |= UCA0RXIE; 
	__bis_SR_register(GIE);
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
		IE2 |= UCA0TXIE;
	}
}

interrupt(USCIAB0RX_VECTOR) USCI0RX_ISR(void)
{
	if (!serial_rb_full(&srx)) {
        serial_rb_write(&srx, UCA0RXBUF);
	}
}

interrupt(USCIAB0TX_VECTOR) USCI0TX_ISR(void)
{
	if(!serial_rb_empty(&stx)) {
    	serial_send(serial_rb_read(&stx));
    }
    else {
    	/* Disable the TX interrupt, it's no longer needed. */
		IE2 &= ~UCA0TXIE; 
    }
}

