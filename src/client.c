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

#include <libemb/serial/serial_rb.h>
#include <libemb/nrf24l01/nrf24l01.h>

#include "ywasp.h"
#include "delay.h"
#include "client_server.h"
#include "client.h"
#include "signaling.h"

void client_init(int addr_id)
{
     nrf_reg_buf addr0 = {
          .data = YWASP_NRF_ADDR0,
     };

     nrf_reg_buf addr1 = {
          .data = YWASP_NRF_ADDR1,
     };

     nrf_reg_buf addr2 = {
          .data = YWASP_NRF_ADDR2,
     };

     nrf_reg_buf addr3 = {
          .data = YWASP_NRF_ADDR3,
     };

     nrf_reg_buf *addr = &addr0;

     switch(addr_id) {
     case 1:
          addr = &addr1;
          break;
     case 2:
          addr = &addr2;
          break;
     case 3:
          addr = &addr3;
          break;
     }

     nrf_preset_esbpl(NRF_MODE_PRX, YWASP_RF_CHANNEL, YWASP_NRF_PL_SIZE + 1, YWASP_TX_RETRY, YWASP_TX_RETRY_DELAY, addr);

     delay(10000);
}

void client_loop(void)
{
     nrf_payload   ptx;
     nrf_payload   prx;

     unsigned char cnt = 0;

     int s;

     prx.size 	= YWASP_NRF_PL_SIZE + 1;
     ptx.size 	= YWASP_NRF_PL_SIZE + 1;

     while (1) {

          // Signal indication has to be delayd since otherwise it would not be visble ...
          if(++cnt == 0xff) {
               signaling_set(SIG_TX, SIG_STATE_OFF);
               signaling_set(SIG_RX, SIG_STATE_OFF);
          }

          ptx.data[0] = YWASP_NRF_PL_NOP;

          while(!serial_rb_empty(&srx) && ptx.data[0] < YWASP_NRF_PL_SIZE) {
               ptx.data[ptx.data[0] + 1] = serial_rb_read(&srx);
               ptx.data[0]++;
          }

          if(ptx.data[0] > 0) {
               signaling_set(SIG_TX, SIG_STATE_ON);
          }

          nrf_write_ack_pl(&ptx, 0);

          s = nrf_receive_blocking(&prx);

          if(s != 0 && prx.data[0] != YWASP_NRF_PL_NOP) {
               signaling_set(SIG_RX, SIG_STATE_ON);
               client_server_tx_stx(&(prx.data[1]), prx.data[0]);
          }
     }
}

