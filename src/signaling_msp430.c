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

#include "signaling.h"

/**
 * GPIOs used for the defined signal IDs (see SIG_x).
 */
unsigned int signals[] = {
     /**
      * SIG_CON
      */
     BIT3,

     /**
      * SIG_TX
      */
     BIT4,

     /**
      * SIG_RX
      */
     BIT4,

     /**
      * SIG_CLI
      */
     BIT5,

     /**
      * SIG_SRV
      */
     BIT5,
};

void signaling_init(void)
{
	int i;

	for(i = 0; i < 5; i++) {
		P2DIR  |= signals[i];
		P2OUT  |= signals[i];
	}
}

void signaling_set(unsigned char sig, unsigned char state)
{
     if(state) {
		P2OUT |= signals[sig];
     } else {
		P2OUT &= ~signals[sig];
     }
}
