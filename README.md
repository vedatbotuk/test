# ESP32-H2 Project

This project involves the development of an IoT system using the ESP32-H2 microcontroller. Below you'll find instructions for setting up the project, hardware overview, and build process using the ESP-IDF toolchain. Additionally, Zigpy is integrated for Zigbee protocol support.

## Hardware Overview
The system is built around the **ESP32-H2**, which supports low-power applications and Zigbee connectivity. The primary components of the hardware setup include:

- **Power Supply**: 
  - Powered by a 3.3V regulated power source suitable for the ESP32-H2.
  
- **Sensor Integration**: 
  - The project may integrate various sensors for data collection (e.g., temperature, humidity, or motion detection).
  
- **Communication**: 
  - **Zigbee** for low-power, wireless communication over the Zigbee protocol stack.

## Zigpy Integration
Zigpy is a Zigbee protocol stack, enabling communication between Zigbee devices. It is utilized for wireless networking within the system.

## Development Environment Setup

### ESP-IDF Installation
To set up the environment for building the project, follow these steps:

1. Install the necessary dependencies:
  ```bash
  sudo apt-get install -y git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
  ```
1. Clone the ESP-IDF repository:
  ```bash
  mkdir -p ~/esp
  cd ~/esp
  git clone -b v5.4-dev --recursive https://github.com/espressif/esp-idf.git
  ```
1. Install the ESP-IDF toolchain:
  ```bash
  cd ~/esp/esp-idf
  ./install.sh esp32h2
  ```
1. Set up the environment variables:
  ```bash
  . $HOME/esp/esp-idf/export.sh
  ```

### Zigpy Installation
Zigpy is required for Zigbee communication. To install it:
```bash
pip3 install zigpy
```

## Build and Flash Instructions
### Build Process
To build the project for the ESP32-H2, follow these steps:
1. Set the target for ESP32-H2:
  ```bash
  idf.py set-target esp32h2
  ```
1. Build the project:
  ```bash
  idf.py build
  ```

### Flashing the Firmware
After building the project, flash the firmware to the ESP32-H2 using:
```bash
idf.py flash
```
### Monitor Serial Output
For debugging purposes, you can monitor the serial output from your ESP32-H2:
```bash
idf.py monitor
```

## Automatic Build using GitHub Actions
This project is configured to use GitHub Actions for continuous integration. The build will automatically trigger on each push or pull request to the main branch. Below is a summary of the key steps in the build process:

1. Set up ESP-IDF: Installs the ESP-IDF toolchain and dependencies on the GitHub runner.
1. Install Zigpy: Installs the Zigpy library for Zigbee communication.
1. Build the Project: Builds the project using idf.py.

The configuration is specified in the ```.github/workflows/c-cpp.yaml``` file.

## Project Structure
- ***src/*** : Contains the source code for the project.
- ***include/*** : Contains header files and configuration files.
- ***.github/workflows/*** : Contains the GitHub Actions workflow for automated builds.
