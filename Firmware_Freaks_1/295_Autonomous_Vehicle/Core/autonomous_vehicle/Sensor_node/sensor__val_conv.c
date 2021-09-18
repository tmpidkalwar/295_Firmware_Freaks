#include "sensor__val_conv.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct sens_val_buff {
  sensValType_t *buff;
  int current_pointer; // Points to next available index
} sens_val_buff;

extern uint32_t sensor_config__read_sens_raw_value(sensor_index current_sensor);

sens_val_buff sens_data_buff[MAX_SENSOR];
static const uint16_t buffer_size = 10;
static const uint16_t filter_sample_count = 7;

static int compare(const void *p1, const void *p2) { return (*(sensValType_t *)p1 - *(sensValType_t *)p2); }

// NOTE: sample count should be odd number always
static sensValType_t calc_avg_of_median_samples_in_buffer(uint16_t *arr, size_t odd_sample_count) {
  int median_index = buffer_size / 2 - 1;
  int index_offset = odd_sample_count / 2;
  sensValType_t result = 0;
  for (int i = (median_index - index_offset); i <= (median_index + index_offset); i++) {
    result += arr[i];
  }
  return result / odd_sample_count;
}

void sens_val_conv__buffer_init(void) {
  for (int i = 0; i < MAX_SENSOR; i++) {
    sens_data_buff[i].buff = calloc(buffer_size, sizeof(sensValType_t));
    sens_data_buff[i].current_pointer = 0;
  }
}

void sens_val_conv__update_buffer(sensor_index current_sen, const sensValType_t current_val) {
  sens_data_buff[current_sen].buff[sens_data_buff[current_sen].current_pointer] = current_val;

  sens_data_buff[current_sen].current_pointer = (sens_data_buff[current_sen].current_pointer + 1) % buffer_size;
}

sensValType_t sens_val_conv__get_filtered_val_in_cm(sensor_index current_sens) {
  qsort(sens_data_buff[current_sens].buff, buffer_size, sizeof(sensValType_t), compare);
  return calc_avg_of_median_samples_in_buffer(sens_data_buff[current_sens].buff, filter_sample_count);
}

/**
 * This is MB1000-00 LV-EZ0 ultrasonic sensor. Max range is 254 inches. (645 cm).
 * Precision => (Vcc/512) = 1 inch = 25 mm.  Our ADC is 12 bit, so our precision is 8 times higher.
 * Each ADC value = 25 / 8 = 3 mm. or 0.38
 */

uint16_t sens_val_conv__get_sens_val_in_cm(sensor_index current_sens) {
  uint16_t conv_val = 0;
  uint32_t raw_val = 0;

  raw_val = sensor_config__read_sens_raw_value(current_sens);

  if (current_sens != REAR_SENSOR) {
    // This calculation is for LV EZ sensors
    conv_val = (raw_val * 0.3182) - 0.3959;
  } else {
    // NOTE: HRLV0 EZ0 max range is 500 cm
    conv_val = (raw_val * 5) / 4;
    conv_val /= 10;
  }

  return raw_val;//conv_val;
}

/*****************Without Buffer Operation**************************************/
static uint16_t left_sens_dist;
static uint16_t right_sens_dist;
static uint16_t front_sens_dist;
static uint16_t rear_sens_dist;

void sens_val_conv__set_left_sens(uint16_t value) { left_sens_dist = value; }

void sens_val_conv__set_right_sens(uint16_t value) { right_sens_dist = value; }

void sens_val_conv__set_front_sens(uint16_t value) { front_sens_dist = value; }

void sens_val_conv__set_rear_sens(uint16_t value) { rear_sens_dist = value; }

uint16_t sens_val_conv__get_left_sens(void) { return left_sens_dist; }

uint16_t sens_val_conv__get_right_sens(void) { return right_sens_dist; }

uint16_t sens_val_conv__get_front_sens(void) { return front_sens_dist; }

uint16_t sens_val_conv__get_rear_sens(void) { return rear_sens_dist; }
