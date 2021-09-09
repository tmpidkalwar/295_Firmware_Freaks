#include <stdint.h>
#include <stdio.h>

//void motor_encoder__init(void);
void motor_encoder__periodic_handler(void);
uint32_t motor_encoder__get_rps(void);
float motor_encoder__get_speed(void);
