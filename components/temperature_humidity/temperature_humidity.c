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

#include "macros.h"
#include "dht22.h"
#include "temperature_humidity.h"
#include "esp_log.h"
#include "update_cluster.h"

static const char *TAG_TEMP_HUM = "TEMPERATURE_HUMIDITY_CHECK";

float _temperature, _humidity;
bool _new_data_temperature;
bool _new__data_humidity;

uint8_t _timer = 0;

esp_err_t get_dht22_data()
{
    if (dht_read_float_data(DHT_TYPE_AM2301, GPIO_NUM_0, &_humidity, &_temperature) == ESP_OK)
    {
        ESP_LOGI(TAG_TEMP_HUM, "Temperature : %.1f ℃", _temperature);
        ESP_LOGI(TAG_TEMP_HUM, "Humidity : %.1f %%", _humidity);
        _new__data_humidity = true;
        _new_data_temperature = true;
    }
    else
    {
        ESP_LOGW(TAG_TEMP_HUM, "Could not read data from DHT22 Sensor.");
        return ESP_ERR_INVALID_ARG;
    }
    return ESP_OK;
}

void check_temperature()
{
    if (_timer >= 30 || _timer == 0)
    {
        get_dht22_data();
        _timer = 0;
    }
    if (_new_data_temperature == true)
    {
        zb_update_temp((int16_t)(_temperature * 100));
        _new_data_temperature = false;
    }

    _timer++;
}

void check_humidity()
{
    if (_timer >= 30 || _timer == 0)
    {
        get_dht22_data();
        _timer = 0;
    }
    if (_new__data_humidity == true)
    {
        zb_update_hum((uint16_t)(_humidity * 100));
        _new__data_humidity = false;
    }
    _timer++;
}
