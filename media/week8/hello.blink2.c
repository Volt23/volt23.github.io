#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

void delay_ms(uint16_t ms);
void init_io();
int button_is_pressed();
void toggle_led();

int
main (void)
{
    
        //Button = Attiny44 pin PB2
        DDRB &= (1<<PB2);
        PORTB |= (1<<PB2);
        
        //LED = Attiny44 pin PA7
        DDRA |= (1<<PA7);
        PORTA |= (1<<PA7);
    
    
            
        while (1) {
            //check if button is pressed
            if ((PINB & (1<<PB2)) == (1 << PB2)) {
                //blink faster
                PORTA &= ~(1<<PA7);
                _delay_ms(100);
                PORTA |= (1<<PA7);
                _delay_ms(100);

                
                
            } else {
                //blink normal
                PORTA &= ~(1<<PA7);
                _delay_ms(1000);
                PORTA |= (1<<PA7);
                _delay_ms(1000);
            }
        }
    }