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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc_caps.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "update_cluster.h"
#include "random_utils.h"
#include "macros.h"

const static char *TAG_VOL = "VOLTAGE";

#if !defined SIMULATE

#define VOLTAGE_MAX 3000
#define VOLTAGE_MIN 1500
#define CHECK_ARG(VAL)                  \
    do                                  \
    {                                   \
        if (!(VAL))                     \
            return ESP_ERR_INVALID_ARG; \
    } while (0)

// ADC1 Channels
#define EXAMPLE_ADC1_CHAN0 ADC_CHANNEL_0
#define EXAMPLE_ADC_ATTEN ADC_ATTEN_DB_12

static adc_oneshot_unit_handle_t adc1_handle;
static int adc_raw[2][10];
static uint8_t battery_lev;
static uint8_t battery_vol;

static esp_err_t voltage_calculate_init(void)
{
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = EXAMPLE_ADC_ATTEN,
    };

    return adc_oneshot_config_channel(adc1_handle, EXAMPLE_ADC1_CHAN0, &config);
}

static esp_err_t voltage_calculate_deinit(void)
{
    return adc_oneshot_del_unit(adc1_handle);
}

static uint8_t calc_battery_percentage(int adc)
{
    int battery_percentage = 100 * ((float)adc - VOLTAGE_MIN) / (VOLTAGE_MAX - VOLTAGE_MIN);
    return battery_percentage < 0 ? 0 : battery_percentage;
}
#endif

esp_err_t get_battery_level(void)
{
#if !defined SIMULATE
    voltage_calculate_init();
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, EXAMPLE_ADC1_CHAN0, &adc_raw[0][0]));
    voltage_calculate_deinit();
    ESP_LOGI(TAG_VOL, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_1 + 1, EXAMPLE_ADC1_CHAN0, adc_raw[0][0]);

    battery_vol = (uint8_t)(adc_raw[0][0] / 10);
    battery_lev = calc_battery_percentage(adc_raw[0][0]);

    ESP_LOGI(TAG_VOL, "Battery level: %d %%", battery_lev);
    ESP_LOGI(TAG_VOL, "Battery voltage: %d mV", battery_vol);
#else
    int battery_lev = random_utils_generate(101); // Generate a random temperature between 0 and 100
    int battery_vol = random_utils_generate(4);   // Generate a random temperature between 0 and 3
    ESP_LOGI(TAG_VOL, "SIMULATE Battery level: %d %%", battery_lev);
    ESP_LOGI(TAG_VOL, "SIMULATE Battery voltage: %d mV", battery_vol);
#endif
    zb_update_battery_level((uint8_t)(2 * battery_lev), (uint8_t)(battery_vol));
#ifdef DEEP_SLEEP
    zb_report_battery_level();
#endif
    return ESP_OK;
}
