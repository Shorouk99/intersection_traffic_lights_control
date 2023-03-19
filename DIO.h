/* ****************************************************************************
File Name: DIO.h
Description: Header file for ports driver and abstraction layer
***************************************************************************** */

#ifndef __DIO_HEADER__
#define __DIO_HEADER__

#define NUM_OF_PORTS           6
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3
#define PORTE_ID               4
#define PORTF_ID               5

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

#define bit0                   1
#define bit1                   (1 << 1)
#define bit2                   (1 << 2)
#define bit3                   (1 << 3)
#define bit4                   (1 << 4)
#define bit5                   (1 << 5)
#define bit6                   (1 << 6)
#define bit7                   (1 << 7)


#define LOGIC_HIGH             1


void DIO_Init      (char port , char pin , char direction);
void DIO_WritePin  (char port , char pin , char value);
void DIO_WritePort (char port , char value);
char DIO_ReadPin (char port, char pin);
char DIO_ReadPort (char port, char input_pins);

#endif
