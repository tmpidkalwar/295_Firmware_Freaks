#include <stdio.h>
#include <stdbool.h>

#include "motor_encoder.h"
#include "motor_esc.h"

#include "stm32f4xx_hal.h"

TIM_HandleTypeDef htim2; //SERVO_PWM
TIM_HandleTypeDef htim3; //DC_MOTOR_PWM

typedef enum {
  RIGHT_1 = 0,
  RIGHT_2,
  RIGHT_3,
  RIGHT_4,
  RIGHT_5,
  RIGHT_6,
  RIGHT_7,
  RIGHT_8,
  RIGHT_9,
  LEFT_1,
  LEFT_2,
  LEFT_3,
  LEFT_4,
  LEFT_5,
  LEFT_6,
  LEFT_7,
  LEFT_8,
  LEFT_9,
  STRAIGHT
} steer_angles_e;


// Setup Values
//static const gpio_s motor_dc = {2, 0}, motor_servo = {2, 1};
//static const int pwm_dc_motor = PWM1__2_0;
//static const int pwm_servo_motor = PWM1__2_1;
//static const uint32_t PWM_FREQUENCY = 100;
//
//static uint32_t initial_callback_count;
//static bool test_flag = true;
//
//static float calculated_pwm;
static float steer_pwm_val;


//gpio_s left_ind = {0, 26};
//gpio_s right_ind = {1, 20};
//gpio_s mid_ind = {1, 31};
//gpio_s buzzer = {1, 28};
static bool boost_pwm = false;
// ESC values
static float PWM_NEUTRAL = 15.00;
static float PWM_SPEED_1 = 15.91;
static float PWM_SPEED_2 = 15.94;
static float PWM_SPEED_3 = 15.97;
static float PWM_SPEED_4 = 16.01;
static float PWM_SPEED_5 = 16.06;
static float PWM_SPEED_6 = 16.10;
static float PWM_SPEED_7 = 16.14;
static float PWM_SPEED_8 = 16.18;
static float PWM_SPEED_9 = 16.22;
static float PWM_SPEED_10 = 16.26;
static float PWM_SPEED_11 = 16.30;
static float PWM_SPEED_12 = 16.33;
static float PWM_SPEED_13 = 16.36;

static float PWM_REVERSE = 14.2;
static float PWM_FULL_REVERSE = 10;

static float increment_factor = 0.01;
static float decrement_factor = 0.2;

static bool reverse_flag = false;
static bool hard_brake = false;
static const float SPEED_ZERO = 0;
static const float SPEED_L1 = 1;
static const float SPEED_L2 = 1;
static const float SPEED_L3 = 1;
//static const float SPEED_R = 0;

// Servo values
static const float PWM_LEFT_1 = 11.0;
static const float PWM_LEFT_2 = 11.5;
static const float PWM_LEFT_3 = 12.0;
static const float PWM_LEFT_4 = 12.5;
static const float PWM_LEFT_5 = 13.0;
static const float PWM_LEFT_6 = 13.5;
static const float PWM_LEFT_7 = 14.0;
static const float PWM_LEFT_8 = 14.5;
static const float PWM_LEFT_9 = 14.8;
static const float PWM_STRAIGHT = 15.0;
static const float PWM_RIGHT_9 = 15.2;
static const float PWM_RIGHT_8 = 15.5;
static const float PWM_RIGHT_7 = 16.0;
static const float PWM_RIGHT_6 = 16.5;
static const float PWM_RIGHT_5 = 17.0;
static const float PWM_RIGHT_4 = 17.5;
static const float PWM_RIGHT_3 = 18.0;
static const float PWM_RIGHT_2 = 18.5;
static const float PWM_RIGHT_1 = 19.0;

static void motor_esc__set_steer_angle(float);
static void motor_esc__set_motor_speed(float);

//void motor_esc__init() {
////  gpio__construct_as_output(motor_dc.port_number, motor_dc.pin_number);
////  gpio__construct_as_output(motor_servo.port_number, motor_servo.pin_number);
////  gpio__construct_with_function(motor_dc.port_number, motor_dc.pin_number, GPIO__FUNCTION_1);
//  gpio__construct_with_function(motor_servo.port_number, motor_servo.pin_number, GPIO__FUNCTION_1);
//  pwm1__init_single_edge(PWM_FREQUENCY);
//
//  gpio__set_as_output(debug_l0);
//  gpio__set_as_output(debug_l1);
//  gpio__set_as_output(debug_l2);
//  gpio__set_as_output(debug_l3);
//  gpio__set_as_output(buzzer);
//  gpio__reset(debug_l0);
//  gpio__reset(debug_l1);
//  gpio__reset(debug_l2);
//  gpio__reset(debug_l3);
//  gpio__reset(buzzer);
//
//  gpio__set_as_output(left_ind);
//  gpio__set_as_output(right_ind);
//  gpio__set_as_output(mid_ind);
//  gpio__reset(left_ind);
//  gpio__reset(right_ind);
//  gpio__reset(mid_ind);
//}

int received_speed = 0;
float calculated_pwm_dc = 15;

static uint8_t reverse_counter = 0;

void motor_esc__control_speed(float motor_speed) {
//  int current_speed_from_enc = motor_encoder__get_speed();
//  if (motor_speed <= 0) {
//    boost_pwm = false;
//    reverse_counter++;
//    if (reverse_flag) {
//      calculated_pwm_dc = PWM_REVERSE;
////      if (motor_speed < 0)
////        gpio__set(buzzer);
//    }
//
//    if (reverse_counter >= 1 && (!reverse_flag)) {
//      //      received_speed = SPEED_R;
//      if (reverse_counter < 8) {
//        calculated_pwm_dc = PWM_FULL_REVERSE;
////        gpio__set(mid_ind);
//      }
//      if (reverse_counter >= 8 && reverse_counter < 11) {
//        calculated_pwm_dc = PWM_NEUTRAL;
//      }
//      if (reverse_counter >= 11) {
//        if (motor_encoder__get_rps() != 0) {
//          reverse_counter = 9;
//        } else {
//          calculated_pwm_dc = PWM_REVERSE;
//          reverse_flag = true;
//          reverse_counter = 0;
//        }
//      }
////      gpio__reset(board_io__get_led1());
//    }
//  }
//  // HERE END
//  else {
//    reverse_flag = false;
//    reverse_counter = 0;
////    gpio__set(board_io__get_led1());
////    gpio__reset(buzzer);
//
//    static uint8_t boost_count = 0;
//    if (motor_encoder__get_rps() == 0) {
//      boost_count++;
//      if (boost_count > 65 && boost_count < 76) {
//        boost_pwm = true;
//      } else {
//        boost_pwm = false;
//      }
//    } else {
//      boost_count = 0;
//      boost_pwm = false;
//    }
//  }
//
//  if (motor_speed >= 0 && motor_speed < (float)(0.5)) {
//    if (!hard_brake) {
//      hard_brake = true;
//      received_speed = SPEED_ZERO;
//      calculated_pwm_dc = PWM_FULL_REVERSE;
//
//    } else {
//      calculated_pwm_dc = PWM_NEUTRAL;
//    }
//  } else if (motor_speed >= (float)(0.5) && motor_speed < 1) {
//    hard_brake = false;
//    received_speed = SPEED_L1;
//    calculated_pwm_dc = PWM_SPEED_1;
//  } else if (motor_speed >= 1 && motor_speed < 2) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_2;
//  } else if (motor_speed >= 2 && motor_speed < 3) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_3;
//  } else if (motor_speed >= 3 && motor_speed < 4) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_4;
//  } else if (motor_speed >= 4 && motor_speed < 5) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_5;
//  } else if (motor_speed >= 5 && motor_speed < 6) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_6;
//  } else if (motor_speed >= 6 && motor_speed < 7) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_7;
//  } else if (motor_speed >= 7 && motor_speed < 8) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_8;
//  } else if (motor_speed >= 8 && motor_speed < 9) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_9;
//  } else if (motor_speed >= 9 && motor_speed < 10) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_10;
//  } else if (motor_speed >= 10 && motor_speed < 11) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_11;
//  } else if (motor_speed >= 11 && motor_speed < 12) {
//    hard_brake = false;
//    received_speed = SPEED_L2;
//    calculated_pwm_dc = PWM_SPEED_12;
//  } else if (motor_speed >= 12) {
//    hard_brake = false;
//    received_speed = SPEED_L3;
//    calculated_pwm_dc = PWM_SPEED_13;
//  } else {
//    // received_speed = SPEED_ZERO;
//    // calculated_pwm_dc = 15;
//  }
//  // }
//  //  }

  motor_esc__set_motor_speed(motor_speed);
}


void motor_esc__maintain_speed() {
  int speed_from_encoder = motor_encoder__get_speed();

  if (speed_from_encoder < received_speed) {
    calculated_pwm_dc += increment_factor;
    if (calculated_pwm_dc >= PWM_SPEED_3)
      calculated_pwm_dc = PWM_SPEED_3;
  }

  else if (speed_from_encoder > received_speed) {
    calculated_pwm_dc -= decrement_factor;
    if (calculated_pwm_dc <= (float)15)
      calculated_pwm_dc = 15;
  }
}

void motor_esc__stop_motor() { motor_esc__set_motor_speed(PWM_NEUTRAL); }

void motor_esc__steer_handler(int8_t angle) {
  uint8_t calculated_angle = PWM_STRAIGHT;

  if (angle >= (-45) && angle <= (-40))
    calculated_angle = RIGHT_1;
  else if (angle > (-40) && angle < (-35))
    calculated_angle = RIGHT_2;
  else if (angle >= (-35) && angle < (-30))
    calculated_angle = RIGHT_3;
  else if (angle >= (-30) && angle < (-25))
    calculated_angle = RIGHT_4;
  else if (angle >= (-25) && angle < (-20))
    calculated_angle = RIGHT_5;
  else if (angle >= (-20) && angle < (-15))
    calculated_angle = RIGHT_6;
  else if (angle >= (-15) && angle < (-10))
    calculated_angle = RIGHT_7;
  else if (angle >= (-10) && angle < (-5))
    calculated_angle = RIGHT_8;
  else if (angle >= (-5) && angle < (0))
    calculated_angle = RIGHT_9;
  else if (angle == 0)
    calculated_angle = STRAIGHT;
  else if (angle > 0 && angle < 5)
    calculated_angle = LEFT_9;
  else if (angle >= 5 && angle < 10)
    calculated_angle = LEFT_8;
  else if (angle >= 10 && angle < 15)
    calculated_angle = LEFT_7;
  else if (angle >= 15 && angle < 20)
    calculated_angle = LEFT_6;
  else if (angle >= 20 && angle < 25)
    calculated_angle = LEFT_5;
  else if (angle >= 25 && angle < 30)
    calculated_angle = LEFT_4;
  else if (angle >= 30 && angle < 35)
    calculated_angle = LEFT_3;
  else if (angle >= 35 && angle < 40)
    calculated_angle = LEFT_2;
  else if (angle >= 40 && angle <= 45)
    calculated_angle = LEFT_1;

  switch (calculated_angle) {
  case LEFT_1:
    motor_esc__set_steer_angle(PWM_LEFT_1);
    break;

  case LEFT_2:
    motor_esc__set_steer_angle(PWM_LEFT_2);
    break;

  case LEFT_3:
    motor_esc__set_steer_angle(PWM_LEFT_3);
    break;

  case LEFT_4:
    motor_esc__set_steer_angle(PWM_LEFT_4);
    break;
  case LEFT_5:
    motor_esc__set_steer_angle(PWM_LEFT_5);
    break;
  case LEFT_6:
    motor_esc__set_steer_angle(PWM_LEFT_6);
    break;
  case LEFT_7:
    motor_esc__set_steer_angle(PWM_LEFT_7);
    break;
  case LEFT_8:
    motor_esc__set_steer_angle(PWM_LEFT_8);
    break;
  case LEFT_9:
    motor_esc__set_steer_angle(PWM_LEFT_9);
    break;
  case RIGHT_1:
    motor_esc__set_steer_angle(PWM_RIGHT_1);

    break;

  case RIGHT_2:
    motor_esc__set_steer_angle(PWM_RIGHT_2);
    break;

  case RIGHT_3:
    motor_esc__set_steer_angle(PWM_RIGHT_3);
    break;

  case RIGHT_4:
    motor_esc__set_steer_angle(PWM_RIGHT_4);
    break;
  case RIGHT_5:
    motor_esc__set_steer_angle(PWM_RIGHT_5);
    break;
  case RIGHT_6:
    motor_esc__set_steer_angle(PWM_RIGHT_6);
    break;
  case RIGHT_7:
    motor_esc__set_steer_angle(PWM_RIGHT_7);
    break;
  case RIGHT_8:
    motor_esc__set_steer_angle(PWM_RIGHT_8);
    break;
  case RIGHT_9:
    motor_esc__set_steer_angle(PWM_RIGHT_9);
    break;

  case STRAIGHT:
    motor_esc__set_steer_angle(PWM_STRAIGHT);
    break;

  default:
    break;
  }
}
float get_dc_motor_pwm() { return calculated_pwm_dc; }

float get_servo_motor_pwm() { return steer_pwm_val; }

// Private Functions
static void motor_esc__set_steer_angle(float servo_pwm_val) {
  //  fprintf(stderr, " Current pwm val on servo : %f", steer_pwm_val);
  steer_pwm_val = 5;//servo_pwm_val;
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, servo_pwm_val);  //Set Servo Duty cycle
}

static void motor_esc__set_motor_speed(float motor_speed) {
  calculated_pwm_dc = motor_speed;
  // fprintf(stderr, "Current DC Pwm : %f\n", calculated_pwm_dc);
//  if (boost_pwm && (motor_speed > 15.7f)) {
//    motor_speed = motor_speed + 0.25;
//    boost_pwm = false;
//  }
  // Pin Congiguration: PA 6
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, motor_speed);  //Set DC motor Duty cycle
}
