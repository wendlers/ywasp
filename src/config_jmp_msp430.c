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
#include <libemb/conio/conio.h>
#include "config.h"

/**
 * GPIO for jumer to select client/server mode
 */
#define CFG_JMP_CLISRV     	BIT0 

/**
 * GPIO for jumer to select address ID bit 1
 */
#define CFG_JMP_ADDR1     	BIT1 

/**
 * GPIO for jumer to select address ID bit 2
 */
#define CFG_JMP_ADDR2     	BIT2 

void config_init(void)
{
	P2DIR &= ~CFG_JMP_CLISRV;
	P2DIR &= ~CFG_JMP_ADDR1;
	P2DIR &= ~CFG_JMP_ADDR2;
	P2OUT  = 0;
}

int config_is_server(void)
{
  	return ((P2IN & CFG_JMP_CLISRV) == 0);
}

int config_get_address_id(void)
{
     int adr = 0;

     if((P2IN & CFG_JMP_ADDR1) == 0) {
          adr = 1;
     }
     if((P2IN & CFG_JMP_ADDR2) == 0) {
          adr |= 2;
     }

     return adr;
}
