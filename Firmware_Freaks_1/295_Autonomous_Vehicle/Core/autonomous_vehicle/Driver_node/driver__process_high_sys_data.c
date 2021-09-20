#include "driver__process_sens_data.h"

#include <stdlib.h>
#include <stdbool.h>

#include "driver__process_high_sys_data.h"

static uint16_t geo_destination_angle;
static float geo_destination_distance;
static bool at_the_destination = false;
bool car_stopped = false;
bool destination_reached() { return at_the_destination; }

static void __get_motor_data_to_stop(driver_to_motor_data *motor_data) {
  motor_data->MOTOR_direction = 0;
  motor_data->MOTOR_speed = 0;
  return;
}

static float get_speed_from_angle(uint16_t angle) {
  float speed;
  float speed_diff;
  float step_size_per_degree;
  float max_speed;
  float min_speed;
  uint8_t req_angle_offset;

  // TODO, use macros to get min max speed and angles
  max_speed = MAX_SPEED_WHILE_TURNING;
  min_speed = MIN_SPEED_WHILE_TURNING;
  speed_diff = max_speed - min_speed;
  step_size_per_degree = (float)speed_diff / MAX_ALLOWED_TURN_ANGLE;

  speed = max_speed - (angle * step_size_per_degree);
  return speed;
}

static bool get_min_left_motor_data(driver_to_motor_data *motor_data) {
  possible_steer_angle_range left_steer_angle_range;
  left_steer_angle_range = driver_process_sens_data__get_left_steer_range();
  if (left_steer_angle_range.is_possible) {
    motor_data->MOTOR_direction = left_steer_angle_range.data.min_angle;
    motor_data->MOTOR_speed = get_speed_from_angle(left_steer_angle_range.data.min_angle);
    return 1;
  }
  return 0;
}

static bool get_min_right_motor_data(driver_to_motor_data *motor_data) {
  possible_steer_angle_range right_steer_angle_range;
  right_steer_angle_range = driver_process_sens_data__get_right_steer_range();
  if (right_steer_angle_range.is_possible) {
    motor_data->MOTOR_direction = (-1) * right_steer_angle_range.data.min_angle;
    motor_data->MOTOR_speed = get_speed_from_angle(right_steer_angle_range.data.min_angle);
    return 1;
  }
  return 0;
}

static bool get_min_reverse_motor_data(driver_to_motor_data *motor_data) {
  possible_speed_range reverse_speed_range;
  static int cnt = 0;
  reverse_speed_range = driver_process_sens_data__get_reverse_speed_range();
  if (reverse_speed_range.drivingState == KEEP_GOING) {
    if (cnt % 2 == 0) {
      motor_data->MOTOR_direction = MIN_REVERSE_ANGLE;
    } else {
      motor_data->MOTOR_direction = (-1) * MIN_REVERSE_ANGLE;
    }
    motor_data->MOTOR_speed = MIN_REVERSE_SPEED_GEO;
    return 1;
  }
  return 0;
}

static bool get_min_forward_motor_data(driver_to_motor_data *motor_data) {
  possible_speed_range forward_speed_range;
  forward_speed_range = driver_process_sens_data__get_fwd_speed_range();
  if (forward_speed_range.drivingState == KEEP_GOING) {
    motor_data->MOTOR_direction = MIN_FORWARD_ANGLE;
    motor_data->MOTOR_speed = GET_MIN(MIN_FORWARD_SPEED_GEO, forward_speed_range.speed_data.max_speed);
    return 1;
  }
  return 0;
}

static bool get_max_forward_motor_data(driver_to_motor_data *motor_data) {
  possible_speed_range forward_speed_range;
  forward_speed_range = driver_process_sens_data__get_fwd_speed_range();
  if (forward_speed_range.drivingState == KEEP_GOING) {
    motor_data->MOTOR_direction = 0;
    motor_data->MOTOR_speed = forward_speed_range.speed_data.max_speed;
    return 1;
  }
  return 0;
}

static void try_to_go_straight(driver_to_motor_data *motor_data) {
  possible_speed_range forward_speed_range;

  forward_speed_range = driver_process_sens_data__get_fwd_speed_range();
  if (forward_speed_range.drivingState == KEEP_GOING) {
    // TODO
    (void)get_max_forward_motor_data(motor_data);
  } else if (get_min_left_motor_data(motor_data)) {

  } else if (get_min_right_motor_data(motor_data)) {

  } else if (get_min_reverse_motor_data(motor_data)) {

  } else {
    __get_motor_data_to_stop(motor_data);
  }
  return;
}

static void get_motor_data_to_turn(uint16_t angle, driver_to_motor_data *motor_data,
                                   possible_steer_angle_range steer_angle_range) {
  uint16_t possible_turn_angle;
  if ((angle > 0) && (angle <= steer_angle_range.data.min_angle)) {
    possible_turn_angle = steer_angle_range.data.min_angle;
  } else if ((angle >= steer_angle_range.data.min_angle) && (angle <= steer_angle_range.data.max_angle)) {
    possible_turn_angle = angle;
  } else if (angle > steer_angle_range.data.max_angle) {
    possible_turn_angle = steer_angle_range.data.max_angle;
  } else {
    // TODO: Should never hit this. Ideally should assert
  }
  motor_data->MOTOR_direction = possible_turn_angle;
  motor_data->MOTOR_speed = get_speed_from_angle(possible_turn_angle);
  // motor_data->MOTOR_speed = 2.5;
}

static void try_to_go_right(uint16_t angle, driver_to_motor_data *motor_data) {
  possible_steer_angle_range right_steer_angle_range;
  right_steer_angle_range = driver_process_sens_data__get_right_steer_range();
  if (right_steer_angle_range.is_possible) {
    // TODO
    get_motor_data_to_turn(angle, motor_data, right_steer_angle_range);
    motor_data->MOTOR_direction = (-1) * motor_data->MOTOR_direction;
  } else if (get_min_left_motor_data(motor_data)) {

  } else if (get_max_forward_motor_data(motor_data)) {

  } else if (get_min_reverse_motor_data(motor_data)) {

  } else {
    __get_motor_data_to_stop(motor_data);
  }
  return;
}

static void try_to_go_left(uint16_t angle, driver_to_motor_data *motor_data) {
  possible_steer_angle_range left_steer_angle_range;
  left_steer_angle_range = driver_process_sens_data__get_left_steer_range();

  if (left_steer_angle_range.is_possible) {
    // TODO
    get_motor_data_to_turn(angle, motor_data, left_steer_angle_range);
  } else if (get_min_right_motor_data(motor_data)) {

  } else if (get_max_forward_motor_data(motor_data)) {

  } else if (get_min_reverse_motor_data(motor_data)) {

  } else {
    __get_motor_data_to_stop(motor_data);
  }
  return;
}

static void __get_motor_commands(driver_to_motor_data *motor_data) {

  possible_speed_range forward_speed_range;

  forward_speed_range = driver_process_sens_data__get_fwd_speed_range();

  if (geo_destination_distance == (float)(999)) {
    __get_motor_data_to_stop(motor_data);
    return;
  }

  if ((geo_destination_distance < (float)DESTINATION_THRESHOLD_DISTANCE)) {
    // Send Stop Signal to car
    __get_motor_data_to_stop(motor_data);
    at_the_destination = true;
  } else if (geo_destination_angle >= 350 && geo_destination_angle <= 10) {
    //
    try_to_go_straight(motor_data);
  } else if ((geo_destination_angle) > 10 && (geo_destination_angle <= 180)) {
    //
    try_to_go_right(geo_destination_angle, motor_data);
  } else {
    try_to_go_left(360 - geo_destination_angle, motor_data);
  }
}

driver_to_motor_data driver_process_geo_data__get_motor_data() {
	driver_to_motor_data motor_data = {.MOTOR_direction = 0, .MOTOR_speed = 0};
  __get_motor_commands(&motor_data);
  return motor_data;
}


void driver_process_geo_data__process_input(high_sys_data *high_sys_data) {
  geo_destination_angle = high_sys_data->HEADING;
  geo_destination_distance = high_sys_data->DISTANCE;
  at_the_destination = false;
  return;
}
