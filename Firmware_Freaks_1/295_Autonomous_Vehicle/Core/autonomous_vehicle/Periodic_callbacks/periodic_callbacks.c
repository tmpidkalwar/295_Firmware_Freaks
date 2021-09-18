#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "periodic_callbacks.h"
#include "../Sensor_node/sensor__config.h"
#include "../Sensor_node/sensor__val_conv.h"
#include "../Motor_node/motor_esc.h"

#include "stm32f4xx_hal.h"


static uint16_t current_adc_value1;
static uint16_t current_adc_value2;
static uint16_t current_adc_value3;
static uint16_t current_adc_value4;

UART_HandleTypeDef huart1;

uint32_t read_adc_value = 0;

uint32_t read_array[50] = {0};
/******************************************************************************
 * Your board will reset if the periodic function does not return within its deadline
 * For 1Hz, the function must return within 1000ms
 * For 1000Hz, the function must return within 1ms
 */
void periodic_callbacks__initialize(void) {
  // This method is invoked once when the periodic tasks are created
	motor_esc__control_speed(5);
	motor_esc__steer_handler(43);
	sens_val_conv__buffer_init();
}

bool flag = true;
void periodic_callbacks__1Hz(uint32_t callback_count) {
	//sensor_node__trigger_Front_ultrasonic();
//	if(flag){
//	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
//	flag = false;
//	}else {
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//	flag = true;
//	}
}

void periodic_callbacks__10Hz(uint32_t callback_count) {

}

char buff[100] = "";
void periodic_callbacks__100Hz(uint32_t callback_count) {
	  volatile static int chance = 0;
	  uint16_t current_adc_value_front = 0, current_adc_value_left = 0, current_adc_value_right = 0;
	  uint16_t SENSOR_SONARS_left = 0, SENSOR_SONARS_middle = 0, SENSOR_SONARS_right = 0;
	  if (callback_count % 5 == 0) {
	    if (chance == 0) {

	      sensor_node__trigger_Front_ultrasonic();
	    } else if (chance == 1) {
//
	      sensor_node__trigger_Left_ultrasonic();
	      sensor_node__trigger_Right_ultrasonic();
	    }
	    SENSOR_SONARS_left = sens_val_conv__get_filtered_val_in_cm(LEFT_SENSOR);
	    SENSOR_SONARS_middle = sens_val_conv__get_filtered_val_in_cm(FRONT_SENSOR);
	    SENSOR_SONARS_right = sens_val_conv__get_filtered_val_in_cm(RIGHT_SENSOR);
	    sprintf(buff, "front ADC value %d   left ADC value %d   Right ADC value %d\r\n", SENSOR_SONARS_middle, SENSOR_SONARS_left, SENSOR_SONARS_right);
	    HAL_UART_Transmit(&huart1, (uint8_t *)buff, strlen(buff), HAL_MAX_DELAY);
	  } else if (callback_count % 5 == 4) {

	    if (chance == 0) {
	    	current_adc_value_front = sens_val_conv__get_sens_val_in_cm(FRONT_SENSOR);
	      sens_val_conv__update_buffer(FRONT_SENSOR, current_adc_value_front);
//	      sens_val_conv__set_front_sens(current_adc_value);
	      chance++;
	      //read_array[chance++] = current_adc_value;
	     //sprintf(buff, "front ADC value %d   ", current_adc_value_front);
	    } else if (chance == 1) {
	      current_adc_value_left = sens_val_conv__get_sens_val_in_cm(LEFT_SENSOR);
	      sens_val_conv__update_buffer(LEFT_SENSOR, current_adc_value_left);
	      //sens_val_conv__set_left_sens(current_adc_value);
	      current_adc_value_right = sens_val_conv__get_sens_val_in_cm(RIGHT_SENSOR);
	      sens_val_conv__update_buffer(RIGHT_SENSOR, current_adc_value_right);
//	      sens_val_conv__set_right_sens(current_adc_value);
	     // read_array[chance++] = current_adc_value;

	     // sprintf(buff, "Right ADC value %d\r\n", current_adc_value_right);
	      chance = 0;
	    }
//	    current_adc_value4 = sens_val_conv__get_sens_val_in_cm(REAR_SENSOR);
//	    sens_val_conv__update_buffer(REAR_SENSOR, current_adc_value4);
//	    sens_val_conv__set_rear_sens(current_adc_value4);
	      //current_adc_value++;

	  }
}

/**
 * @warning
 * This is a very fast 1ms task and care must be taken to use this
 * This may be disabled based on intialization of periodic_scheduler__initialize()
 */
void periodic_callbacks__1000Hz(uint32_t callback_count) {}
