#include "servosim.h"

#include <stdio.h>
#include <unistd.h>

unsigned targets[6];
unsigned actualPos[6];

const unsigned max = 1000;
const unsigned screen_width = 50;

void setServo(unsigned nr, unsigned pos) {
    targets[nr] = pos;
}

void update(float dt) {
    for (int i = 0; i < 6; i++) {
        actualPos[i] = targets[i];
    }
};

void display() {
    for (int i = 0; i < 6; i++) {
        printf("[%i] %4i  [", i, actualPos[i]);
        int displayPos = actualPos[i] * screen_width / max;
        for (int j = 0; j < displayPos; j++)
            putchar('=');
        putchar('O');
        for (int j = 0; j < screen_width - displayPos; j++)
            putchar(' ');
        printf("]\n");
    }
};

void multiSetServo(unsigned nr, unsigned z) {
    setServo(nr, z - 1000);
};


void _delay_ms(unsigned short t) {
    usleep(t * 1000);
};
