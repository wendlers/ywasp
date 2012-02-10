BINARY	 = firmware
OBJS	+= main.o signaling_stm32.o config_jmp_stm32.o client_server_stm32.o delay_stm32.o
OBJS	+= client.o server.o

ifeq ($(TARCH),STM32_100)
LDSCRIPT = firmware_stm32_100.ld
CFLAGS   = -DSTM32_100
else
LDSCRIPT = firmware_stm32_103.ld
CFLAGS   = -DSTM32_103
endif

CFLAGS  += -DNRF_REG_DEF_META

include ../common.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC)
	$(DOXYGEN) $(DOXYGENFLAGS)

