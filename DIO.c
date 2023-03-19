/* ****************************************************************************
File Name: DIO.c
Description: Ports driver and abstraction layer
***************************************************************************** */

#include "DIO.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"

//*****************************************************************************
//Function Name: DIO_Init
//
//Function Describtion: Initializes the given pins on the given port and assigns
//the given direction to these pins. The corresponding clock bit is set to enable
//the port and other rgistrs needed to unlock the port and the spcefied pins are 
//Pull_up resistors are enabled for input pins.
//
//Function Arguments:
//port: char value from the set {'A', 'B', 'C', 'D', 'E', 'F'}  correseponding
//to Tiva_C ports.
//pin: char value of hexadiciaml or binary numbers corresponding to the desired
//pins.
//direction: char value of hexadiciaml or binary numbers corresponding to the 
//desired direction of chosn pins.
//*****************************************************************************
void DIO_Init(char port , char pin , char direction) {
  switch (port) {
  case 'A':
  SYSCTL_RCGCGPIO_R |= 0x1;
  while((SYSCTL_PRGPIO_R & 0x1)== 0){};
  GPIO_PORTA_LOCK_R = 0x4C4F434B;
  GPIO_PORTA_CR_R |= pin;
  GPIO_PORTA_PUR_R |= (~direction);
  GPIO_PORTA_DEN_R |= pin;
  GPIO_PORTA_DIR_R &= direction;
  GPIO_PORTA_DIR_R |= direction;
  break;
  
  case 'B':
  SYSCTL_RCGCGPIO_R |= 0x2;
  while((SYSCTL_PRGPIO_R & 0x2)== 0){};
  GPIO_PORTB_LOCK_R = 0x4C4F434B;
  GPIO_PORTB_CR_R |= pin;
  GPIO_PORTB_PUR_R |= (~direction);
  GPIO_PORTB_DEN_R |= pin;
  GPIO_PORTB_DIR_R &= direction;
  GPIO_PORTB_DIR_R |= direction;
  break;
  
  case 'C':
  SYSCTL_RCGCGPIO_R |= 0x4;
  while((SYSCTL_PRGPIO_R & 0x4)== 0){};
  GPIO_PORTC_LOCK_R = 0x4C4F434B;
  GPIO_PORTC_CR_R |= pin;
  GPIO_PORTC_PUR_R |= (~direction);
  GPIO_PORTC_DEN_R |= pin;
  GPIO_PORTC_DIR_R &= direction;
  GPIO_PORTC_DIR_R |= direction;
  break;
  
  case 'D':
  SYSCTL_RCGCGPIO_R |= 0x8;
  while((SYSCTL_PRGPIO_R & 0x8)== 0){};
  GPIO_PORTD_LOCK_R = 0x4C4F434B;
  GPIO_PORTD_CR_R |= pin;
  GPIO_PORTD_PUR_R |= (~direction);
  GPIO_PORTD_DEN_R |= pin;
  GPIO_PORTD_DIR_R &= direction;
  GPIO_PORTD_DIR_R |= direction;
  break;
  
  case 'E':
  SYSCTL_RCGCGPIO_R |= 0x10;
  while((SYSCTL_PRGPIO_R & 0X10)== 0){};
  GPIO_PORTE_LOCK_R = 0x4C4F434B;
  GPIO_PORTE_CR_R |= pin;
  GPIO_PORTE_PUR_R |= (~direction);
  GPIO_PORTE_DEN_R |= pin;
  GPIO_PORTE_DIR_R &= direction;
  GPIO_PORTE_DIR_R |= direction;
  break;
  
  case 'F':
  SYSCTL_RCGCGPIO_R |= 0x20;
  while((SYSCTL_PRGPIO_R & 0x20)== 0){};
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_CR_R |= pin;
  GPIO_PORTF_PUR_R |= (~0xE);
  GPIO_PORTF_DEN_R |= pin;
  GPIO_PORTF_DIR_R &= direction;
  GPIO_PORTF_DIR_R |= direction;
  break;
  }
}

//*****************************************************************************
//Function Name: DIO_WritePin
//
//Function Describtion: Sets or clears the specified pin on the specified port.
//
//Function Arguments:
//port: Number of port 0-5. Port IDs can be used from macros. 
//pin: Number of pin 0-7. Pin IDs can be used from macros.
//value: 1 (defined as LOGIC_HIGH) to set the pin, or 0 to clear the pin 
//*****************************************************************************
void DIO_WritePin (char port , char pin , char value) {

  if((pin >= NUM_OF_PINS_PER_PORT) || (port >= NUM_OF_PORTS)) {}
  
  else {
    
    switch(port) {
    case PORTA_ID:
      if(value == LOGIC_HIGH)
      {
        Set_Bit(GPIO_PORTA_DATA_R,pin);
      }
      
      else
      {
        Clear_Bit(GPIO_PORTA_DATA_R,pin);
      }
      break;
      
    case PORTB_ID:
      if(value == LOGIC_HIGH)
      {
        Set_Bit(GPIO_PORTB_DATA_R,pin);
      }
      
      else
      {
        Clear_Bit(GPIO_PORTB_DATA_R,pin);
      }
      break;
      
    case PORTC_ID:
      if(value == LOGIC_HIGH)
      {
        Set_Bit(GPIO_PORTC_DATA_R,pin);
      }
      else
      {
        Clear_Bit(GPIO_PORTC_DATA_R,pin);
      }
      break;
      
    case PORTD_ID:
      if(value == LOGIC_HIGH)
      {
        Set_Bit(GPIO_PORTD_DATA_R,pin);
      }
      else
      {
        Clear_Bit(GPIO_PORTD_DATA_R,pin);
      }
      break;
      
    case PORTE_ID:
      if(value == LOGIC_HIGH)
      {
        Set_Bit(GPIO_PORTE_DATA_R,pin);
      }
      else
      {
        Clear_Bit(GPIO_PORTE_DATA_R,pin);
      }
      break;
      
    case PORTF_ID:
      if(value == LOGIC_HIGH)
      {
        Set_Bit(GPIO_PORTF_DATA_R,pin);
      }
      else
      {
        Clear_Bit(GPIO_PORTF_DATA_R,pin);
      }
      break;
    }
  }
}

//*****************************************************************************
//Function Name: DIO_WritePort
//
//Function Describtion: Sets and Clears several pins from the same port 
//simultaneously.
//
//Function Arguments:
//port: char value from the set {'A', 'B', 'C', 'D', 'E', 'F'}  correseponding
//to Tiva_C ports.
//value: char value of hexadiciaml or binary numbers corresponding to the desired
//value of each chosen pin.
//*****************************************************************************
void DIO_WritePort (char port , char value) {
  switch (port) {
  
  case 'A':
    GPIO_PORTA_DATA_R &= value;
    GPIO_PORTA_DATA_R |= value;
    break;
    
  case 'B':
    GPIO_PORTB_DATA_R &= value;
    GPIO_PORTB_DATA_R |= value;
    break;
    
  case 'C':
    GPIO_PORTC_DATA_R &= value;
    GPIO_PORTC_DATA_R |= value;
    break; 
    
  case 'D':
    GPIO_PORTD_DATA_R &= value;
    GPIO_PORTD_DATA_R |= value;
    break;
    
  case 'E':
    GPIO_PORTE_DATA_R &= value;
    GPIO_PORTE_DATA_R |= value;
    break;
    
  case 'F':
    GPIO_PORTF_DATA_R &= value;
    GPIO_PORTF_DATA_R |= value;
    break;
  }
}

//*****************************************************************************
//Function Name: DIO_ReadPin
//
//Function Describtion: Determines if a specified pin on a specified port is
//having a value of 0 or 1
//
//Function Arguments:
//port: char value from the set {'A', 'B', 'C', 'D', 'E', 'F'}  correseponding
//to Tiva_C ports. 
//pin: Number of pin 0-7. Pin IDs can be used from macros.
//
//Return Value:
//0 or 1 (value stored in the pin's bit)
//*****************************************************************************
char DIO_ReadPin (char port, char pin) {
  switch (port) {
  case 'A':
    return (Get_Bit(GPIO_PORTA_DATA_R,pin));
    break;
    
  case 'B':
    return (Get_Bit(GPIO_PORTB_DATA_R,pin));
    break;
    
  case 'C':
    return (Get_Bit(GPIO_PORTC_DATA_R,pin));
    break;
    
  case 'D':
    return (Get_Bit(GPIO_PORTD_DATA_R,pin));
    break;
    
  case 'E':
    return (Get_Bit(GPIO_PORTE_DATA_R,pin));
    break;
    
  case 'F':
    return (Get_Bit(GPIO_PORTF_DATA_R,pin));
    break;
    
  default:
    return 0;
    break;
  }
}

//*****************************************************************************
//Function Name: DIO_ReadPort
//
//Function Describtion: Determines the value of several pins on the same port 
//simultaneously
//
//Function Arguments:
//port: char value from the set {'A', 'B', 'C', 'D', 'E', 'F'}  correseponding
//to Tiva_C ports. 
//input_pins: char value of hexadiciaml or binary numbers corresponding to the desired
//pins.
//
//Return Value:
//char representig the value (0 or 1) of each specified pin when converted to
//hexadiciaml or binary number
//*****************************************************************************
char DIO_ReadPort (char port, char input_pins) {
  switch (port) {
  case 'A':
    return (GPIO_PORTA_DATA_R & input_pins);
    break;
    
  case 'B':
    return (GPIO_PORTB_DATA_R & input_pins);
    break;
    
  case 'C':
    return (GPIO_PORTC_DATA_R & input_pins);
    break;
    
  case 'D':
    return (GPIO_PORTD_DATA_R & input_pins);
    break;
    
  case 'E':
    return (GPIO_PORTE_DATA_R & input_pins);
    break;
    
  case 'F':
    return (GPIO_PORTF_DATA_R & input_pins);
    break;
    
  default:
    return 0x0;
    break;
  }
}
