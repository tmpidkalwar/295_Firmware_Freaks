#pragma once

#include "stdint.h"

typedef enum sensor_index { FRONT_SENSOR = 0, LEFT_SENSOR, RIGHT_SENSOR, REAR_SENSOR, MAX_SENSOR } sensor_index;

void sensor_config__ultrasonic_sensors_init(void);

uint32_t sensor_config__read_sens_raw_value(sensor_index current_sensor);

void sensor_node__init_trigger_pins_as_gpio(void);

void sensor_node__trigger_Left_ultrasonic(void);

void sensor_node__trigger_Front_ultrasonic(void);

void sensor_node__trigger_Right_ultrasonic(void);
