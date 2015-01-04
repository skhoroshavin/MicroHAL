
#pragma once

/**
 * @brief Empty function
 */
#define none()

/**
 * @brief Define read-only device
 * @param name Device name
 * @param type Device data type
 * @param reg Device data register
 * @param pre_get Device function to update register
 */
#define DEFINE_DEVICE_RO(name, type, reg, pre_get) \
	inline type name() { pre_get(); return reg; }

/**
 * @brief Define write-only device
 * @param name Device name
 * @param type Device data type
 * @param reg Device data register
 * @param post_set Device function to update internal state
 */
#define DEFINE_DEVICE_WO(name, type, reg, post_set) \
	inline void name##_set( type value ) { reg = value; post_set(); }

/**
 * @brief Define read-write device
 * @param name Device name
 * @param type Device data type
 * @param reg Device data register
 * @param pre_get Device function to update register
 * @param post_set Device function to update internal state
 */
#define DEFINE_DEVICE_RW(name, type, reg, pre_get, post_set) \
	DEFINE_DEVICE_RO(name, type, reg, pre_get) \
	DEFINE_DEVICE_WO(name, type, reg, post_set)
