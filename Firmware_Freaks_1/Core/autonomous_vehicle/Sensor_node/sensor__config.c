#include "sensor__config.h"

#include "stm32f7xx_hal.h"


/****************************************************************************************
 **************************** S T A T I C   P A R A M S *********************************
 ****************************************************************************************/

ADC_HandleTypeDef hadc1; //FRONT_SENSOR
ADC_HandleTypeDef hadc2; //LEFT_SENSOR
ADC_HandleTypeDef hadc3; //RIGHT_SENSOR

TIM_HandleTypeDef htim1; //Using TIM1 for microsecond delay

static const uint8_t trigger_delay_time = 30;


/****************************************************************************************
 **************************** P U B L I C    F U N C T I O N S **************************
 ****************************************************************************************/

void delay__us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // wait for the counter to reach the us input in the parameter
}


void sensor_node__trigger_Front_ultrasonic(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
	delay__us(trigger_delay_time);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
}

void sensor_node__trigger_Left_ultrasonic(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	delay__us(trigger_delay_time);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
}

void sensor_node__trigger_Right_ultrasonic(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	delay__us(trigger_delay_time);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
}

//void sensor_node__trigger_Rear_ultrasonic(void) {
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
//	delay__us(trigger_delay_time);
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
//}

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
