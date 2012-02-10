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

#ifndef _CLIENT_SERVER_H_
#define _CLIENT_SERVER_H_

#include <libemb/serial/serial_rb.h>

extern serial_rb srx;

extern serial_rb stx;

/**
 * Board initslizatin for both, client and server mode.
 */
void client_server_board_init(void);

/**
 * IRQ initialization for UART. Used in client and server mode.
 */
void client_server_serialirq_init(void);

/**
 * Transmit given data via the TX ringbuffer to the UART.
 *
 * @param[in]	*data	the data to transmit
 * @param[in]	 size	number of bytes to transmit from data
 */
void client_server_tx_stx(unsigned char *data, int size);

#endif
