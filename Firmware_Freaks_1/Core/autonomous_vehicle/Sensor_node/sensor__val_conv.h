#pragma once

#include "sensor__config.h"
#include <stdint.h>

#define sensValType_t uint16_t

uint16_t sens_val_conv__get_sens_val_in_cm(sensor_index current_sens);

void sens_val_conv__set_left_sens(uint16_t value);

void sens_val_conv__set_right_sens(uint16_t value);

void sens_val_conv__set_front_sens(uint16_t value);

void sens_val_conv__set_rear_sens(uint16_t value);

uint16_t sens_val_conv__get_left_sens(void);

uint16_t sens_val_conv__get_right_sens(void);

uint16_t sens_val_conv__get_front_sens(void);

uint16_t sens_val_conv__get_rear_sens(void);

void sens_val_conv__buffer_init(void);

void sens_val_conv__update_buffer(sensor_index current_sen, const sensValType_t current_val);

uint16_t sens_val_conv__get_filtered_val_in_cm(sensor_index current_sens);
