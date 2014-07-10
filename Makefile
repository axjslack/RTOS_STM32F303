# put your *.c source files here, make should handle the rest!
#SRCS = main.c errno.c stm32f3_discovery.c system_stm32f30x.c

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)
PROJ_NAME=main

# Location of the Libraries folder from the STM32F0xx Standard Peripheral Library
STD_PERIPH_LIB=Libraries

# Location of the linker scripts
LDSCRIPT_INC=Device/ldscripts

# location of OpenOCD Board .cfg files (only used with 'make program')
#OPENOCD_BOARD_DIR=/home/matt/bin/openocd/share/openocd/scripts/board

# Configuration (cfg) file containing programming directives for OpenOCD
#OPENOCD_PROC_FILE=extra/stm32f3-openocd.cfg

# that's it, no need to change anything below this line!

#Alex ADD Begin

FREERTOS=freertos

SRCS = \
src/stm32f3_discovery.c \
src/system_stm32f30x.c \
freertos/tasks.c \
freertos/event_groups.c \
freertos/queue.c \
freertos/croutine.c \
freertos/portable/MemMang/heap_1.c \
freertos/portable/GCC/ARM_CM4F/port.c \
freertos/list.c \
freertos/timers.c \
src/mymain.c


#src/osMain.c \


#Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.c

#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_exti.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_crc.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_spi.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_dma.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_pwr.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_usart.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_dbgmcu.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_rcc.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_can.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_wwdg.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_tim.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_misc.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_dac.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_iwdg.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_flash.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_i2c.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_opamp.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_comp.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_rtc.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_syscfg.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_gpio.c
#Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_adc.c
#Libraries/STM32_USB-FS-Device_Driver/src/usb_init.c
#Libraries/STM32_USB-FS-Device_Driver/src/usb_regs.c
#Libraries/STM32_USB-FS-Device_Driver/src/usb_mem.c
#Libraries/STM32_USB-FS-Device_Driver/src/usb_core.c
#Libraries/STM32_USB-FS-Device_Driver/src/usb_sil.c
#Libraries/STM32_USB-FS-Device_Driver/src/usb_int.c

#freertos/portable/MemMang/heap_4.c
#freertos/portable/MemMang/heap_2.c
#freertos/portable/MemMang/heap_3.c

#Alex ADD End


###################################################

CC=arm-none-eabi-gcc
GDB=arm-none-eabi-gdb
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size

CFLAGS  = -Wall -g -std=c99 -Os  
CFLAGS += -mlittle-endian -mcpu=cortex-m4  -march=armv7e-m -mthumb
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -ffunction-sections -fdata-sections

#ALEX ADD
CFLAGS += -mthumb-interwork

LDFLAGS += -Wl,--gc-sections -Wl,-Map=$(PROJ_NAME).map

###################################################

vpath %.a $(STD_PERIPH_LIB)

ROOT=$(shell pwd)

CFLAGS += -I inc 
CFLAGS += -I $(STD_PERIPH_LIB) 
CFLAGS += -I $(STD_PERIPH_LIB)/CMSIS/Device/ST/STM32F30x/Include
CFLAGS += -I $(STD_PERIPH_LIB)/CMSIS/Include 
CFLAGS += -I $(STD_PERIPH_LIB)/STM32F30x_StdPeriph_Driver/inc
CFLAGS += -I $(STD_PERIPH_LIB)/STM32_USB-FS-Device_Driver/inc
CFLAGS += -include $(STD_PERIPH_LIB)/stm32f30x_conf.h

#ALEX ADD
CFLAGS += -I $(FREERTOS)/include
CFLAGS += -I $(FREERTOS)/portable/GCC/ARM_CM4F


STARTUP = Device/startup_stm32f30x.s # add startup file to build

# need if you want to build with -DUSE_CMSIS 
#SRCS += stm32f0_discovery.c
#SRCS += stm32f0_discovery.c stm32f0xx_it.c


#ALEX Mod
#OBJS = $(addprefix objs/,$(SRCS:.c=.o))
#DEPS = $(addprefix deps/,$(SRCS:.c=.d))

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)


###################################################

.PHONY: all lib proj program debug clean reallyclean

all: lib proj

-include $(DEPS)

lib:
	$(MAKE) -C $(STD_PERIPH_LIB)

proj: 	$(PROJ_NAME).elf

dirs:
	mkdir -p deps objs
	touch dirs

objs/%.o : src/%.c dirs
	$(CC) $(CFLAGS) -c -o $@ $< -MMD -MF deps/$(*F).d

$(PROJ_NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(STARTUP) -L$(STD_PERIPH_LIB) -lstm32f3 -L$(LDSCRIPT_INC) -Tstm32f3.ld
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(OBJDUMP) -St $(PROJ_NAME).elf >$(PROJ_NAME).lst
	$(SIZE) $(PROJ_NAME).elf

program: all
	openocd -f $(OPENOCD_BOARD_DIR)/stm32f3discovery.cfg -f $(OPENOCD_PROC_FILE) -c "stm_flash `pwd`/$(PROJ_NAME).bin" -c shutdown

debug: program
	$(GDB) -x extra/gdb_cmds $(PROJ_NAME).elf

clean:
	find ./ -name '*~' | xargs rm -f	
	rm -f objs/*.o
	rm -f deps/*.d
	rm -f dirs
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).map
	rm -f $(PROJ_NAME).lst

reallyclean: clean
	$(MAKE) -C $(STD_PERIPH_LIB) clean
