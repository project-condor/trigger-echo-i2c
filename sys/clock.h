#ifndef CLOCK_H
#define CLOCK_H

void clock_init();
uint64_t time_micros();
uint64_t time_millis();
void wait_micros(uint64_t delay);

#endif
