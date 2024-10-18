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

#include "esp_log.h"
#include "pump_switch.h"
#include "driver/gpio.h"

static const char *TAG_PUMP_SWITCH = "AUTOMATIC_IRRIGATION";
// static led_strip_handle_t s_led_strip;

void relay_set_power(bool power)
{
    ESP_ERROR_CHECK(gpio_set_level(8, 1));
    ESP_LOGI(TAG_PUMP_SWITCH, "Dummy LOG");
}

esp_err_t relay_driver_init(bool power)
{
    gpio_set_direction(8, GPIO_MODE_OUTPUT);
    relay_set_power(power);
    return ESP_OK;
}