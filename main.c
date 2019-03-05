#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "servosim.h"


#include "notes.h"

// variables and constants go here

#define SERVO_COUNT 6
#define LOOP_DELAY 10

int32_t clock;
#define HIT_DELAY 50

uint16_t pos[SERVO_COUNT];
int16_t dir[SERVO_COUNT];
int16_t offset[SERVO_COUNT];	// offset from "true" center position. offset +- angle may not go out of the range (1000, 2000), otherwise the servos will cry :(

uint16_t speed = 5;

uint16_t z = 1500;

uint16_t angle[SERVO_COUNT];
const uint16_t middle = 1500;

const int loopForeverAndEver = 0;



/*struct Hit {
	uint16_t string;
	uint16_t time;
};*/


// gets called once at the start of the program
void init();



void loop() {
	int16_t i;
		for (i = 0; i < SERVO_COUNT; i++) {
			// stop servos that went out of this range:
			// set dir to 0 (stop movement)
			// and set pos to the respective edge of the range
			if (pos[i] > middle + angle[i]) {
				dir[i] = 0;
				pos[i] = middle + angle[i];
			}
			if (pos[i] < middle - angle[i]) {
				dir[i] = 0;				
				pos[i] = middle - angle[i];
			}

			// iterate through all hits
			int16_t j;
			for (j = 0; j < HIT_COUNT; j++) {
				// if time remaining until the hit is supposed to take place <= time it takes to hit a string,
				// but before the next timestep has started
				if (clock >= hits[j].time - HIT_DELAY && clock < hits[j].time - HIT_DELAY + LOOP_DELAY) {
					// then start to move the servo: forwards/backwards, depending on which side we are on right now
					dir[hits[j].string] = pos[hits[j].string] < middle ? 1 : -1;
				}
			}		

			pos[i] += dir[i] * speed;

			multiSetServo(i, pos[i] + offset[i]);
		}				

		clock += LOOP_DELAY;
		
		if (loopForeverAndEver) {
			if (clock >= 5500)
		        clock = 0;
		}

		_delay_ms(LOOP_DELAY);
}




int main(void) {
	init();

    while (1) {
        printf("\e[1;1H\e[2J");     // clears the console, might not work on windows idk

        loop();						// each call is one iteration of the loop
        update(LOOP_DELAY);
        display();

        //usleep(2.5 * 1000);
    }
}


int compare_hits(const void* a, const void* b) {
	struct Hit arg1 = *(const struct Hit*)a;
	struct Hit arg2 = *(const struct Hit*)b;

	if (arg1.time < arg2.time) return -1;
	if (arg1.time > arg2.time) return 1;
	return 0;
}

void init() {
	uartInit();			// serielle Ausgabe an PC
	ADCInit(0);			// Analoge Werte einlesen
	timerInit();		// "Systemzeit" initialisieren
	multiServoInit();	// Servoansteuerung initialisieren
	
	clock = -HIT_DELAY - 2500;

	set_notes();

	qsort(hits, HIT_COUNT, sizeof(struct Hit), compare_hits);
	
	/*
	pos[0] = 1500;
	dir[0] = 1;*/


	int16_t i;
	for (i = 0; i < SERVO_COUNT; i++)
		angle[i] = 20;

	for (i = 0; i < SERVO_COUNT; i++)
		pos[i] = middle - angle[i];
	
	for (i = 0; i < SERVO_COUNT; i++)
		dir[i] = 0;
		
	
	offset[0] = 0;
	offset[1] = 0;
	offset[2] = 0;
	offset[3] = 0;
	offset[4] = 0;
	offset[5] = 0;
}