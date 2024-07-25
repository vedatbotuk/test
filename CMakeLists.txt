# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)
set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/components
    )

## Set dev or prod
set(DEV_PROD "dev")

#### Define Macros
# add_definitions(-DCONFIG_ZB_ZED=y)
# idf_build_set_property(COMPILE_OPTIONS "-DCDCONFIG_ZB_ZED=y" APPEND)
## First 7 bits are for additional future features
## END_DEVICE(0=ROUTER_DEVICE) | OTA_UPGRADE | Humidity | Temperature | BATTERY | LIGHT_SLEEP | DEEP_SLEEP | SENSOR_WATERLEAK | AUTOMATIC_IRRIGATION
set(SENSOR_MAP_DEF "1111110000000000")
add_definitions(-DSENSOR_MAP=0b${SENSOR_MAP_DEF})
add_definitions(-DMODEL_ID_MAP=${SENSOR_MAP_DEF})
add_definitions(-DDEVICE_ENDPOINT=10)

## Channel and TX-Power
add_definitions(-DTX_POWER=0)

## KEEP ALIVE
add_definitions(-DED_KEEP_ALIVE=4000)

## OTA MACROS
add_definitions(-DESP_OTA_CLIENT_ENDPOINT=10)
# Define HEX 0x0101 or DEC 257
set(HW_VERSION "257")
set(VERSION "16843016")
add_definitions(-DOTA_UPGRADE_HW_VERSION=${HW_VERSION})
add_definitions(-DOTA_UPGRADE_DOWNLOADED_FILE_VERSION=${VERSION})
add_definitions(-DOTA_UPGRADE_RUNNING_FILE_VERSION=${VERSION})
add_definitions(-DOTA_UPGRADE_IMAGE_TYPE=0x1011)
add_definitions(-DOTA_UPGRADE_MANUFACTURER=0x1001)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(device_${SENSOR_MAP_DEF}_v${VERSION}${DEV_PROD})

# Funktion zur Konvertierung einer Binärzahl in eine Dezimalzahl
function(binary_to_decimal binary_number result)
    set(decimal_value 0)
    set(base 1)

    # Umgekehrte Reihenfolge der Binärzahl verarbeiten
    string(REVERSE "${binary_number}" reversed_binary)

    foreach(digit IN LISTS reversed_binary)
        if(digit EQUAL "1")
            math(EXPR decimal_value "${decimal_value} + ${base}")
        endif()
        math(EXPR base "${base} * 2")
    endforeach()

    # Ergebnis zurückgeben
    set(${result} "${decimal_value}" PARENT_SCOPE)
endfunction()

# Variable für das Ergebnis der Konvertierung
binary_to_decimal(${binary_number} imageType)

## Create OTA-Update File
set(MY_DIR ${CMAKE_BINARY_DIR}/ota)
file(MAKE_DIRECTORY ${MY_DIR})

set(PYTHON_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/create_ota.py)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E env python3 ${PYTHON_SCRIPT} -m 4097 -i ${imageType} -v ${VERSION} \
                                            build/device_${SENSOR_MAP_DEF}_v${VERSION}${DEV_PROD}.bin \
                                            ota/device_${SENSOR_MAP_DEF}_v${VERSION}${DEV_PROD}.ota
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
# python3 ../../scripts/create_ota.py -m 4097 -i 4113 -v 16843014 build/sensor_device_light_sleep.bin > build/sensor_device.ota