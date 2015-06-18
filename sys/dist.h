#ifndef DIST_H
#define DIST_H

#include "gpio.h"
#include "irq.h"

struct dist_sensor {
	pinspec trig_pin;
	pinspec echo_pin;
	irq_t echo_irq;
	
	uint16_t distance;

	uint64_t delta_time;
};

void dist_init(struct dist_sensor* sensor);
void dist_read(struct dist_sensor* sensor);

#endif
