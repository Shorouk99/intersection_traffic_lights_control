/* ****************************************************************************
File Name: main.c
Description: The Main function where initialization occurs and program is entered
in infinite loop
***************************************************************************** */

#include "traffic_lights_sequence.h"
#include "gptm_timer_interrupts.h"
#include "GPIOF_interrupt.h"

int main()
{
  ports_init(); //initialize output and input pins
  timer0_init(); //initialize timer0 used for cars traffic lights
  timer1_init(); //initialize timer1 used for pedestrian traffic lights
  timer2_init(); //initialize timer2 used for miilis() function that calculates elapsed time from power on
  GPIOF_interrupt_init(); //initialize switch buttons external interrupts
  
  while (1); //nothing is done here as all process are in interrupt handlers
  return 0; //added just for debugging purposes
}
