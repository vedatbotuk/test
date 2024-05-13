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

#ifndef MACROS_H
#define MACROS_H 

// TODO: Rename the Macros. For example WATERLEAK_FEATURES, TEMPERATURE_FEATURES

#if (SENSOR_MAP >> 0 & 1) == 1
#define AUTOMATIC_IRRIGATION true
#endif

#if (SENSOR_MAP >> 1 & 1) == 1
#define SENSOR_WATERLEAK true
#endif

#if (SENSOR_MAP >> 2 & 1) == 1
#define DEEP_SLEEP true
#endif

#if (SENSOR_MAP >> 3 & 1) == 1
#define LIGHT_SLEEP true
#endif

#if (SENSOR_MAP >> 4 & 1) == 1
#define BATTERY true
#endif

#if (SENSOR_MAP >> 5 & 1) == 1
#define SENSOR_TEMPERATURE true
#endif

#if (SENSOR_MAP >> 6 & 1) == 1
#define SENSOR_HUMIDITY true
#endif

#if (SENSOR_MAP >> 7 & 1) == 1
#define OTA_UPDATE true
#endif

#endif /* MACROS_H */
