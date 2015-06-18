#include "gpio.h"

#include <avr/io.h>

void pin_mode(pinspec ps, bool out)
{
	if (out) {
		*ps.ddr |= (1 << ps.num);
	} else {

		*ps.ddr &= ~(1 << ps.num);
	}
}

void pin_write(pinspec ps, bool value)
{
	if (value) {
		*ps.port |= (1 << ps.num);
	} else {
		*ps.port &= ~(1 << ps.num);
	}
}

bool pin_read(pinspec ps)
{
	return *ps.pin & (1 << ps.num);
}
