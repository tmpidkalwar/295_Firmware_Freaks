//#include "adc.h"
//#include "delay.h"
//#include "gpio.h"
//#include "lpc40xx.h"

#include "sensor__config.h"

/****************************************************************************************
 **************************** S T A T I C   P A R A M S *********************************
 ****************************************************************************************/

static uint8_t rear_sensor_adc_channel = ADC__CHANNEL_3;
static uint8_t left_sensor_adc_channel = ADC__CHANNEL_4;
static uint8_t right_sensor_adc_channel = ADC__CHANNEL_5;
static uint8_t front_sensor_adc_channel = ADC__CHANNEL_2;

static const uint8_t trigger_delay_time = 30;
static gpio_s trigger_left, trigger_front, trigger_right, trigger_rear;

//static void rear_sens_init(void) {
//
//  // Make Port 0 Pin 26 functionality as ADC0[3]
//  gpio__construct_with_function(0, 26, GPIO__FUNCTION_1);
//
//  // Set mode and analog input bits in control register
//  LPC_IOCON->P0_26 &= ~(0b11 << 3);
//
//  // Analog mode
//  LPC_IOCON->P0_26 &= ~(1 << 7);
//}
//
//static void left_sens_init(void) {
//
//  gpio__construct_with_function(GPIO__PORT_1, 30, GPIO__FUNCTION_3);
//
//  LPC_IOCON->P1_30 &= ~(0b11 << 3);
//
//  LPC_IOCON->P1_30 &= ~(1 << 7);
//}
//
//static void right_sens_init(void) {
//
//  gpio__construct_with_function(GPIO__PORT_1, 31, GPIO__FUNCTION_3);
//
//  LPC_IOCON->P1_31 &= ~(0b11 << 3);
//
//  LPC_IOCON->P1_31 &= ~(1 << 7);
//}
//
//static void front_sens_init(void) {
//
//  // Make Port 0 Pin 25 functionality as ADC0[2]
//  gpio__construct_with_function(0, 25, GPIO__FUNCTION_1);
//
//  // Set mode and analog input bits in control register
//  LPC_IOCON->P0_25 &= ~(0b11 << 3);
//
//  // Analog mode
//  LPC_IOCON->P0_25 &= ~(1 << 7);
//}

/****************************************************************************************
 **************************** P U B L I C    F U N C T I O N S **************************
 ****************************************************************************************/
void sensor_config__ultrasonic_sensors_init() {
//  adc__initialize();
//  front_sens_init();
//  rear_sens_init();
//  left_sens_init();
//  right_sens_init();
}

void sensor_node__init_trigger_pins_as_gpio(void) {
//  trigger_left = gpio__construct_as_output(0, 6);
//  trigger_front = gpio__construct_as_output(0, 7);
//  trigger_right = gpio__construct_as_output(0, 8);
  // trigger_rear = gpio__construct_as_output(0, 9);
}

void sensor_node__trigger_Left_ultrasonic(void) {
//  gpio__set(trigger_left);
//  delay__us(trigger_delay_time);
//  gpio__reset(trigger_left);
}

void sensor_node__trigger_Front_ultrasonic(void) {
//  gpio__set(trigger_front);
//  delay__us(trigger_delay_time);
//  gpio__reset(trigger_front);
}

void sensor_node__trigger_Right_ultrasonic(void) {
//  gpio__set(trigger_right);
//  delay__us(trigger_delay_time);
//  gpio__reset(trigger_right);
}

void sensor_node__trigger_Rear_ultrasonic(void) {
//  gpio__set(trigger_rear);
//  delay__us(trigger_delay_time);
//  gpio__reset(trigger_rear);
}

uint32_t sensor_config__read_sens_raw_value(sensor_index current_sensor) {
  switch (current_sensor) {
//  case FRONT_SENSOR:
//    return adc__get_adc_value(front_sensor_adc_channel);
//
//  case LEFT_SENSOR:
//    return adc__get_adc_value(left_sensor_adc_channel);
//
//  case RIGHT_SENSOR:
//    return adc__get_adc_value(right_sensor_adc_channel);
//
//  case REAR_SENSOR:
//    return adc__get_adc_value(rear_sensor_adc_channel);

  default:
    return -1;
  }
}
