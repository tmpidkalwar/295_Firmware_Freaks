#include <stdint.h>

void motor_esc__init();
void motor_esc__control_speed(float);
void motor_esc__stop_motor();
void motor_esc__steer_handler(int8_t angle);
void motor_esc__self_test(uint32_t callback_count);
void motor_esc__maintain_speed();

float get_servo_motor_pwm();
float get_dc_motor_pwm();