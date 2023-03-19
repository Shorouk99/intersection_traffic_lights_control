#include "tm4c123gh6pm.h"
#include "Systick.h"

void SystickDisable() //disables timer and interrupt
{
  NVIC_ST_CTRL_R = 0x0; 
}


void SystickEnable() //enables timer only and uses 16MHz clock
{
  NVIC_ST_CTRL_R = 0x5;
}

void Systick_init_ms() {

  NVIC_ST_CTRL_R = 0X0;
  NVIC_ST_RELOAD_R = 15999; //Reload value to count 1 millisecond 
  NVIC_ST_CURRENT_R = 0;
  NVIC_ST_CTRL_R = 0X5;
}

void Systick_delay_ms(int n_ms){
  
  Systick_init_ms(); //
  for (int i = 0; i < n_ms; i++) {
    while ((NVIC_ST_CTRL_R&0x10000) == 0) {}
  }
  
}



