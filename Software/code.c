#define __AVR_ATmega16U2__

#include <avr/io.h> 
#include <avr/interrupt.h> 
#include <util/delay.h>

uint8_t counter = 0;
uint8_t mode = 0;

const uint8_t NUM_MODES = 5;


volatile uint8_t* ledmr[3] = {&DDRB, &DDRC, &DDRD};
volatile uint8_t* ledr[3] = {&PORTB, &PORTC, &PORTD};
const uint8_t conv[16] = {0, 0, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0};

const uint8_t ledn[16] = {PB1, PB0, PD6, PD5, PD4, PD3, PD2, PD1, PD0, PC7, PB7, PB6, PB5, PB4, PB3, PB2};

void ledON(uint8_t index) { *(ledr[conv[index]]) |= (1 << ledn[index]); }
void ledOFF(uint8_t index) { *(ledr[conv[index]]) &= ~(1 << ledn[index]); }

void init_leds() {
    for (uint8_t i = 0; i < 16; i++) {
        *(ledmr[conv[i]]) |= (1 << ledn[i]);
        *(ledr[conv[i]]) &= ~(1 << ledn[i]);
    }
}

void allON() {
    for (uint8_t i = 0; i < 16; i++) {
        *(ledr[conv[i]]) |= (1 << ledn[i]);
    }
}

void allOFF() {
    for (uint8_t i = 0; i < 16; i++) {
        *(ledr[conv[i]]) &= ~(1 << ledn[i]);
    }
}


void init_interrupts()
{
    // Configure Pin C2 as input
    DDRC &= ~(1 << PC2);
    // Enable pull-up resistor on Pin C2
    PORTC |= (1 << PC2);

    // Enable interrupt on Pin C2 (PCINT11)
    PCICR |= (1 << PCIE1) | (1 << PCIE0); 
    PCMSK1 |= (1 << PCINT11); 
}

ISR(PCINT1_vect) {

    if (PINC & (1 << PC2)) {
        allOFF();

        mode = (mode+1) % NUM_MODES;
        counter = 0;

        if (mode == NUM_MODES - 1) {
            allON();
        }
    }

}

void startup() {

    // . .
    // . - . .  - - -    . . . -    . 
    // - . - -  - - -   . . -
    _delay_ms(100);

    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);

    _delay_ms(150);

    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);

    _delay_ms(75);

    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);

    _delay_ms(75);

    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);

    _delay_ms(75);

    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);

    _delay_ms(150);

    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);

    _delay_ms(75);

    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);

    _delay_ms(75);

    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(25);
    allOFF();
    _delay_ms(25);
    allON();
    _delay_ms(50);
    allOFF();
    _delay_ms(25);

    _delay_ms(75);


}

int main()
{

    init_leds();
    init_interrupts();

    startup();

    sei(); //Enable global interrupts


    while (1) {

        if (mode == 0) {
            counter = counter%8;
            if (counter%4 == 0) { //twinkle1
                for (uint8_t i = 0; i < 16; i+=2) {
                    ledON(i);
                }

                for (uint8_t i = 1; i < 16; i+=2) {
                    ledOFF(i);
                }

            } else if (counter%2 == 0) { //twinkle2-- "else if" very important so that twinkle2 is not triggered after twinkle1
                for (uint8_t i = 0; i < 16; i+=2) {
                    ledOFF(i);
                }

                for (uint8_t i = 1; i < 16; i+=2) {
                    ledON(i);
                }
            }

        } else if (mode == 1) {
            counter = counter%10;
            if (counter == 0 || counter == 2) {
                allON();
            } else if (counter == 1 || counter == 3) {
                allOFF();
            }

        } else if (mode == 2) {
            counter = counter%18;
            if (counter < 9) {
                if(counter != 8)
                    ledON(8+counter);
                ledON(8-counter);
            } else {
                if(counter != 17)
                    ledOFF(8+(counter-9));
                ledOFF(8-(counter-9));
            }
            
        } else if (mode == 3) {
            counter = counter%32;
            if (counter < 16)
                ledON(counter);
            else
                ledOFF(counter-16);
            
        } else if (mode == 4) {
            //do nothing
        }


        counter++;
        _delay_ms(25);

    }

    return 0;
}



/* LED Mappings (Clockwise, starting from top)
17  B1
16  B0
14  D6
13  D5
12  D4
11  D3
10  D2
09  D1
08  D0
07  C7
23  B7
22  B6
21  B5
20  B4
19  B3
18  B2
*/

/* MODES
0 - twinkle
1 - heart beat
2 - vertical snake
3 - snake
4 - solid

*/


