PROJECT_NAME := zigbee-with-esp32h2

# Paths
IDF_PATH := $(HOME)/esp/esp-idf
PROJECT_PATH := $(HOME)/esp/$(PROJECT_NAME)
BUILD_PATH := $(PROJECT_PATH)/build

# Compiler and tools
CC := $(HOME)/.espressif/tools/riscv32-esp-elf/esp-13.2.0_20230928/riscv32-esp-elf/bin/riscv32-esp-elf-gcc
CXX := $(HOME)/.espressif/tools/riscv32-esp-elf/esp-13.2.0_20230928/riscv32-esp-elf/bin/riscv32-esp-elf-g++
ESPTOOL := $(HOME)/.espressif/python_env/idf5.2_py3.8_env/bin/python -m esptool

# Flash settings
FLASH_BAUD := 460800
FLASH_MODE := dio
FLASH_SIZE := 2MB
FLASH_FREQ := 48m

# Flash addresses
BOOTLOADER_OFFSET := 0x0
PARTITION_TABLE_OFFSET := 0x8000
OTA_DATA_OFFSET := 0xf000
APP_OFFSET := 0x20000

COMPONENTS_INCLUDE := $(shell find $(PROJECT_PATH)/components -type d -exec echo -I{} \;)
LIBRARY_PATHS := $(shell find $(IDF_PATH)/components -type d -exec echo -L{} \;)
MANAGED_LIB_PATHS := $(shell find $(PROJECT_PATH)/managed_components -type d -exec echo -L{} \;)


# Targets
all: build

build:
	@echo "Building project..."
	@$(CC) -o $(BUILD_PATH)/$(PROJECT_NAME).elf $(PROJECT_PATH)/main/device.c -I$(COMPONENTS_INCLUDE) -L$(MANAGED_LIB_PATHS) -L$(LIBRARY_PATHS) -lesp32

flash: build
	@echo "Flashing project..."
	@$(ESPTOOL) --chip esp32h2 -b $(FLASH_BAUD) --before default_reset --after hard_reset write_flash \
		--flash_mode $(FLASH_MODE) --flash_size $(FLASH_SIZE) --flash_freq $(FLASH_FREQ) \
		$(BOOTLOADER_OFFSET) $(BUILD_PATH)/bootloader/bootloader.bin \
		$(PARTITION_TABLE_OFFSET) $(BUILD_PATH)/partition_table/partition-table.bin \
		$(OTA_DATA_OFFSET) $(BUILD_PATH)/ota_data_initial.bin \
		$(APP_OFFSET) $(BUILD_PATH)/device_40000_v16843022dev.bin

flash_manual: build
	@echo "Flashing project manually..."
	@$(ESPTOOL) --chip esp32h2 -b $(FLASH_BAUD) --before default_reset --after hard_reset write_flash \
		--flash_mode $(FLASH_MODE) --flash_size $(FLASH_SIZE) --flash_freq $(FLASH_FREQ) \
		$(BOOTLOADER_OFFSET) $(BUILD_PATH)/bootloader/bootloader.bin \
		$(PARTITION_TABLE_OFFSET) $(BUILD_PATH)/partition_table/partition-table.bin \
		$(OTA_DATA_OFFSET) $(BUILD_PATH)/ota_data_initial.bin \
		$(APP_OFFSET) $(BUILD_PATH)/device_40000_v16843022dev.bin

clean:
	@echo "Cleaning project..."
	@idf.py fullclean

.PHONY: all build flash flash_manual clean
