/* ****************************************************************************
File Name: GPIO_interrupt.c
Description: GPIO port F pins 0 and 4 interrupt driver and abstraction layer
***************************************************************************** */

#include "tm4c123gh6pm.h"
#define PORTF_PINS              0x11;

/* ****************************************************************************
Functions Implementaion
***************************************************************************** */

//Attach external interrupts to pins 0 and 4 of port F
void GPIOF_interrupt_init() {
  GPIO_PORTF_IS_R &= ~0x11; //set to be edge sensing
  GPIO_PORTF_IBE_R = ~0x11; //trigger to be controlled by IEV_R (not both edges)
  GPIO_PORTF_IEV_R &= 0x11; //Falling edge trigger
  GPIO_PORTF_ICR_R |= 0x11; //Clearing interrupt flag
  GPIO_PORTF_IM_R |= 0x11; //Enabling interrupts to pins 0 and 4
  NVIC_PRI7_R |= (1<<23); //setting priority to 4th
  NVIC_EN0_R |= 0x40000000; //enabling interrupt to GPIO port F in NVIC
}

//Clear interrupt flag for pins 0 and 4
void GPIOF_clear_interrupt_flag() {
  GPIO_PORTF_ICR_R |= PORTF_PINS;
}

