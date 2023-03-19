/* ****************************************************************************
File Name: gptm_timer_interrupts.h
Description: Header file for GPTM deriver
***************************************************************************** */

#ifndef __GPTM_TIMER_INTERRUPTS_HEADR__
#define __GPTM_TIMER_INTERRUPTS_HEADR__

/* ****************************************************************************
Constants Macro Definitions
***************************************************************************** */
#define PORTF_MASK      GPIO_PORTF_MIS_R    
#define TIMER1_RL       ((2*16000000)-1)
#define TIMER1_RL_5S    ((5*16000000)-1)
#define TIMER2_RL       (16000-1)

/* ****************************************************************************
Functions Prototypes
***************************************************************************** */
void timer0_init();
void timer0_enable();
void timer0_disable();
void clear_timer0_interrupt_flag();
void timer0_delay(unsigned int delay);
void timer1_init();
void timer1_enable();
void timer1_disable();
void clear_timer1_interrupt_flag();
void timer1_reset_enable_2s();
void timer1_reset_enable_5s();
void timer2_init();
void millis();

#endif