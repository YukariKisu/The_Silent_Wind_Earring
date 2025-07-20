TARGET := nrf52832_xxaa
OBJ_DIR := _build/$(TARGET)
SRC_DIR := src

OBJECTS := \
  $(OBJ_DIR)/main.o \
  $(OBJ_DIR)/syscalls.o \
  $(OBJ_DIR)/gcc_startup_nrf52.o \
  $(OBJ_DIR)/system_nrf52.o 
#  $(OBJ_DIR)/boards.o


vpath %.c src
vpath %.c ../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx/mdk
vpath %.c ../nRF5/nRF5_SDK_17.1.0_ddde560/components/boards
vpath %.c ../shared
vpath %.S ../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx/mdk

  
SRC_FILES := \
  src/main.c \
  src/syscalls.c \
  ../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx/mdk/gcc_startup_nrf52.S \
  ../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx/mdk/system_nrf52.c \
  src/ble_receiver.c \
  src/effect_controller.c \
  ../shared/utils.c \
  ../nRF5/nRF5_SDK_17.1.0_ddde560/components/drivers_nrf/delay/nrf_delay.c


SRC_DIRS := src ../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx/mdk ../nRF5/nRF5_SDK_17.1.0_ddde560/components/boards
SRC_FILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c) )

ASM_FILES := $(wildcard ../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx/mdk/*.S)
ASM_OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(notdir $(ASM_FILES:.S=.o)))

OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o)))
OBJ_FILES += $(addprefix $(OBJ_DIR)/, $(notdir $(ASM_FILES:.S=.o)))



SHELL := cmd.exe
CC := arm-none-eabi-gcc

CFLAGS := -Wall -g3 -O0 -mthumb -mcpu=cortex-m4 \
  -DFLOAT_ABI_HARD -DNRF52 -DNRF52832_XXAA -DBOARD_PCA10040 \
  -DNRF_SD_BLE_API_VERSION=6 \
  -Isrc -Iconfig -I../../shared \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx/hal \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx/mdk \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/components \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/components/boards \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/components/libraries/util \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/components/drivers_nrf/delay \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/components/drivers_nrf/soc \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/components/toolchain/cmsis/include \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/components/softdevice/s132/headers \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/components/softdevice/common \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560/integration/nrfx \
  -I../nRF5/nRF5_SDK_17.1.0_ddde560\components\libraries\delay 



LDFLAGS = -T blinky_gcc_nrf52.ld -Wl,-Map=_build/nrf52832_xxaa/nrf52832_xxaa.map
LD := $(CC)
OBJCOPY := arm-none-eabi-objcopy
ASMFLAGS := $(CFLAGS)

.PHONY: flash
flash:
	nrfjprog -f nrf52 --program $(OBJ_DIR)/$(TARGET).hex --chiperase --verify
	nrfjprog -f nrf52 --reset


all: $(OBJ_DIR)/$(TARGET).hex

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/%.o: ../nRF5/nRF5_SDK_17.1.0_ddde560/modules/nrfx/mdk/%.S | $(OBJ_DIR)
	@echo Assembling $<
	$(CC) $(ASMFLAGS) -c $< -o $@


$(OBJ_DIR)/%.o: %.S | $(OBJ_DIR)
	@echo Assembling $<
	$(CC) $(ASMFLAGS) -c $< -o $@

$(OBJ_DIR)/$(TARGET).out: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/$(TARGET).hex: $(OBJ_DIR)/$(TARGET).out
	$(OBJCOPY) -O ihex $< $@

$(OBJ_DIR):
	if not exist _build mkdir _build
	if not exist _build\nrf52832_xxaa mkdir _build\nrf52832_xxaa

clean:
	@if exist $(subst /,\,$(OBJ_DIR)) rd /s /q $(subst /,\,$(OBJ_DIR))