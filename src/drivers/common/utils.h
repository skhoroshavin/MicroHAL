
#pragma once

#include <utils/bit_utils.h>

/**
 * @brief Empty function
 */
#define none()

/**
 * @brief Define register-based read only property
 * @param name Property name
 * @param type Property data type
 * @param reg Register name
 * @param update Function to update register before reading
 */
#define PROPERTY_REG_RO(name, type, reg, update) \
	inline type name() { update(); return reg; }

/**
 * @brief Define register-based write only property
 * @param name Property name
 * @param type Property data type
 * @param reg Register name
 * @param apply Function to apply register changes after writing
 */
#define PROPERTY_REG_WO(name, type, reg, apply) \
	inline void name##_set( type value ) { reg = value; apply(); }

/**
 * @brief Define register-based read write property
 * @param name Property name
 * @param type Property data type
 * @param reg Register name
 * @param update Function to update register before reading
 * @param apply Function to apply register changes after writing
 */
#define PROPERTY_REG_RW(name, type, reg, update, apply) \
	PROPERTY_REG_RO(name, type, reg, update) \
	PROPERTY_REG_WO(name, type, reg, apply)
