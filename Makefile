######################################
# target
######################################
TARGET = GD32F303VET6
GCC_PATH=gcc-arm-none-eabi-10.3-2021.10/bin

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization for size
OPT = -O1


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources


C_SOURCES += $(addprefix MALLOC/,	\
malloc.c	\
)

C_SOURCES += $(addprefix Module/,	\
power_task.c	\
TouchPoint.c	\
user_config.c	\
app.c			\
lcd_cfg.c		\
ssd_2832.c		\
)

C_SOURCES += $(addprefix User/,	\
systick.c \
gd32f30x_it.c \
main.c 			\
gd32f303e_eval.c	\
)



#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary 
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_STDPERIPH_DRIVER \
-DGD32F30X_HD


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-IFirmware/CMSIS \
-IFirmware/CMSIS/GD/GD32F30x/Include \
-IFirmware/GD32F30x_standard_peripheral/Include \
-IUSER	\
-ICMD	\
-IFatFs/src/	\
-IFatFs/src/drivers	\
-IGPU	\
-ILCD	\
-IMALLOC	\
-Isdio		\
-ISoft_Drive \
-ITEXT		\
-IYMODEM	\
-IModule	\
-IMB/modbus/include	\
-IMB/modbus/ascii	\
-IMB/modbus/rtu    \
-IMB/modbus/tcp    \
-IMB/port    \
-IMB/user_app    \






# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections 

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -std=c99

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

LIBPATH = -L./ \
#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = Firmware/Ld/Link.ld

# libraries
#LIBS = -lc -lm -lnosys 
LIBS += -l$(TARGET)
LIBDIR = $(LIBPATH)
LDFLAGS = $(MCU) -u_printf_float -specs=nosys.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -static




# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@



$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		


#debug:
#	arm-none-eabi-gdb ./build/$(TARGET).elf	
#	target remote 127.0.0.1:3333
#######################################
# program
#######################################
program:
	openocd -f C:/tool-chain/openocd-20230712/OpenOCD-20230712-0.12.0/share/openocd/scripts/interface/jlink.cfg -f C:/tool-chain/openocd-20230712/OpenOCD-20230712-0.12.0/share/openocd/scripts/target/gd32f30x.cfg -c "program build/$(TARGET).elf verify reset exit"




#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***

