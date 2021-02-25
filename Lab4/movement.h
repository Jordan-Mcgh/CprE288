/*
 * movement.h
 *
 *  Created on: Feb 11, 2021
 *      Author: jatorres
 */
#include "open_interface.h"
#ifndef MOVEMENT_H_
#define MOVEMENT_H_





#endif /* MOVEMENT_H_ */

static int threshold = 70; // How close move forward has to be in mm

double move_forward (oi_t *sensor_data, double distance_mm);
double move_backwards(oi_t *sensor_data, double distance_mm);
double turn_right(oi_t *sensor, double degrees);
double turn_left(oi_t *sensor, double degrees);
