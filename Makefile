# Path to the ESP-IDF directory
IDF_PATH := $(HOME)/esp/esp-idf

# Project name
PROJECT_NAME := zigbee_with_esp32h2

# Output directory for the build
BUILD_DIR := build

# Default target: build the project
all: build flash monitor

# Build the project
build:
	@. $(IDF_PATH)/export.sh
	idf.py set-target esp32h2
	idf.py build

# Flash the project to the device
flash:
	@. $(IDF_PATH)/export.sh
	idf.py -p $(ESPPORT) flash

# Monitor the serial output
monitor:
	@. $(IDF_PATH)/export.sh
	idf.py -p $(ESPPORT) monitor

# Clean the build directory
clean:
	@. $(IDF_PATH)/export.sh
	idf.py fullclean

# Build and flash in one step
flash_monitor: flash monitor

# Use this to set the serial port (default /dev/ttyUSB0 on Linux)
ESPPORT ?= /dev/ttyUSB0

# Remove the build directory completely
fullclean:
	@rm -rf $(BUILD_DIR) ota managed_components
	@rm sdkconfig sdkconfig.old sdkconfig.defaults

.PHONY: all build flash monitor clean distclean flash_monitor
