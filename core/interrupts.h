
#pragma once

#if defined(AVR)

#include <avr/interrupt.h>
#include <avr/sleep.h>

#define irq_enable() sei()
#define irq_disable() cli()

#define enable_critical() uint8_t _sreg
#define enter_critical() do { _sreg = SREG; cli(); } while(0)
#define leave_critical() do { SREG = _sreg; } while(0)

#define wait_for_irq() sleep_cpu()

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
 * @brief Enable critical sections in this block of code
 */
#define enable_critical()

/**
 * @brief Enter cricial section
 */
#define enter_critical()

/**
 * @brief Leave critical section
 */
#define leave_critical()

/**
 * @brief Wait for hardware IRQ
 */
#define wait_for_irq()

#endif
