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

#include "dht22.h"
#include "temperature_humidity.h"
#include "esp_log.h"
#include "update_cluster.h"
#include "macros.h"

static const char *TAG_TEMP_HUM = "TEMPERATURE_HUMIDITY_CHECK";

static float temperature = 0.0f;
static float humidity = 0.0f;

static esp_err_t read_dht22_data()
{
    esp_err_t result = dht_read_float_data(DHT_TYPE_AM2301, GPIO_NUM_0, &humidity, &temperature);
    if (result == ESP_OK)
    {
        ESP_LOGI(TAG_TEMP_HUM, "Temperature : %.1f ℃", temperature);
        ESP_LOGI(TAG_TEMP_HUM, "Humidity : %.1f %%", humidity);
    }
    else
    {
        ESP_LOGW(TAG_TEMP_HUM, "Could not read data from DHT22 Sensor.");
    }
    return result;
}

void check_temperature()
{
#if defined SENSOR_TEMPERATURE
    read_dht22_data();
#endif
    zb_update_temp((int16_t)(temperature * 100));
}

void check_humidity()
{
#if !defined SENSOR_TEMPERATURE
    read_dht22_data();
#endif
    zb_update_hum((uint16_t)(humidity * 100));
}