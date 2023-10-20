#include <avr/io.h>
#include <stdio.h>
#include <util/setbaud.h>

#define BAUD 115200 // Baudratehastigheten


// Funktion som initierar uart
void uart_init(void)
{
    UBRR0H = UBBRH_VALUE;
    UBRR0L = UBBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

 UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bitar data */ 
 UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Aktivera RX and TX */  
}
int uart_putchar (char c, FILE *stream)
{
    // if (c == '\n') {
    //     uart_putchar('\r', stream);
    // }
  loop_until_bit_is_set(USCR0A, UDRE0);
  UDR0 = c;
  return(0);
}

// Läser character från UART 
int uart_getchar (FILE *stream)
{
    loop_until_bit_is_set(USCR0A, RXC0);
    return UDR0;
}

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar,NULL, _FDEV_SETUP_WRITE)
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);


// Funktion för seriell kommunikation
void init_serial()
{
    uart_init();
    stdout = &uart_output;
    stdin = &uart_input;
}
