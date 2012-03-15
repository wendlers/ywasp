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

#ifndef _YWASP_H_
#define _YWASP_H_

/**
 * Baudrate to use on UART
 */
#define YWASP_SERIAL_BR         9600

#ifdef MSP430

/**
 * Size of RX buffer for UART
 */
#define YWASP_SERIAL_RX_BUF    	64	

#else

/**
 * Size of RX buffer for UART
 */
#define YWASP_SERIAL_RX_BUF    	128	

/**
 * Size of TX buffer for UART
 */
#define YWASP_SERIAL_TX_BUF    	128	

#endif

/**
 * How to identify the NOP payload
 */
#define YWASP_NRF_PL_NOP        0

/**
 * Payload maximum size
 */
#define YWASP_NRF_PL_SIZE       8

/**
 * Predefined address 1 wich could be select through configuration jumpers
 */
#define YWASP_NRF_ADDR0         {1, 1, 1, 1, 1}

/**
 * Predefined address 2 wich could be select through configuration jumpers
 */
#define YWASP_NRF_ADDR1         {1, 1, 1, 1, 2}

/**
 * Predefined address 3 wich could be select through configuration jumpers
 */
#define YWASP_NRF_ADDR2         {1, 1, 1, 1, 3}

/**
 * Predefined address 4 wich could be select through configuration jumpers
 */
#define YWASP_NRF_ADDR3         {1, 1, 1, 1, 4}

/**
 * RF channel to use with the nRF23l01. Effective RF channel will be 2400 + YWASP_RF_CHANNEL
 */
#define YWASP_RF_CHANNEL        40

/**
 * Number of retrys before geving up sending a package
 */
#define YWASP_TX_RETRY          10

/**
 * Retry delay in us
 */
#define YWASP_TX_RETRY_DELAY    NRF_RT_DELAY_750

/**
 * Wait a certain time before next package is sent out. Only relevent
 * for the server part. Normally you should not need this if both, the
 * client and the server device are fast enough to handle the traffic.
 * The value given here is the number of "NOPs" / 2 to execute while waiting.
 */
#define YWASP_TX_THROTTLE		2000

#endif
