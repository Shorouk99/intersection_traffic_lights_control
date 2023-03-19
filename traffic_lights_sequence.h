/* ****************************************************************************
File Name: traffic_lights_sequence.h
Description: Header file traffic lights sequence controller
***************************************************************************** */

#ifndef __TRAFFIC_LIGHTS_SEQUENCE_HEADER__
#define __TRAFFIC_LIGHTS_SEQUENCE_HEADER__

#include "DIO.h"
#include "tm4c123gh6pm.h"

/* ****************************************************************************
Constants Macro Definitions
***************************************************************************** */
#define T1_GREEN_LED            bit3
#define T1_YELLOW_LED           bit2
#define T1_RED_LED              bit1

#define T2_GREEN_LED            bit2
#define T2_YELLOW_LED           bit1
#define T2_RED_LED              bit0

#define PT1_GREEN_LED           bit4
#define PT1_RED_LED             bit5
#define PT2_GREEN_LED           bit7
#define PT2_RED_LED             bit6

#define T1_PINS                 bit1|bit2|bit3
#define T2_PINS                 bit0|bit1|bit2
#define PT1_PINS                bit4|bit5
#define PT2_PINS                bit6|bit7

#define PORTD_PINS              (T2_PINS|PT2_PINS)
#define PORTE_PINS              (T1_PINS|PT1_PINS)
#define PORTF_PINS              bit0|bit4

#define GREEN                   0
#define YELLOW                  1
#define RED                     2
#define RED_SWITCH              3

#define NORTH_SOUTH             0
#define EAST_WEST               1

/* ****************************************************************************
Functions Prototypes
***************************************************************************** */
void ports_init();
void cars_north_south_go();
void cars_east_west_go();
void cars_north_south_slow();
void cars_east_west_slow();
void cars_north_south_stop();
void cars_east_west_stop();
void Timer0_Handler();
void Timer1_Handler();
void GPIOF_Handler();

#endif