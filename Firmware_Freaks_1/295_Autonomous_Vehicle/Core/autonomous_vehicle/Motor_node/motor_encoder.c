#include "motor_encoder.h"

#include "stm32f4xx_hal.h"

#define PI 3.14

static uint32_t rps = 0;

static float rotation_to_convert = 0;

static uint32_t rotation_counter = 0;
static uint32_t observed_rotation_count = 0;
// static uint32_t observation_period_in_ms = 500;

static float wheel_radius = 0.05;
static float gear_ratio = 2.720;

static void calculate_rps(uint32_t rotation_count);

//gpio_s encoder_sensor = {GPIO__PORT_0, 6};
//static const uint32_t encoder_pin_mask = (1 << 6);
//static void encoder_interrupt_handler(void);

// Public Functions
//void motor_encoder__init(void) {
//
//  LPC_GPIOINT->IO0IntEnR |= encoder_pin_mask;
//  gpio__construct_as_input(GPIO__PORT_0, 6);
//  lpc_peripheral__enable_interrupt(LPC_PERIPHERAL__GPIO, encoder_interrupt_handler, NULL);
//}

void motor_encoder__periodic_handler(void) {
  observed_rotation_count = rotation_counter;
  calculate_rps(observed_rotation_count);
  rotation_counter = 0;
}

float motor_encoder__get_speed() {
  float current_speed;
  current_speed = (float)((rotation_to_convert * 2 * PI * wheel_radius) / gear_ratio);
  return current_speed;
}

uint32_t motor_encoder__get_rps(void) { return rps; }

// Private Functions
//static void encoder_interrupt_handler(void) {
//  if ((LPC_GPIOINT->IO0IntStatR) & encoder_pin_mask) {
//    rotation_counter++;
//    LPC_GPIOINT->IO0IntClr = encoder_pin_mask;
//  }
//}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
  rotation_counter++;
}

static void calculate_rps(uint32_t rotation_count) {
  rps = rotation_count;
  rotation_to_convert = rps;
}
