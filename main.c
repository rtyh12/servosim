#include <stdio.h>
#include <unistd.h>

#include "servosim.h"



// variables and constants go here

#define SERVO_COUNT 6
#define LOOP_DELAY 20

int clock;
#define HIT_DELAY 250

uint16_t pos[SERVO_COUNT];
int dir[SERVO_COUNT];

uint16_t speed = 15;



struct Hit {
	uint16_t string;
	uint16_t time;
};

#define HIT_COUNT 12
struct Hit hits[HIT_COUNT];



// gets called once at the start of the program
void initialize() {
	clock = -HIT_DELAY;

	hits[0].string = 0;
	hits[0].time = 0;

	hits[1].string = 1;
	hits[1].time = 500;

	hits[2].string = 2;
	hits[2].time = 1000;

	hits[3].string = 0;
	hits[3].time = 1500;

	hits[4].string = 4;
	hits[4].time = 2000;

	hits[5].string = 5;
	hits[5].time = 2500;

	hits[6].string = 0;
	hits[6].time = 3000;

	hits[7].string = 1;
	hits[7].time = 3500;

	hits[8].string = 2;
	hits[8].time = 4000;

	hits[9].string = 3;
	hits[9].time = 4500;

	hits[10].string = 4;
	hits[10].time = 5000;

	hits[11].string = 5;
	hits[11].time = 5500;
	

	for (int i = 0; i < SERVO_COUNT; i++)
		pos[i] = 1100;
	
	for (int i = 0; i < SERVO_COUNT; i++)
		dir[i] = 0;
}



// each call to this function is one iteration of the loop
void loop() {
	for (int i = 0; i < SERVO_COUNT; i++) {
		// stop all servos which went out of this range
		if (pos[i] > 1900 || pos[i] < 1100) {
			dir[i] = 0;
		}

		// iterate through all hits
		for (int i = 0; i < HIT_COUNT; i++) {
			// if time remaining until the hit is supposed to take place <= time it takes to hit a string
			if (clock >= hits[i].time - HIT_DELAY && clock <= hits[i].time - 20) {
				// then start to move the servo: forwards/backwards, depending on which side we are on right now
				dir[hits[i].string] = pos[hits[i].string] < 1500 ? 1 : -1;
			}
		}		

		pos[i] += dir[i] * speed;

		multiSetServo(i, pos[i]);
	}

	clock += LOOP_DELAY;
	_delay_ms(LOOP_DELAY);
}



void main() {
	initialize();

    while (1) {
        printf("\e[1;1H\e[2J");     // clears the console, might not work on windows idk

        loop();						// each call is one iteration of the loop
        update(LOOP_DELAY);
        display();

        usleep(25 * 1000);
    }
}
