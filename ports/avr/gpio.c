
#include <ports/avr/gpio.h>

#ifdef PORTA
AVR_IMPLEMENT_GPIO(A)
#endif // PORTA

#ifdef PORTB
AVR_IMPLEMENT_GPIO(B)
#endif // PORTB

#ifdef PORTC
AVR_IMPLEMENT_GPIO(C)
#endif // PORTC

#ifdef PORTD
AVR_IMPLEMENT_GPIO(D)
#endif // PORTD

#ifdef PORTE
AVR_IMPLEMENT_GPIO(E)
#endif // PORTE

#ifdef PORTF
AVR_IMPLEMENT_GPIO(F)
#endif // PORTF
