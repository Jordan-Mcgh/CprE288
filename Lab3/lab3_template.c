/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "resetSimulation.h"
#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity,  COM1

#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
    //resetSimulationBoard();
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	cyBot_uart_init();
	            // Don't forget to initialize the cyBot UART before trying to use it
	
	// YOUR CODE HERE

	lcd_printf("");

	char strBuffer[30];
	int idx = 0;

	for (idx = 0; idx < 30; idx++){
	    strBuffer[idx] = ' ';
	}



	while(1)
	{
	  if(false){
          if(button_getButton() > 0){
              char message[17] = "Button pushed:  ";
              message[16] = (char)(button_getButton() + '0');

              int i = 0;

              for( i = 0; i < strlen(message); i++){

                  cyBot_sendByte(message[i]);
              }
              cyBot_sendByte('\n');
              //Wait until button is lifted
              while(button_getButton() > 0){}
          }

	  } else {

	      idx = 0;
	      strBuffer[idx] = (char)cyBot_getByte();

	      if(strBuffer[idx] <= 32){
	          continue;
	      }

	      while(strBuffer[idx++] >= 32){
	          strBuffer[idx] = (char)cyBot_getByte();
	          idx %= strlen(strBuffer);
	      }
	      lcd_printf(strBuffer);

	      for (idx = 0; idx < 30; idx++){
	          strBuffer[idx] = ' ';
	       }
	  }

	
	}
	
}
