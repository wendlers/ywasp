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

#include "signaling.h"

/**
 * RCC to enable for signaling on STM32
 */
#define SIG_PORT_EN_CLK     RCC_APB2ENR_IOPBEN

/**
 * Port where signals (LEDs) are connected on STM32
 */
#define SIG_PORT            GPIOB

/**
 * GPIOs used for the defined signal IDs (see SIG_x).
 */
unsigned int signals[] = {
     /**
      * SIG_CON
      */
     GPIO5,

     /**
      * SIG_TX
      */
     GPIO6,

     /**
      * SIG_RX
      */
     GPIO7,

     /**
      * SIG_CLI
      */
     GPIO8,

     /**
      * SIG_SRV
      */
     GPIO9,
};

void signaling_init(void)
{
     int i = 0;

     rcc_peripheral_enable_clock(&RCC_APB2ENR, SIG_PORT_EN_CLK);

     for(i = 0; i < 5; i++) {
          gpio_set_mode(SIG_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, signals[i]);
     }
}

void signaling_set(unsigned char sig, unsigned char state)
{
     if(state) {
          gpio_set(SIG_PORT, signals[sig]);
     } else {
          gpio_clear(SIG_PORT, signals[sig]);
     }
}
