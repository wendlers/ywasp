BINARY	 = firmware
OBJS	+= main.o client.o server.o delay.o

ifeq ($(TARCH),MSP430)
OBJS	+= signaling_msp430.o config_jmp_msp430.o client_server_msp430.o 
else
OBJS	+= signaling_stm32.o config_jmp_stm32.o client_server_stm32.o 
endif

ifeq ($(TARCH),STM32_100)
LDSCRIPT = firmware_stm32_100.ld
CFLAGS   = -DSTM32_100
else
LDSCRIPT = firmware_stm32_103.ld
CFLAGS   = -DSTM32_103
endif

include ../common.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC)
	$(DOXYGEN) $(DOXYGENFLAGS)

