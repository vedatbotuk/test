idf_component_register(
    SRCS "signal_handler.c"
    INCLUDE_DIRS "include"
    PRIV_REQUIRES esp_timer espressif__esp-zigbee-lib driver light_sleep deep_sleep nvs_flash battery esp_adc waterleak macros temperature_humidity
    )
