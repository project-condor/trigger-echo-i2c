#include "irq.h"
#include <avr/interrupt.h>

struct irq_entry {
	void (*fct)(void*);
	void* arg;
};

static struct irq_entry irqs[IRQ_SIZE] = {{0}};

void irq_register(irq_t irq, void (*fct)(void*), void* arg)
{
	if (irq >= IRQ_SIZE) return;

	(&irqs[irq])->fct = fct;
	(&irqs[irq])->arg = arg;
	
}

inline static void run_irq(irq_t num)
{
	struct irq_entry* entry = &irqs[num];
	if (entry->fct != 0) {
		entry->fct(entry->arg);
	}
}


//ISR(TIMER0_OVF_vect) { run_irq(IRQ_TIMER0_OVF); }
ISR(PCINT0_vect) { run_irq(IRQ_PCINT0); }
