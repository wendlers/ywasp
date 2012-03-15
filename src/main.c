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

#include <libemb/serial/serial.h>
#include <libemb/serial/serial_rb.h>
#include <libemb/nrf24l01/nrf24l01.h>

#include "ywasp.h"
#include "signaling.h"
#include "config.h"
#include "client_server.h"
#include "client.h"
#include "server.h"

/**
 * Memory used for receiving ringbuffer
 */
static SERIAL_RB_Q srx_buf[YWASP_SERIAL_RX_BUF];

/**
 * Ringbuffer for receiving from UART
 */
serial_rb srx;

#ifndef MSP430
/**
 * Memory used for transmision ringbuffer
 */
static SERIAL_RB_Q stx_buf[YWASP_SERIAL_TX_BUF];

/**
 * Ringbuffer for sending to UART
 */
serial_rb stx;
#endif

/**
 * Are we running in server mode?
 */
int is_server;

/**
 * Init all the hardware used.
 */
void init()
{
     serial_rb_init(&srx, &(srx_buf[0]), YWASP_SERIAL_RX_BUF);
#ifndef MSP430
     serial_rb_init(&stx, &(stx_buf[0]), YWASP_SERIAL_TX_BUF);
#endif

     client_server_board_init();

     signaling_init();

     config_init();

     serial_init(YWASP_SERIAL_BR);

     client_server_serialirq_init();

     nrf_init();

     if(config_is_server()) {
          is_server = 1;
          server_init(config_get_address_id());
          signaling_set(SIG_SRV, SIG_STATE_ON);
     } else {
          is_server = 0;
          client_init(config_get_address_id());
          signaling_set(SIG_CLI, SIG_STATE_ON);
     }

}

int main(void)
{
     init();

     /**
      * Enter main loop depending on the role configured
      */
     if(is_server) {
          server_loop();
     } else {
          client_loop();
     }

     return 0;
}
