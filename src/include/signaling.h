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

#ifndef __SIGNALING_H_
#define __SIGNALING_H_

/**
 * ID for signal indicating "connected"
 */
#define SIG_CON     	0

/**
 * ID for signal indicating "TX data"
 */
#define SIG_TX      	1

/**
 * ID for signal indicating "RX data"
 */
#define SIG_RX      	2

/**
 * ID for signal indicating "client mode"
 */
#define SIG_CLI     	3

/**
 * ID for signal indicating "server mode"
 */
#define SIG_SRV     	4

/**
 * Signal state "ON"
 */
#define SIG_STATE_ON    1

/**
 * Signal state "OFF"
 */
#define SIG_STATE_OFF   0

/**
 * Initialize the hardware used for signaling.
 */
void signaling_init(void);

/**
 * Set the state for a given signal.
 *
 * @param[in]	sig		signal ID (one of SIG_x)
 * @param[in]	state	signal state (one of SIG_STATE_x)
 */
void signaling_set(unsigned char sig, unsigned char state);

#endif
