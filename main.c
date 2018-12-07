#include <stdio.h>
#include <unistd.h>

#include "servosim.h"


typedef unsigned short uint16_t;


// variables and constants go here

uint16_t z = 1500; // recomend starting at the same position as the initialized value, as this way when the program starts up, it does not perform a jump
uint16_t y = 1300;

uint16_t c = 15; // having the speed at 15 seems to be a good speed to adequately play notes
uint16_t dir = 1;


// code from inside the microcontroller's loop goes here
// (so remove the loop when copy pasting it into this function)
void loop() {
	multiSetServo(0, z);
	multiSetServo(1, y);
	multiSetServo(5, z);

	if (dir) {
		z += c;
		y -= c;
	}
	else {
		z -= c;
		y += c;
	}

	if (z > 1650)
		dir = 0;
	if (z < 1350) // having a distance of 300 seems to be a good distance to play a singular string
		dir = 1;

	_delay_ms(20);
}

void main() {
    while (1) {
        printf("\e[1;1H\e[2J");     // clears the console, might not work on windows tho

        loop();
        update(20);
        display();

        usleep(100 * 1000);
    }
}
