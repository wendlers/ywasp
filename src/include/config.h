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

#ifndef _CONFIG_H_
#define _CONFIG_H_

/**
 * Initialize the hardware (GPIOs for jumpers) to be used for
 * configuration.
 */
void config_init(void);

/**
 * Check if the device is configured in server mode.
 *
 * @return	1 if in server mode, 0 for client mode
 */
int config_is_server(void);

/**
 * Get id (0..3) of the predefined address to use for this device
 * for TX and on RX pipe 0 of the nRF24l01.
 *
 * @return	id of address to use (0..3)
 */
int config_get_address_id(void);

#endif
