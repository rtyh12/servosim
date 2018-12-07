#ifndef SERVOSIM_H
#define SERVOSIM_H

void setServo(unsigned nr, unsigned pos);
void update(float dt);
void display();

// these should mimic the functions given in basis-multiservo or the avr stdlib
// if they dont its cause im dum
void multiSetServo(unsigned nr, unsigned z);
void _delay_ms(unsigned short t);

#endif
