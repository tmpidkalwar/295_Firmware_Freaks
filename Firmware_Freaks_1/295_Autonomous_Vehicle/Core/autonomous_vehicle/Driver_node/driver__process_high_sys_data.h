#pragma once

//#include "project.h"
#define GET_MIN(x, y) ((x) < (y) ? (x) : (y))
#define DESTINATION_THRESHOLD_DISTANCE 2 // meters
#define MAX_ALLOWED_TURN_ANGLE 45        // degrees
#define MAX_SPEED_WHILE_TURNING 12.5     // kmph
#define MIN_SPEED_WHILE_TURNING 2.5      // kmph
#define MIN_REVERSE_SPEED_GEO (-2.5)     // kmph
#define MIN_REVERSE_ANGLE (15)           // degrees
#define MIN_FORWARD_SPEED_GEO (2.5)      // kmph
#define MIN_FORWARD_ANGLE 0              // degrees
#define MIA_GEO_LED_PORT_NUM 2
#define MIA_GEO_LED_NUM 4
#define MIA_SENSOR_LED_PORT_NUM 2
#define MIA_SENSOR_LED_NUM 1
#define DESTINATION_REACHED_LED_PORT_NUM 1
#define DESTINATION_REACHED_LED_NUM1 29
#define DESTINATION_REACHED_LED_NUM2 23

typedef struct {
	uint16_t HEADING; // Angle referenced with current heading of vehicle to turn
	float DISTANCE; // Distance of the obstacle in the current direction
}high_sys_data;

typedef struct {
	float MOTOR_speed;
	uint8_t MOTOR_direction;
}driver_to_motor_data;

void driver_process_geo_data__process_input(high_sys_data *high_sys_data);
//dbc_DRIVER_TO_MOTOR_s driver_process_geo_data__get_motor_data(void);
bool destination_reached();
// dbc_DRIVER_BROADCAST_s driver_get_broadcast_data(void);
