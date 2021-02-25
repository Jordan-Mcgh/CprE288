/*
 * movement.c
 *
 *  Created on: Feb 11, 2021
 *      Author: jatorres
 */
#include "movement.h"

double turn_right(oi_t *sensor, double degrees){
    // the following code could be put in function move_forward()
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(100,-100); //move forward at full speed
    while (sum < degrees-2) {
           oi_update(sensor);
           sum += sensor -> angle; // use -> notation since pointer
    }
    oi_setWheels(0,0); //stop
}
double turn_left(oi_t *sensor, double degrees){
    // the following code could be put in function move_forward()
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(-100,100); //move forward at full speed
    while (sum > -degrees+2) {
           oi_update(sensor);
           sum += sensor -> angle; // use -> notation since pointer
    }
    oi_setWheels(0,0); //stop
}
double move_forward (oi_t *sensor_data, double distance_mm) {
    // the following code could be put in function move_forward()
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(500,500); //move forward at full speed
    while (sum < distance_mm) {
           oi_update(sensor_data);
           bool withinThreshold = (distance_mm - sum) > threshold;
           if(sensor_data -> bumpLeft && withinThreshold ){

               move_backwards(sensor_data, 150);

               turn_right(sensor_data, 90);
               move_forward(sensor_data, 250);

               turn_left(sensor_data, 90);
               sum += move_forward(sensor_data, 250);

               turn_left(sensor_data, 90);
               move_forward(sensor_data, 250);

               turn_right(sensor_data, 90);
               oi_setWheels(500,500);
               sum -= 150;
           }
           if(sensor_data -> bumpRight && withinThreshold ){

               move_backwards(sensor_data, 150);

               turn_left(sensor_data, 90);
               move_forward(sensor_data, 250);

               turn_right(sensor_data, 90);
               sum += move_forward(sensor_data, 250);

               turn_right(sensor_data, 90);
               move_forward(sensor_data, 250);

               turn_left(sensor_data, 90);
               oi_setWheels(500,500);
               sum -= 150;
           }

           if(withinThreshold && (sensor_data -> bumpRight || sensor_data -> bumpLeft )){
               sum = distance_mm;
               return 0;
           } else {
               sum += sensor_data -> distance; // use -> notation since pointer
           }
    }
    return sum;
    oi_setWheels(0,0); //stop
}
double move_backwards (oi_t *sensor_data, double distance_mm) {
    // the following code could be put in function move_forward()
        double sum = 0; // distance member in oi_t struct is type double
        oi_setWheels(-500,-500); //move forward at full speed
        while (sum > -distance_mm) {
               oi_update(sensor_data);
               sum += sensor_data -> distance; // use -> notation since pointer
        }
        oi_setWheels(0,0); //stop
}

