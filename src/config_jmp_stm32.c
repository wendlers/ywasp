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
#include <libopencm3/stm32/f1/gpio.h>

#include "config.h"

/**
 * RCC to enable for port where config-jumpers are connected on STM32
 */
#define CFG_PORT_EN_CLK     RCC_APB2ENR_IOPCEN

/**
 * Port where config jumpers are connected to on STM32
 */
#define CFG_PORT            GPIOC

/**
 * GPIO for jumer to select client/server mode
 */
#define CFG_JMP_CLISRV      GPIO0

/**
 * GPIO for jumer to select address ID bit 1
 */
#define CFG_JMP_ADDR1       GPIO1

/**
 * GPIO for jumer to select address ID bit 2
 */
#define CFG_JMP_ADDR2       GPIO2

void config_init(void)
{
     rcc_peripheral_enable_clock(&RCC_APB2ENR, CFG_PORT_EN_CLK);

     gpio_set_mode(CFG_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, CFG_JMP_CLISRV);
     gpio_set(CFG_PORT, CFG_JMP_CLISRV);

     gpio_set_mode(CFG_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, CFG_JMP_ADDR1);
     gpio_set(CFG_PORT, CFG_JMP_ADDR1);

     gpio_set_mode(CFG_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, CFG_JMP_ADDR2);
     gpio_set(CFG_PORT, CFG_JMP_ADDR2);
}

int config_is_server(void)
{
     return ((GPIO_IDR(GPIOC) & CFG_JMP_CLISRV) == 0);
}

int config_get_address_id(void)
{
     int adr = 0;

     if((GPIO_IDR(GPIOC) & CFG_JMP_ADDR1) == 0) {
          adr = 1;
     }
     if((GPIO_IDR(GPIOC) & CFG_JMP_ADDR2) == 0) {
          adr |= 2;
     }

     return adr;
}
