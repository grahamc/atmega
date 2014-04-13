#define F_CPU 8000000UL

#define P_TOGGLE PD2
#define P_TIMER  PD3

#define P_SPEAKER PD5
#define P_DISPLAY PD6

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.h"

typedef enum { HIGH, LOW} digital_state;
void speaker(digital_state state);
digital_state toggle_status();
digital_state timer_status();

int main (void)
{
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;

puts("hi\n");

    DDRD |= (1 << P_SPEAKER); // Speaker out
    DDRD |= (1 << P_DISPLAY); // Display out

    PORTD |= (1 << P_TOGGLE); // Pull-up toggle switch
    PORTD |= (1 << P_TIMER); // Pull-up timer switch


    while(1) {
      if (toggle_status() == LOW) {
        speaker(HIGH);
      } else {
        speaker(LOW);
      }
    }
    return 1;
}

digital_state toggle_status() {
  if (PIND & (1 << P_TOGGLE)) {
    return HIGH;
  }

  return LOW;
}

digital_state timer_status() {
  if (PIND & (1 << P_TIMER)) {
    return HIGH;
  }

  return LOW;
}

void speaker(digital_state status) {
  if (status == HIGH) {
    PORTD |=  (1 << P_SPEAKER);
  } else {
    PORTD &= ~(1 << P_SPEAKER);
  }
}

