#ifndef DS1822_H_
#define DS1822_H_

#include <msp430.h>

#define WIRE BIT1
#define down 	P2OUT &= ~WIRE; P2DIR |= WIRE;
#define up 		P2DIR &= ~WIRE; P2OUT |= WIRE;

#define CT 	0x44
#define RS	0xBE
#define WS	0x4E
#define CS	0x48
#define RR	0x33
#define SR	0xCC

//public functions definitions
int TEMP_GET_T(void);
void TEMP_GPIO_init(void);
void TEMP_int_to_string(int, char*);

#endif
