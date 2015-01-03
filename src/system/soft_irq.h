
/**
 * @file   soft_irq.h
 * @brief  Software IRQ implementation
 */

#pragma once

#include <stdint.h>

/**
 * @brief Call software IRQ handler (user-defined function)
 * @param id Software IRQ identifier
 */
void soft_irq_call( uint8_t id );

/**
 * @brief Call idle handler (user-defined function)
 */
void soft_irq_idle();

/**
 * @brief Raise software IRQ (interrupt version)
 * @param id Software IRQ identifier
 */
void soft_irq_raiseI( uint8_t id );

/**
 * @brief Raise software IRQ
 * @param id Software IRQ identifier
 */
void soft_irq_raise( uint8_t id );

/**
 * @brief Process software IRQs
 */
void soft_irq_process();
