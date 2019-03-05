#include "servosim.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

unsigned targets[6];
unsigned actualPos[6];

const unsigned max = 1000;
const unsigned screen_width = 50;

float clocky = 0;

void setServo(unsigned nr, unsigned pos) {
    targets[nr] = pos;
}

void update(float dt) {
    for (int i = 0; i < 6; i++) {
        actualPos[i] = targets[i];
    }

    clocky += dt;
};

void display() {
        char bg = '-';
        char bg_hit = '=';
        char fg = 'H';
        char fg_hit = '$';

        float zoom = 3;

    for (int i = 0; i < 6; i++) {
        printf(" [%i]  %4i  [", i, actualPos[i] + 1000);
        int displayPos = (actualPos[i] * screen_width / max);

        for (int j = 0; j < displayPos; j++)
            abs((int) actualPos[i] - 500) > 5 ? putchar(bg) : putchar(bg_hit);

        abs((int) actualPos[i] - 500) > 5 ? putchar(fg) : putchar(fg_hit);

        for (int j = 0; j < screen_width - displayPos; j++)
            abs((int) actualPos[i] - 500) > 5 ? putchar(bg) : putchar(bg_hit);
            
        printf("]\n");
    }
 
    //printf("%f", clocky);
};

void multiSetServo(unsigned nr, unsigned z) {
    setServo(nr, z - 1000);
};


void _delay_ms(unsigned short t) {
    // this multiplicative constant is a magic number that should in theory be 1000,
    // but that didn't quite match the speed of the real servos.
    usleep(t * 990);
};

void uartInit() {}
void ADCInit(int a) {}
void timerInit() {}
void multiServoInit() {}