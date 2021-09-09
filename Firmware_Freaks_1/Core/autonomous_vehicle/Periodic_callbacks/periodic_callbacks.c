#include <stdio.h>

#include "periodic_callbacks.h"


//static uint16_t current_adc_value1;
//static uint16_t current_adc_value2;
//static uint16_t current_adc_value3;
//static uint16_t current_adc_value4;

/******************************************************************************
 * Your board will reset if the periodic function does not return within its deadline
 * For 1Hz, the function must return within 1000ms
 * For 1000Hz, the function must return within 1ms
 */
void periodic_callbacks__initialize(void) {
  // This method is invoked once when the periodic tasks are created

}

void periodic_callbacks__1Hz(uint32_t callback_count) {  }

void periodic_callbacks__10Hz(uint32_t callback_count) { }

void periodic_callbacks__100Hz(uint32_t callback_count) { }

/**
 * @warning
 * This is a very fast 1ms task and care must be taken to use this
 * This may be disabled based on intialization of periodic_scheduler__initialize()
 */
void periodic_callbacks__1000Hz(uint32_t callback_count) {}
