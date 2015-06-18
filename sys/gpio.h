#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>

#define INPUT 0
#define OUTPUT 1

typedef struct {
	volatile uint8_t * const ddr;
	volatile uint8_t * const port;
	volatile uint8_t * const pin;
	uint8_t num;
} pinspec;

void pin_mode(pinspec spec, bool out);
void pin_write(pinspec spec, bool value);
bool pin_read(pinspec spec);

#endif
