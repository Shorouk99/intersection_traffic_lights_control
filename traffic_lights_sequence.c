/* ****************************************************************************
File Name: traffic_lights_sequence.c
Description: Traffic files sequence controller
***************************************************************************** */

#include "traffic_lights_sequence.h"
#include "gptm_timer_interrupts.h"
#include "GPIOF_interrupt.h"


/* ****************************************************************************
Variables Declaration and / or Definition
***************************************************************************** */
char cars_traffic_light_state = RED_SWITCH;
char cars_movement_state = NORTH_SOUTH;
unsigned long last_trigger = 0;
unsigned extern volatile long now; 


/* ****************************************************************************
Functions Implementaion
***************************************************************************** */

//Initialize LED and buttons pins and set their direction to output and input
//respectively
void ports_init() {
  DIO_Init('D',PORTD_PINS, PORTD_PINS);
  DIO_Init('E', PORTE_PINS, PORTE_PINS);
  DIO_Init('F', PORTF_PINS,0x0);
}

//Output event allowing cars in north_south direction while stopping pedstrians
//in this direction and cars in east_west direction:
//north_south green cars LED: ON, north_south red pedestrian LED: ON
//east_west red cars LED: ON, east_west green pedesrian LED: ON
void cars_north_south_go() {
  DIO_WritePort('E', T1_GREEN_LED | PT1_RED_LED);
  DIO_WritePort('D', T2_RED_LED | PT2_GREEN_LED);
}

//Output event allowing cars in east_west direction while stopping pedstrians
//in this direction and cars in north_south direction:
//north_south red cars LED: ON, north_south green pedestrian LED: ON
//east_west green cars LED: ON, east_west red pedesrian LED: ON
void cars_east_west_go() {
  DIO_WritePort('D', T2_GREEN_LED | PT2_RED_LED);
  DIO_WritePort('E', T1_RED_LED | PT1_GREEN_LED);
}

//Output event slowing cars in north_south direction 
//north_south yellow cars LED: ON, north_south red pedestrian LED: ON
void cars_north_south_slow() {
  DIO_WritePort('E', T1_YELLOW_LED | PT1_RED_LED);
}

//Output event slowing cars in east_west direction 
//east_west yellow cars LED: ON, east_west red pedestrian LED: ON
void cars_east_west_slow() {
  DIO_WritePort('D', T2_YELLOW_LED | PT2_RED_LED);
}

//Output event stopping cars in north_south direction 
//north_south red cars LED: ON, north_south green pedestrian LED: ON
void cars_north_south_stop() {
  DIO_WritePort('E',T1_RED_LED | PT1_GREEN_LED);
}

//Output event stopping cars in east_west direction 
//east_west red cars LED: ON, east_west green pedestrian LED: ON
void cars_east_west_stop() {
  DIO_WritePort('D', T2_RED_LED | PT2_GREEN_LED);
}

//Output event corresponding to pedestrian pressing north_south button
//north_south red cars LED: ON, north_south green pedestrian LED: ON
void ped_north_south_go() {
  DIO_WritePort('E',T1_RED_LED | PT1_GREEN_LED);
}

//Output event corresponding to pedestrian pressing east_west button
//east_west red cars LED: ON, east_west green pedestrian LED: ON
void ped_east_west_go() {
  DIO_WritePort('D', T2_RED_LED | PT2_GREEN_LED);
}

//Timer0 handler which is responsible for normal traffic lights sequence timing
//Finite state machine is applied using the if-statements method for better
//readability and less RAM usage than look-up table method
void Timer0_Handler() {
  
  if (cars_movement_state == NORTH_SOUTH) {
    if (cars_traffic_light_state == RED_SWITCH) {
      cars_north_south_go();
      cars_traffic_light_state = GREEN;
      timer0_delay(5000);
    }
    
    else if (cars_traffic_light_state == GREEN) {      
      cars_north_south_slow();
      cars_traffic_light_state = YELLOW;
      timer0_delay(2000);
    }
    
    else if (cars_traffic_light_state == YELLOW) {
      cars_north_south_stop();
      cars_traffic_light_state = RED;
      timer0_delay(1000);
    }

    else if (cars_traffic_light_state == RED) {
      cars_traffic_light_state = RED_SWITCH;
      cars_movement_state = EAST_WEST;
    }
  }
  
  if (cars_movement_state == EAST_WEST) {
    if (cars_traffic_light_state == RED_SWITCH) {
      cars_east_west_go();
      cars_traffic_light_state = GREEN;
      timer0_delay(5000);
    }
    
    else if (cars_traffic_light_state == GREEN) {
      cars_east_west_slow();
      cars_traffic_light_state = YELLOW;
      timer0_delay(2000);
    }
    
    else if (cars_traffic_light_state == YELLOW) {
      cars_east_west_stop();
      cars_traffic_light_state = RED;
      timer0_delay(1000);
    }

    else if (cars_traffic_light_state == RED) {
      cars_traffic_light_state = RED_SWITCH;
      cars_movement_state = NORTH_SOUTH;
    }
  }
  
  clear_timer0_interrupt_flag();
}

//Timer1 handler which is responsible for returning traffic lights sequence to 
//normal after pedestrians interrupt
void Timer1_Handler() {
  timer0_enable();
  if (cars_movement_state == NORTH_SOUTH) {
    cars_north_south_go();
  }
  else if (cars_movement_state == EAST_WEST) {
    cars_east_west_go();
  }
  timer1_disable();
  last_trigger = now; //saving last trigger time to ensure next stop will be after 1 sec at least
  clear_timer1_interrupt_flag();
}

//Extrnal interrupts handler which is responsible for timing traffic lights during
//pedestrian interval
void GPIOF_Handler() {
  
  //checking a traffic light is green to be stopped and if last stop is at 
  //least 1 sec ago
  if ((cars_traffic_light_state == GREEN) && (now - last_trigger > 1000)) {
    
    //Disable normal sequence timer to pause it
    timer0_disable();
    
    //Managing cases of one button pressed
    if ((PORTF_MASK&0x10) && (cars_movement_state == NORTH_SOUTH)) {
      ped_north_south_go();
      timer1_reset_enable_2s();
    }
    
    else if ((PORTF_MASK&0x1) && cars_movement_state == EAST_WEST) {
      ped_east_west_go();
      timer1_reset_enable_2s();
    }
    
    //Managing cases of two buttons pressed
    else if ((PORTF_MASK&0x11) && cars_movement_state == NORTH_SOUTH) {
      ped_north_south_go();
      timer1_reset_enable_5s();
    }
    
    else if ((PORTF_MASK&0x11) && cars_movement_state == EAST_WEST) {
      ped_east_west_go();
      timer1_reset_enable_5s();
    }

  }
  GPIOF_clear_interrupt_flag();
}