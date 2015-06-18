#ifndef IRQ_H
#define IRQ_H

//#define IRQ_TIMER0_OVF 0 // ISR is handled directly by clock
#define IRQ_PCINT0 0

#define IRQ_SIZE 1

typedef unsigned char irq_t;

void irq_register(irq_t irq, void (*fct)(void*), void* arg);

#endif
