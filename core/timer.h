
#pragma once

/***********************************************************************\
 * Get timer counter                                                  *
\***********************************************************************/

#define _timer_counter(TIMER) TIMER##_counter()
#define timer_counter(TIMER) _timer_counter(TIMER)

/***********************************************************************\
 * Set timer counter                                                   *
\***********************************************************************/

#define _timer_set_counter(TIMER,VALUE) TIMER##_set_counter(value)
#define timer_set_counter(TIMER,VALUE) _timer_set_counter(TIMER,VALUE)

/***********************************************************************\
 * Get timer overflow status                                           *
\***********************************************************************/

#define _timer_has_overflow(TIMER) TIMER##_has_overflow()
#define timer_has_overflow(TIMER) _timer_has_overflow(TIMER)

/***********************************************************************\
 * Clear timer overflow status                                         *
\***********************************************************************/

#define _timer_clear_overflow(TIMER) TIMER##_clear_overflow()
#define timer_clear_overflow(TIMER) _timer_clear_overflow(TIMER)

/***********************************************************************\
 * Get timer top status                                           *
\***********************************************************************/

#define _timer_has_top(TIMER) TIMER##_has_top()
#define timer_has_top(TIMER) _timer_has_top(TIMER)

/***********************************************************************\
 * Clear timer top status                                         *
\***********************************************************************/

#define _timer_clear_top(TIMER) TIMER##_clear_top()
#define timer_clear_top(TIMER) _timer_clear_top(TIMER)

