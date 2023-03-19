/* ****************************************************************************
File Name: gptm_timer_interrupts.c
Description: GPTM deriver and abstraction layer
***************************************************************************** */
#include "tm4c123gh6pm.h"
#include "gptm_timer_interrupts.h"

/* ****************************************************************************
Variables Declaration and / or Definition
***************************************************************************** */
unsigned volatile long now = 0;

/* ****************************************************************************
Functions Implementaion
***************************************************************************** */

//Initialize timer0
void timer0_init() {
  SYSCTL_RCGCTIMER_R |= 0x1; //enable clock to timer A
  TIMER0_CTL_R = 0x0; //disable timer0
  TIMER0_CFG_R = 0x0; //configure to 32-bit timer
  TIMER0_TAMR_R = 0x2; //set mode to periodic timer
  TIMER0_TAILR_R = 1; //reload value
  TIMER0_ICR_R = 0x1; //clear timeout interrupt flag
  TIMER0_IMR_R |= 0X1; //enable timer timeout flag
  NVIC_PRI4_R |= (1<<30)|(1<<29); //set priority
  NVIC_EN0_R |= (1 << 19); //enable interrupt in NVIC
  TIMER0_CTL_R |= 0X1; //enable timer0
  
}

//Clear timer interrupt flag
void clear_timer0_interrupt_flag() {
  TIMER0_ICR_R |= 0x1;
}

//Set timer0 reload value to achieve a required delay in milliseconds
void timer0_delay(unsigned int delay) {
  //delay is in milliseconds
  TIMER0_CTL_R = 0x0; //disable timer0
  TIMER0_TAILR_R = (delay*16000)-1;
  TIMER0_CTL_R = 0x1; //enable timer0
}

//Disable timer0
void timer0_disable() {
  TIMER0_CTL_R = 0x0;
}

//Enable timer0
void timer0_enable() {
  TIMER0_CTL_R |= 0x1; //enable timer
}

//Initialize timer1
void timer1_init() {
  SYSCTL_RCGCTIMER_R |= 1<<1; //enable clock to timer A
  TIMER1_CTL_R = 0x0; //disable
  TIMER1_CFG_R = 0x0; //32-bit timer
  TIMER1_TAMR_R = 0x2; //periodic timer
  TIMER1_TAILR_R = TIMER1_RL; //reload value
  TIMER1_ICR_R = 0x1; //clear timeout interrupt flag
  TIMER1_IMR_R |= 0X1; //enable timer timeout flag
  NVIC_PRI5_R |= (1<<15) | (1<<13);// 5th priority
  NVIC_EN0_R |= (1<<21);
}

//Clear timer1 interrupt flag
void clear_timer1_interrupt_flag() {
  TIMER1_ICR_R = 0x1; //clear timeout interrupt flag
}

//Reset timer1 counter, set reload value to 2 seconds and enable 
void timer1_reset_enable_2s() {
  TIMER1_TAILR_R = TIMER1_RL; //reload value
  TIMER1_CTL_R |= 0X1; //enable timer
  TIMER1_TAV_R = TIMER1_RL; //reset counter to 0
}

//Reset timer1 counter, set reload value to 5 seconds and enable 
void timer1_reset_enable_5s() {
  TIMER1_TAILR_R = TIMER1_RL_5S; //reload value
  TIMER1_CTL_R |= 0X1; //enable timer
  TIMER1_TAV_R = TIMER1_RL_5S; //reset counter to 0
}

//Disable timer1
void timer1_disable() {
  TIMER1_CTL_R = 0x0; //disable
}

//Initialize timer2
void timer2_init() {
  SYSCTL_RCGCTIMER_R |= 1<<2; //enable clock to timer A
  TIMER2_CTL_R = 0x0; //disable
  TIMER2_CFG_R = 0x0; //16-bit timer
  TIMER2_TAMR_R = 0x2; //periodic timer
  TIMER2_TAILR_R = TIMER2_RL; //reload value
  TIMER2_ICR_R = 0x1; //clear timeout interrupt flag
  TIMER2_IMR_R |= 0X1; //enable timer timeout flag
  NVIC_PRI5_R |= (1<<30) | (1<<29);// 3th priority
  NVIC_EN0_R |= (1<<23);
  TIMER2_CTL_R |= 0x1; //enable timer
}

//Timer2 ISR which increments now variable every 1millisecond to indicate time
//from system restarting
void millis() {
  now++;
  TIMER2_ICR_R |= 0x1;
  
}