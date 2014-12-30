
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
 * @brief Mark software IRQ for execution (interrupt version)
 * @param id Software IRQ identifier
 */
void soft_irq_emitI( uint8_t id );

/**
 * @brief Mark software IRQ for execution
 * @param id Software IRQ identifier
 */
void soft_irq_emit( uint8_t id );

/**
 * @brief Run software IRQ system
 */
void soft_irq_run();
