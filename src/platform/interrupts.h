
#pragma once

#if defined(AVR)

#include <avr/interrupt.h>
#include <avr/sleep.h>

typedef uint8_t irq_state_t;

#define irq_enable() sei()
#define irq_disable() cli()

inline irq_state_t irq_store_and_disable() { irq_state_t result = SREG; cli(); return result; }
inline void irq_restore( irq_state_t state ) { SREG = state; }

#define wait_for_irq() \
	do { \
		sleep_enable(); \
		sei(); \
		sleep_cpu(); \
		sleep_disable(); \
	} while(0)

#else

/**
 * @brief Enable hardware IRQ
 */
#define irq_enable()

/**
 * @brief Disable hardware IRQ
 */
#define irq_disable()

/**
 * @brief Disable hardware IRQ returning previous state
 * @return Previous IRQ state
 */
inline irq_state_t irq_store_and_disable() { return 0; }

/**
 * @brief Restore hardware IRQ state
 * @param state Hardware IRQ state to be restored
 */
inline void irq_restore( irq_state_t state ) { }

/**
 * @brief Wait for hardware IRQ
 */
#define wait_for_irq()

#endif
