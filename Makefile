TARGET=main.hex
EXECUTABLE=main.elf

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump

BIN=$(CP) -O ihex 

DEFS = -DUSE_STDPERIPH_DRIVER -DSTM32F4XX -DHSE_VALUE=8000000
STARTUP = startup_stm32f40xx.s

MCU = cortex-m4
MCFLAGS = -mcpu=$(MCU) -mthumb -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork -g -Wall -save-temps
STM32_INCLUDES = -I./STM32F4_Std/inc/ -I./ -I./OS_Core/

OPTIMIZE       = 

CFLAGS	= $(MCFLAGS)  $(OPTIMIZE)  $(DEFS) -I. -I./ $(STM32_INCLUDES)  -Wl,-T,stm32_flash.ld
AFLAGS	= $(MCFLAGS) 
#-mapcs-float use float regs. small increase in code size

SRC = main.c \
    *.c \
	./OS_Core/*.c \
	system_stm32f4xx.c \
	./STM32F4_Std/src/misc.c \
	./STM32F4_Std/src/stm32f4xx_adc.c \
	./STM32F4_Std/src/stm32f4xx_can.c \
	./STM32F4_Std/src/stm32f4xx_crc.c \
	./STM32F4_Std/src/stm32f4xx_cryp_aes.c \
	./STM32F4_Std/src/stm32f4xx_cryp.c \
	./STM32F4_Std/src/stm32f4xx_cryp_des.c \
	./STM32F4_Std/src/stm32f4xx_cryp_tdes.c \
	./STM32F4_Std/src/stm32f4xx_dac.c \
	./STM32F4_Std/src/stm32f4xx_dbgmcu.c \
	./STM32F4_Std/src/stm32f4xx_dcmi.c \
	./STM32F4_Std/src/stm32f4xx_dma.c \
	./STM32F4_Std/src/stm32f4xx_exti.c \
	./STM32F4_Std/src/stm32f4xx_flash.c \
	./STM32F4_Std/src/stm32f4xx_fsmc.c \
	./STM32F4_Std/src/stm32f4xx_gpio.c \
	./STM32F4_Std/src/stm32f4xx_hash.c \
	./STM32F4_Std/src/stm32f4xx_hash_md5.c \
	./STM32F4_Std/src/stm32f4xx_hash_sha1.c \
	./STM32F4_Std/src/stm32f4xx_i2c.c \
	./STM32F4_Std/src/stm32f4xx_iwdg.c \
	./STM32F4_Std/src/stm32f4xx_pwr.c \
	./STM32F4_Std/src/stm32f4xx_rcc.c \
	./STM32F4_Std/src/stm32f4xx_rng.c \
	./STM32F4_Std/src/stm32f4xx_rtc.c \
	./STM32F4_Std/src/stm32f4xx_sdio.c \
	./STM32F4_Std/src/stm32f4xx_spi.c \
	./STM32F4_Std/src/stm32f4xx_syscfg.c \
	./STM32F4_Std/src/stm32f4xx_tim.c \
	./STM32F4_Std/src/stm32f4xx_usart.c \
	./STM32F4_Std/src/stm32f4xx_wwdg.c 

OBJDIR = .
OBJ = $(SRC:%.c=$(OBJDIR)/%.o) 
OBJ += Startup.o

all: $(TARGET)

$(TARGET): $(EXECUTABLE)
	$(CP) -O ihex $^ $@

$(EXECUTABLE): $(SRC) $(STARTUP)
	$(CC) $(CFLAGS) $^ -lm -lc -lnosys -o $@

clean:
	rm -f Startup.lst  $(TARGET)  $(TARGET).lst $(OBJ) $(AUTOGEN)  $(TARGET).out  $(TARGET).hex  $(TARGET).map \
	 $(TARGET).dmp  $(TARGET).elf
