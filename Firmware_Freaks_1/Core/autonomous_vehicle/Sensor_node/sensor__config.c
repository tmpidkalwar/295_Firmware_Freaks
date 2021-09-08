//#include "gpio.h"

#include "sensor__config.h"
#include "stm32f7xx_hal_adc.h"
#include "stm32f7xx_hal_tim.h"

/****************************************************************************************
 **************************** S T A T I C   P A R A M S *********************************
 ****************************************************************************************/

//static uint8_t rear_sensor_adc_channel = ADC__CHANNEL_3;
//static uint8_t left_sensor_adc_channel = ADC__CHANNEL_4;
//static uint8_t right_sensor_adc_channel = ADC__CHANNEL_5;
//static uint8_t front_sensor_adc_channel = ADC__CHANNEL_2;

ADC_HandleTypeDef hadc1; //FRONT
ADC_HandleTypeDef hadc2; //LEFT
ADC_HandleTypeDef hadc3; //RIGHT

TIM_HandleTypeDef htim1; //Using TIM1 for microsecond delay

static const uint8_t trigger_delay_time = 30;
static gpio_s trigger_left, trigger_front, trigger_right, trigger_rear;


/****************************************************************************************
 **************************** P U B L I C    F U N C T I O N S **************************
 ****************************************************************************************/

void delay__us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // wait for the counter to reach the us input in the parameter
}

void sensor_node__init_trigger_pins_as_gpio(void) {
//  trigger_left = gpio__construct_as_output(0, 6);
//  trigger_front = gpio__construct_as_output(0, 7);
//  trigger_right = gpio__construct_as_output(0, 8);
  // trigger_rear = gpio__construct_as_output(0, 9);
}

void sensor_node__trigger_Left_ultrasonic(void) {
//  gpio__set(trigger_left);
  delay__us(trigger_delay_time);
//  gpio__reset(trigger_left);
}

void sensor_node__trigger_Front_ultrasonic(void) {
//  gpio__set(trigger_front);
  delay__us(trigger_delay_time);
//  gpio__reset(trigger_front);
}

void sensor_node__trigger_Right_ultrasonic(void) {
//  gpio__set(trigger_right);
  delay__us(trigger_delay_time);
//  gpio__reset(trigger_right);
}

void sensor_node__trigger_Rear_ultrasonic(void) {
//  gpio__set(trigger_rear);
  delay__us(trigger_delay_time);
//  gpio__reset(trigger_rear);
}

uint32_t sensor_config__read_sens_raw_value(sensor_index current_sensor) {
  switch (current_sensor) {
  case FRONT_SENSOR:
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  return HAL_ADC_GetValue(&hadc1);

  case LEFT_SENSOR:
	  HAL_ADC_Start(&hadc2);
	  HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
	  return HAL_ADC_GetValue(&hadc2);

  case RIGHT_SENSOR:
	  HAL_ADC_Start(&hadc3);
	  HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
	  return HAL_ADC_GetValue(&hadc3);

//  case REAR_SENSOR:
//    return adc__get_adc_value(rear_sensor_adc_channel);

  default:
    return -1;
  }
}
