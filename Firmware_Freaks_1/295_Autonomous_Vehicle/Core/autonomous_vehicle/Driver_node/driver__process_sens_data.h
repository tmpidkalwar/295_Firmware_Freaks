#pragma once

//#include "project.h"
#include <stdint.h>

typedef enum driving_states {
  HARD_STOP = 0,
  SOFT_STOP,  // Try to change direction as obstacle nearing ahead if possible, otherwise try to stop
  KEEP_GOING, // As no obstacle ahead
  FAULT_STATE
} driving_states;

typedef union possible_steer_angle_range {
  uint32_t is_possible;
  struct data {
    uint16_t min_angle;
    uint16_t max_angle;
  } data;
} possible_steer_angle_range;

typedef struct possible_speed_range {
  driving_states drivingState;
  struct speed_data {
    float min_speed;
    float max_speed;
  } speed_data;
} possible_speed_range;

void driver_process_sens_data__process_input(void);

possible_speed_range driver_process_sens_data__get_fwd_speed_range(void);

possible_speed_range driver_process_sens_data__get_reverse_speed_range(void);

possible_steer_angle_range driver_process_sens_data__get_left_steer_range(void);

possible_steer_angle_range driver_process_sens_data__get_right_steer_range(void);

//dbc_DRIVER_DEBUG_DATA_s driver_process_sens_data__get_debug_data(void);
