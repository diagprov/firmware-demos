PROJECT_NAME     := blinky_rtc_FreeRTOS_pca10056
TARGETS          := nrf52840dk
OUTPUT_DIRECTORY := build


GNU_INSTALL_ROOT ?= /opt/arm/arm-eabi-latest/bin/
GNU_VERSION ?= 10.3.0
GNU_PREFIX ?= arm-none-eabi

PWD=$(shell pwd)
PROJ_DIR ?=$(PWD)

$(OUTPUT_DIRECTORY)/nrf52840dk.out: \
  LINKER_SCRIPT  := nrf52840.ld

# Source files common to all targets
SRC_FILES += \
  sdk/modules/nrfx/mdk/gcc_startup_nrf52840.S \
  sdk/components/libraries/log/src/nrf_log_frontend.c \
  sdk/components/libraries/log/src/nrf_log_str_formatter.c \
  sdk/components/boards/boards.c \
  freertos/source/croutine.c \
  freertos/source/event_groups.c \
  freertos/source/portable/MemMang/heap_1.c \
  freertos/source/list.c \
  freertos/portable/GCC/nrf52/port.c \
  freertos/portable/CMSIS/nrf52/port_cmsis.c \
  freertos/portable/CMSIS/nrf52/port_cmsis_systick.c \
  freertos/source/queue.c \
  freertos/source/stream_buffer.c \
  freertos/source/tasks.c \
  freertos/source/timers.c \
  sdk/components/libraries/button/app_button.c \
  sdk/components/libraries/util/app_error.c \
  sdk/components/libraries/util/app_error_handler_gcc.c \
  sdk/components/libraries/util/app_error_weak.c \
  sdk/components/libraries/timer/app_timer_freertos.c \
  sdk/components/libraries/util/app_util_platform.c \
  sdk/components/libraries/util/nrf_assert.c \
  sdk/components/libraries/atomic/nrf_atomic.c \
  sdk/components/libraries/balloc/nrf_balloc.c \
  sdk/external/fprintf/nrf_fprintf.c \
  sdk/external/fprintf/nrf_fprintf_format.c \
  sdk/components/libraries/memobj/nrf_memobj.c \
  sdk/components/libraries/ringbuf/nrf_ringbuf.c \
  sdk/components/libraries/strerror/nrf_strerror.c \
  sdk/integration/nrfx/legacy/nrf_drv_clock.c \
  sdk/components/drivers_nrf/nrf_soc_nosd/nrf_nvic.c \
  sdk/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c \
  sdk/modules/nrfx/soc/nrfx_atomic.c \
  sdk/modules/nrfx/drivers/src/nrfx_clock.c \
  sdk/modules/nrfx/drivers/src/nrfx_gpiote.c \
  sdk/modules/nrfx/drivers/src/nrfx_rtc.c \
  sdk/components/libraries/bsp/bsp.c \
  $(PROJ_DIR)/main.c \
  sdk/modules/nrfx/mdk/system_nrf52840.c \

# Include folders common to all targets
INC_FOLDERS += \
  $(PROJ_DIR)/config \
  sdk/components \
  sdk/modules/nrfx/mdk \
  $(PROJ_DIR) \
  sdk/components/libraries/timer \
  sdk/components/libraries/strerror \
  sdk/components/toolchain/cmsis/include \
  freertos/source/include \
  freertos/config \
  sdk/components/libraries/util \
  config \
  sdk/components/libraries/balloc \
  sdk/components/libraries/ringbuf \
  sdk/modules/nrfx/hal \
  sdk/components/libraries/bsp \
  sdk/components/libraries/log \
  sdk/components/libraries/button \
  sdk/modules/nrfx \
  sdk/components/libraries/experimental_section_vars \
  sdk/integration/nrfx/legacy \
  freertos/portable/CMSIS/nrf52 \
  sdk/integration/nrfx \
  sdk/components/drivers_nrf/nrf_soc_nosd \
  sdk/components/libraries/atomic \
  sdk/components/boards \
  sdk/components/libraries/memobj \
  freertos/portable/GCC/nrf52 \
  sdk/modules/nrfx/drivers/include \
  sdk/external/fprintf \
  sdk/components/libraries/log/src \

# Libraries common to all targets
LIB_FILES += \

# Optimization flags
OPT = -O3 -g3
# Uncomment the line below to enable link time optimization
#OPT += -flto

CC      := $($(GNU_INSTALL_ROOT)$(GNU_PREFIX)-gcc)
CXX     := $($(GNU_INSTALL_ROOT)$(GNU_PREFIX)-c++)
AS      := $($(GNU_INSTALL_ROOT)$(GNU_PREFIX)-as)
AR      := $($(GNU_INSTALL_ROOT)$(GNU_PREFIX)-ar) -r
LD      := $($(GNU_INSTALL_ROOT)$(GNU_PREFIX)-ld)
NM      := $($(GNU_INSTALL_ROOT)$(GNU_PREFIX)-nm)
OBJDUMP := $($(GNU_INSTALL_ROOT)$(GNU_PREFIX)-objdump)
OBJCOPY := $($(GNU_INSTALL_ROOT)$(GNU_PREFIX)-objcopy)
SIZE    := $($(GNU_INSTALL_ROOT)$(GNU_PREFIX)-size)

# C flags common to all targets
CFLAGS += $(OPT)
CFLAGS += -DBOARD_PCA10056
CFLAGS += -DCONFIG_GPIO_AS_PINRESET
CFLAGS += -DFLOAT_ABI_HARD
CFLAGS += -DFREERTOS
CFLAGS += -DNRF52840_XXAA
CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb -mabi=aapcs
CFLAGS += -Wall -Werror
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# keep every function in a separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin -fshort-enums

# C++ flags common to all targets
CXXFLAGS += $(OPT)
# Assembler flags common to all targets
ASMFLAGS += -g3
ASMFLAGS += -mcpu=cortex-m4
ASMFLAGS += -mthumb -mabi=aapcs
ASMFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
ASMFLAGS += -DBOARD_PCA10056
ASMFLAGS += -DCONFIG_GPIO_AS_PINRESET
ASMFLAGS += -DFLOAT_ABI_HARD
ASMFLAGS += -DFREERTOS
ASMFLAGS += -DNRF52840_XXAA

# Linker flags
LDFLAGS += $(OPT)
LDFLAGS += -mthumb -mabi=aapcs -Lsdk/modules/nrfx/mdk -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m4
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# let linker dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs

nrf52840dk: CFLAGS += -D__HEAP_SIZE=8192
nrf52840dk: CFLAGS += -D__STACK_SIZE=8192
nrf52840dk: ASMFLAGS += -D__HEAP_SIZE=8192
nrf52840dk: ASMFLAGS += -D__STACK_SIZE=8192

# Add standard libraries at the very end of the linker input, after all objects
# that may need symbols provided by these libraries.
LIB_FILES += -lc -lnosys -lm


.PHONY: default help

# Default target - first one defined
default: nrf52840dk

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo		nrf52840dk
	@echo		sdk_config - starting external tool for editing sdk_config.h
	@echo		flash      - flashing binary

include Makefile.common

$(foreach target, $(TARGETS), $(call define_target, $(target)))

.PHONY: flash erase

# Flash the program
flash: default
	@echo Flashing: $(OUTPUT_DIRECTORY)/nrf52840dk.hex
	nrfjprog -f nrf52 --program $(OUTPUT_DIRECTORY)/nrf52840dk.hex --sectorerase
	nrfjprog -f nrf52 --reset

erase:
	nrfjprog -f nrf52 --eraseall

SDK_CONFIG_FILE := config/sdk_config.h


CMSIS_CONFIG_TOOL := sdk/external_tools/cmsisconfig/CMSIS_Configuration_Wizard.jar
sdk_config:
	java -jar $(CMSIS_CONFIG_TOOL) $(SDK_CONFIG_FILE)




# Link object files
%.out:
  $(info $(call PROGRESS,Linking target: $@))
  $(NO_ECHO)$(GENERATE_LD_INPUT_FILE)
  $(NO_ECHO)$(CC) $(LDFLAGS) $(LD_INPUT) -Wl,-Map=$(@:.out=.map) -o $@
  $(NO_ECHO)$(SIZE) $@

# Create binary .bin file from the .out file
%.bin: %.out
  $(info Preparing: $@)
  $(NO_ECHO)$(OBJCOPY) -O binary $< $@

# Create binary .hex file from the .out file
%.hex: %.out
  $(info Preparing: $@)
  $(NO_ECHO)$(OBJCOPY) -O ihex $< $@

# Create object files from C source files
build/%.o: %.c
	$(CC) -std=c99,$(CFLAGS) -I$(INC_PATHS) -c $< -o $@

# Create object files from C++ source files
build/%.o: %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -I$(INC_PATHS) -c $< -o $@

# Create object files from assembly source files
%.S.o %.s.o.o:
	$(CC) $(ASMFLAGS) -c $< -o $@
