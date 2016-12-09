#ifndef LIFX_H
#define LIFX_H

#include <stdbool.h>
#include "bulb.h"
#include "color.h"

#define LIFX_LABEL_LENGTH (32) // does not include NULL char at the end


int init_lifx_lib(void);

int close_lifx_lib(void);

/** NULL terminated array of bulbs, use free after use */
int discoverBulbs(bulb_service_t ***ppp_bulbs);

int freeBulbs(bulb_service_t **pp_bulbs);

int getPower(bulb_service_t *bulb, bool *p_on);

int setPower(bulb_service_t *bulb, bool on, uint32_t duration);

/** @param label 32 byte string and 1 null character as terminator */
int getColor(bulb_service_t *bulb, bool *p_on, color_t *color, char label[LIFX_LABEL_LENGTH + 1]);

int setColor(bulb_service_t *bulb, color_t color, uint32_t duration);

#endif
