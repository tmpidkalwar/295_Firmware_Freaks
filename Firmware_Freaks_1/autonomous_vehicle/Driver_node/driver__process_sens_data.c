/**
 * @file driver_process_sens_data.c
 * @brief This file has the implementation of processing sensor data received.
 *      It converts sensor data to driver related parameters.
 *      All distance related parameters are in centi meter unit for this file.
 */

#include "driver__process_sens_data.h"

#include "sensor__val_conv.h"

/***************************************************************************************
 ****************************L O C A L    C O M P O N E N T S*************************
 ***************************************************************************************/

static uint16_t left_obstacle_distance_in_cm;
static uint16_t right_obstacle_distance_in_cm;
static uint16_t front_obstacle_distance_in_cm;
static uint16_t rear_obstacle_distance_in_cm;

static possible_steer_angle_range left_steering_possible_angles;
static possible_steer_angle_range right_steering_possible_angles;
static possible_speed_range forward_speed_range;
static possible_speed_range reverse_speed_range;

/**************Steering Data Process*****************/

const static uint16_t max_obstacle_dist_to_restrict_steering = 250;
const static uint16_t min_obstacle_dist_to_allow_steering = 85;
const static uint16_t min_angle = 0;
const static uint16_t max_angle = 45;
// const static float no_turn = 0;

static uint16_t get_steering_anlge_corresponding_to_obstacle_distance(uint16_t obstacle_distance) {
  uint16_t retVal = 0;
  retVal = (obstacle_distance - min_obstacle_dist_to_allow_steering) * (max_angle - min_angle) /
               (max_obstacle_dist_to_restrict_steering - min_obstacle_dist_to_allow_steering) +
           min_angle;
  return retVal;
}

const static uint16_t max_front_sensor_value_to_start_forcing_car_turn = 200;
const static uint16_t min_front_sensor_value_to_start_forcing_car_turn = 100;

static void update_min_possible_steering_angles(void) {
  if (front_obstacle_distance_in_cm < max_front_sensor_value_to_start_forcing_car_turn &&
      front_obstacle_distance_in_cm > min_front_sensor_value_to_start_forcing_car_turn) {
    left_steering_possible_angles.data.min_angle =
        (left_steering_possible_angles.data.max_angle == max_angle) ? max_angle : min_angle;
    left_steering_possible_angles.data.max_angle = left_steering_possible_angles.data.min_angle;

    right_steering_possible_angles.data.min_angle =
        (right_steering_possible_angles.data.max_angle == max_angle) ? max_angle : min_angle;
    right_steering_possible_angles.data.max_angle = right_steering_possible_angles.data.max_angle;

  } else if (front_obstacle_distance_in_cm < min_front_sensor_value_to_start_forcing_car_turn) {
    right_steering_possible_angles.is_possible = 0;
    left_steering_possible_angles.is_possible = 0;
  }
}

static void calculate_possible_steering_angle_range(void) {
  // left steering angle range
  // If left obstacle is farther than or equal to max threshold,
  if (left_obstacle_distance_in_cm >= max_obstacle_dist_to_restrict_steering) {
    left_steering_possible_angles.data.max_angle = max_angle;
    left_steering_possible_angles.data.min_angle = min_angle;
  } else if (left_obstacle_distance_in_cm >= min_obstacle_dist_to_allow_steering) {
    left_steering_possible_angles.data.max_angle =
        get_steering_anlge_corresponding_to_obstacle_distance(left_obstacle_distance_in_cm);
    left_steering_possible_angles.data.min_angle = 0;
  } else {
    left_steering_possible_angles.data.max_angle = 0;
    left_steering_possible_angles.data.min_angle = 0;
  }

  // Right steering angle range
  if (right_obstacle_distance_in_cm >= max_obstacle_dist_to_restrict_steering) {
    right_steering_possible_angles.data.max_angle = max_angle;
    right_steering_possible_angles.data.min_angle = min_angle;
  } else if (right_obstacle_distance_in_cm >= min_obstacle_dist_to_allow_steering) {
    right_steering_possible_angles.data.max_angle =
        get_steering_anlge_corresponding_to_obstacle_distance(right_obstacle_distance_in_cm);
    right_steering_possible_angles.data.min_angle = min_angle;
  } else {
    right_steering_possible_angles.data.max_angle = 0;
    right_steering_possible_angles.data.min_angle = 0;
  }
  update_min_possible_steering_angles();
}

/**************Speeding Data Process*****************/
const static uint16_t max_obstacle_dist_to_start_controlling_speed = 400;
const static uint16_t min_obstacle_dist_to_start_controlling_speed = 95;
const static float max_speed = 12.5;
const static float min_speed = 0;

static float get_speed_corresponding_to_obstacle_distance(uint16_t obstacle_distance) {
  uint16_t retVal = 0;
  retVal = (obstacle_distance - min_obstacle_dist_to_start_controlling_speed) * (max_speed - min_speed) /
               (max_obstacle_dist_to_start_controlling_speed - min_obstacle_dist_to_start_controlling_speed) +
           min_speed;
  return retVal;
}

static void update_driving_states(void) {

  if (front_obstacle_distance_in_cm >= max_front_sensor_value_to_start_forcing_car_turn) {
    forward_speed_range.drivingState = KEEP_GOING;
  } else if (front_obstacle_distance_in_cm < max_front_sensor_value_to_start_forcing_car_turn &&
             front_obstacle_distance_in_cm > min_front_sensor_value_to_start_forcing_car_turn) {
    forward_speed_range.drivingState = SOFT_STOP;
  } else if (front_obstacle_distance_in_cm <= min_front_sensor_value_to_start_forcing_car_turn) {
    forward_speed_range.drivingState = HARD_STOP;
  } else {
    forward_speed_range.drivingState = FAULT_STATE;
  }
}

static void calculate_possible_fwd_reverse_speed_range(void) {
  // Forward speed processing
  if (front_obstacle_distance_in_cm >= max_obstacle_dist_to_restrict_steering) {
    forward_speed_range.speed_data.max_speed = max_speed;
    forward_speed_range.speed_data.min_speed = min_speed;
  } else if (front_obstacle_distance_in_cm >= min_obstacle_dist_to_start_controlling_speed) {
    forward_speed_range.speed_data.max_speed =
        get_speed_corresponding_to_obstacle_distance(front_obstacle_distance_in_cm);
    forward_speed_range.speed_data.min_speed = min_speed;
  } else {
    forward_speed_range.speed_data.max_speed = min_speed;
    forward_speed_range.speed_data.min_speed = min_speed;
    // As car can'g move ahead, turn the car to the left or right at maximum possible angle
    // left_steering_possible_angles.data.min_angle = left_steering_possible_angles.data.max_angle;
    // right_steering_possible_angles.data.min_angle = right_steering_possible_angles.data.max_angle;
  }

  // Reverse speed processing
  if (rear_obstacle_distance_in_cm >= max_obstacle_dist_to_restrict_steering) {
    reverse_speed_range.speed_data.max_speed = max_speed;
    reverse_speed_range.speed_data.min_speed = min_speed;
    reverse_speed_range.drivingState = KEEP_GOING;
  } else if (rear_obstacle_distance_in_cm >= min_obstacle_dist_to_start_controlling_speed) {
    reverse_speed_range.speed_data.max_speed =
        get_speed_corresponding_to_obstacle_distance(rear_obstacle_distance_in_cm);
    reverse_speed_range.speed_data.min_speed = min_speed;
    reverse_speed_range.drivingState = KEEP_GOING;
  } else {
    reverse_speed_range.speed_data.max_speed = min_speed;
    reverse_speed_range.speed_data.min_speed = min_speed;
    reverse_speed_range.drivingState = HARD_STOP;
  }
  update_driving_states();
}

/***************************************************************************************
 ****************************G L O B A L    C O M P O N E N T S*************************
 ***************************************************************************************/

void driver_process_sens_data__process_input(dbc_SENSOR_SONARS_s *sensor_data) {
  if (sensor_data == NULL) {
    return;
  }
  left_obstacle_distance_in_cm = sens_val_conv__get_filtered_val_in_cm(LEFT_SENSOR);
  right_obstacle_distance_in_cm = sens_val_conv__get_filtered_val_in_cm(RIGHT_SENSOR);
  front_obstacle_distance_in_cm = sens_val_conv__get_filtered_val_in_cm(FRONT_SENSOR);
  rear_obstacle_distance_in_cm = sens_val_conv__get_filtered_val_in_cm(REAR_SENSOR);
  calculate_possible_steering_angle_range();
  calculate_possible_fwd_reverse_speed_range();
}

possible_speed_range driver_process_sens_data__get_fwd_speed_range(void) { return forward_speed_range; }

possible_speed_range driver_process_sens_data__get_reverse_speed_range(void) { return reverse_speed_range; }

possible_steer_angle_range driver_process_sens_data__get_left_steer_range(void) {
  return left_steering_possible_angles;
}

possible_steer_angle_range driver_process_sens_data__get_right_steer_range(void) {
  return right_steering_possible_angles;
}

//dbc_DRIVER_DEBUG_DATA_s driver_process_sens_data__get_debug_data(void) {
//  dbc_DRIVER_DEBUG_DATA_s driver_debug_data;
//  driver_debug_data.forwardDrivingState = forward_speed_range.drivingState;
//  driver_debug_data.reverseDrivingState = reverse_speed_range.drivingState;
//  driver_debug_data.isRightSteeringPossible = right_steering_possible_angles.is_possible;
//  driver_debug_data.isLeftSteeringPossible = left_steering_possible_angles.is_possible;
//  return driver_debug_data;
//}
