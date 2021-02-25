

/**
 * main.c
 */
#include "cyBot_FindObjects.h"
#include "cyBot_uart.h"
#include "movement.h"

int main(void)
{

    cyBot_uart_init();

    cyBot_Object_t objects[20];
    int k;
    for(k = 0; k < (sizeof(objects) / sizeof(cyBot_Object_t)); k++){
        cyBot_Object_t clear;
        clear.angle = 0;
        clear.distance = 0;
        clear.width = 0;
        objects[k] = clear;
    }
    cyBot_FindObjects(objects, 20);

    char* initial = "Object#\tAngle\tDistance\tWidth\n";
    int j;
    for(j = 0; j < strlen(initial); j++){
        cyBot_sendByte(initial[j]);
    }

    int i;
    for(i = 0; i < (sizeof(objects) / sizeof(cyBot_Object_t)); i++){
        if(objects[i].distance == 0){
            continue;
        }
        char data[50];

        sprintf(data, "%d\t\t%d\t%f\t%f\n", i, objects[i].angle, objects[i].distance, objects[i].width);
        for(j = 0; j < strlen(data); j++){
            cyBot_sendByte(data[j]);
        }
    }
    float smallest = objects[0].width;
    int smallIdx = 0;
    for(i = 0; i < (sizeof(objects) / sizeof(cyBot_Object_t)); i++){
        if(objects[i].distance == 0){
            continue;
        }
        smallest = smallest - objects[i].width < 0 ? smallest : objects[i].width;
        smallIdx = smallest - objects[i].width < 0 ? smallIdx : i;
    }
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()
    if(objects[smallIdx].angle < 90){
        turn_left(sensor_data, 90 - objects[smallIdx].angle);
    }
    else{
        turn_right(sensor_data, objects[smallIdx].angle - 90);
    }
    move_forward(sensor_data, (double) objects[smallIdx].distance * 10);
    oi_free(sensor_data);
    return 0;
}
