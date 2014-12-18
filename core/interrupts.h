
#pragma once

#ifdef AVR

#include <avr/interrupt.h>

typedef uint8_t isr_status_t;

#define isr_enable() sei()
#define isr_disable() cli()

#define isr_store() SREG
#define isr_restore(s) do { SREG = (s); } while(0)

#endif // AVR

#define enter_critical() { isr_status_t _isr_status = isr_store(); isr_disable();
#define leave_critical() isr_restore( _isr_status ); }
