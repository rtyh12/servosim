#ifndef SERVOSIM_H
#define SERVOSIM_H


// boilerplate, on the microcontroller these are provided by the avr standard library

typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;



void setServo(unsigned nr, unsigned pos);
void update(float dt);
void display();



// these should mimic the functions given in basis-multiservo or the avr stdlib
// if they dont its cause im dum
void multiSetServo(unsigned nr, unsigned z);
void _delay_ms(unsigned short t);

void uartInit();
void ADCInit(int a);
void timerInit();
void multiServoInit();

#endif
