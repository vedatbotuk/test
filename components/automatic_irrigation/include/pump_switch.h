/*
 * selforganized_802.15.4_network_with_esp32
 * Copyright (c) 2024 Vedat Botuk.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <esp_err.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* light intensity level */
#define LIGHT_DEFAULT_ON 1
#define LIGHT_DEFAULT_OFF 0

/* LED strip configuration */
#define CONFIG_EXAMPLE_STRIP_LED_GPIO 8

    /**
     * @brief Set light power (on/off).
     *
     * @param  power  The light power to be set
     */
    void light_driver_set_power(bool power);

    /**
     * @brief color light driver init, be invoked where you want to use color light
     *
     * @param power power on/off
     */
    esp_err_t light_driver_init(bool power);

#ifdef __cplusplus
} // extern "C"
#endif