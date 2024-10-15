idf_component_register(
    SRCS "light_on_off.c"
    INCLUDE_DIRS "include"
    PRIV_REQUIRES led_strip driver
    )
