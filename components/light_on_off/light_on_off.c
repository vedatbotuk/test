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
#include "led_strip.h"
#include "light_on_off.h"

static led_strip_handle_t s_led_strip;
static uint8_t s_red = 255, s_green = 255, s_blue = 255;

void light_driver_set_power(bool power)
{
  ESP_ERROR_CHECK(led_strip_set_pixel(s_led_strip, 0, s_red * power, s_green * power, s_blue * power));
  ESP_ERROR_CHECK(led_strip_refresh(s_led_strip));
}

void light_driver_init(bool power)
{
  led_strip_config_t led_strip_conf = {
      .max_leds = CONFIG_EXAMPLE_STRIP_LED_NUMBER,
      .strip_gpio_num = CONFIG_EXAMPLE_STRIP_LED_GPIO,
  };
  led_strip_rmt_config_t rmt_conf = {
      .resolution_hz = 10 * 1000 * 1000, // 10MHz
  };
  ESP_ERROR_CHECK(led_strip_new_rmt_device(&led_strip_conf, &rmt_conf, &s_led_strip));

  light_driver_set_power(power);
}