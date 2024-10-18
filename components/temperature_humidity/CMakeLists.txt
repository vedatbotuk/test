idf_component_register(
    SRCS "temperature_humidity.c"
    INCLUDE_DIRS "include"
    PRIV_REQUIRES esp_driver_gpio update_cluster espressif__esp-zigbee-lib esp_driver_uart update_cluster dht22 macros
    )
