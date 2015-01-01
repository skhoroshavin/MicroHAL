
#include "soft_irq.h"
#include "hal.h"

#if defined(AVR)
#define soft_irq_reg GPIOR0
#else
static volatile uint8_t soft_irq_reg = 0;
#endif

void soft_irq_raiseI( uint8_t id )
{
	soft_irq_reg |= (1 << id);
}

void soft_irq_raise( uint8_t id )
{
#ifdef AVR
	soft_irq_raiseI( id );
#else
	irq_disable();
	soft_irq_raiseI( id );
	irq_enable();
#endif
}

void soft_irq_process()
{
	uint8_t i = 0;
	uint8_t mask = 1;

	irq_disable();
	while( i < soft_irq_count )
	{
		if( soft_irq_reg & mask )
		{
			soft_irq_reg &= ~mask;
			irq_enable();
			soft_irq_call( i );
			return;
		}

		++i;
		mask <<= 1;
	}

	soft_irq_idle();
}

void soft_irq_run()
{
	while(1)
	{
		irq_enable();
		soft_irq_process();
	}
}
