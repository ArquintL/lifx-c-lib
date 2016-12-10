/*
**  LIFX C Library
**  Copyright 2016 Linard Arquint
*/

#include <stdio.h>
#include <unistd.h>

#include "lifx.h"
#include "bulb.h"
#include "color.h"


static void printBulb(bulb_service_t *bulb) {
	printf("bulb\n");
	printf("    target: %llu\n", bulb->target);
	printf("    service: %d\n", bulb->service);
	printf("    port: %d\n", bulb->port);
	printf("----\n");
}

static void printBulbs(bulb_service_t **bulbs) {
	int bulb_counter = 0;
	while (bulbs[bulb_counter] != NULL) {
		printBulb(bulbs[bulb_counter]);
		bulb_counter++;
	}
}

static int printCurrentPowerLevel(bulb_service_t *bulb) {
	bool on;
	int res;
	if ((res = getPower(bulb, &on))) {
		printf("getPower error: %d\n", res);
		return -1;
	}
	printf("bulb is turned %s\n", on ? "on" : "off");
	return 0;
}

static int testPower(bulb_service_t *bulb) {
	int res;
	if ((res = setPower(bulb, true, 500))) {
		printf("setPower error: %d\n", res);
		return -1;
	}
	sleep(2);
	if (printCurrentPowerLevel(bulb)) {
		return -1;
	}
	if ((res = setPower(bulb, false, 500))) {
		printf("setPower error: %d\n", res);
		return -1;
	}
	sleep(1);
	if (printCurrentPowerLevel(bulb)) {
		return -1;
	}
	return 0;
}

static int testColor(bulb_service_t *bulb) {
	// get color to set the same color afterwards
	bool on;
	color_t orig_color;
	char label[33];
	int res;
	if ((res = getColor(bulb, &on, &orig_color, label))) {
		printf("getColor error: %d\n", res);
		return -1;
	}
	printf("bulb state\n");
	printf("    name: %s\n", label);
	printf("    on: %s\n", on ? "yes" : "no");
	printf("    hue: %d\n", orig_color.hue);
	printf("    saturation: %d\n", orig_color.saturation);
	printf("    brightness: %d\n", orig_color.brightness);
	printf("    kelvin: %d\n", orig_color.kelvin);
	printf("----------\n");

	sleep(2);

	// test: blue color (hue: 240°, saturation: 100%, brightness: 100%)
	color_t blue = {
		.hue = (uint16_t)((float)240 / 360 * 65535),
		.saturation = 65535,
		.brightness = 65535,
		.kelvin = 9000,
	};
	color_t white = {
		.hue = 0,
		.saturation = 0,
		.brightness = 0xFFFF,
		.kelvin = 3500,
	};
	color_t green = {
		.hue = 0x5555,
		.saturation = 0xFFFF,
		.brightness = 0xFFFF,
		.kelvin = 0x0DAC,
	};

	if ((res = setColor(bulb, blue, 1000))) {
		printf("setColor (blue) error: %d\n", res);
		return -1;
	}

	sleep (3); 

	if ((res = setColor(bulb, green, 0))) {
		printf("setColor (green) error: %d\n", res);
		return -1;
	}

	sleep (2); 

	// revert color:
	if ((res = setColor(bulb, white, 500))) { // duration: 2 sec
		printf("setColor (white) error: %d\n", res);
		return -1;
	}

	sleep (2); // 3 sec

	return 0;
}	

int main(void) {
	int res;
	if ((res = init_lifx_lib())) {
		printf("init error: %d\n", res);
		return -1;
	}
	bulb_service_t **bulbs;
	if ((res = discoverBulbs(&bulbs))) {
		printf("discoverBulb error: %d\n", res);
		return -1;
	}
	printBulbs(bulbs);
	if (bulbs[0] != NULL) {
		if ((res = testPower(bulbs[0]))) {
			printf("testPower error: %d\n", res);
			return -1;
		}
		if ((res = testColor(bulbs[0]))) {
			printf("testColor error: %d\n", res);
			return -1;
		}
	}
	if ((res = freeBulbs(bulbs))) {
		printf("freeBulbs error: %d\n", res);
		return -1;
	}
	if ((res = close_lifx_lib())) {
		printf("close error: %d\n", res);
		return -1;
	}
	return 0;
}
