#include "dist.h"
#include "irq.h"
#include "clock.h"

#define F_CPU_KHZ (F_CPU/1000)
#define LOOPS (2000 * F_CPU_KHZ)

//speed of sound in cm/s
#define C_SOUND (340l*100)

#include <avr/io.h>
static void pin_change(void* sensor)
{
	struct dist_sensor* sens = (struct dist_sensor*) sensor;
	if (pin_read(sens->echo_pin)) { //rising edge
		sens->delta_time = time_micros();
	} else { //falling edge
		sens->delta_time = time_micros() - sens->delta_time;
		uint32_t cm = C_SOUND * sens->delta_time / 1000000;
		sens->distance = (uint16_t) cm;
		
		DDRB |= (1 << PB1);
		PORTB |= (1 << PB1);
		dist_read(sensor);
	}
}

void dist_init(struct dist_sensor* sens)
{
	pin_mode(sens->echo_pin, INPUT);
	pin_mode(sens->trig_pin, OUTPUT);
	pin_write(sens->trig_pin, false);
	irq_register(sens->echo_irq, pin_change, sens);

	sens->distance = 0;
	sens->delta_time = 0;
}

/*
  Initiate read by pulsing trigger pin for 5us.
  Bringing the line down for 2us assures a clean pulse.
*/
void dist_read(struct dist_sensor* sens)
{
	pin_write(sens->trig_pin, false);
       	wait_micros(2);
	pin_write(sens->trig_pin, true);
	wait_micros(5);
	pin_write(sens->trig_pin, false);
}
