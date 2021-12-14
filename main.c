/* 
 * File:   main.c
 * Author: Nikhil Saroya
 * Student ID: 1629920
 * ECE 312 Project 3: Data Logger
 * 
 * Created on November 12, 2021, 3:11 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <avr/interrupt.h>

volatile uint8_t T = 0; // Initializing our Time global display variables 
volatile uint8_t S = 0;
volatile uint8_t M = 0;
volatile uint8_t H = 0;
volatile uint16_t D = 0;

ISR(TIMER1_COMPA_vect, ISR_BLOCK) {

    T++;
    if (T > 9) {
        T = 0;
        S++;
    }
    if (S > 59) {
        S = 0;
        
        M++;
    }
    if (M > 59) {
        M = 0;
        H++;
    }
    if (H > 23) {
        H = 0;
        D++;
    }
    if (D > 999) {
        D = 0;
        T = 0;
        S = 0;
        M = 0;
        H = 0;
    }
}; // Interrupt Routine

int main(void) {

    button_init();
    USART_init();
    
    char a[] = "Channel 1\n\r";
    char b[] = "Channel 2\n\r";
    char c[] = "Channel 3\n\r";
    char d[] = "Channel 4\n\r";
    
    wavegenT1_init();
   
    sei(); // turn on interrupts

    USART_Transmit('N');   // Displaying Name and CCID
    USART_Transmit('i');   // If I try to use a loop it kind of misbehaves, so that's why I used this basic way for requirement
    USART_Transmit('k');
    USART_Transmit('h');
    USART_Transmit('i');
    USART_Transmit('l');
    USART_Transmit(' ');
    USART_Transmit('1');
    USART_Transmit('6');
    USART_Transmit('2');
    USART_Transmit('9');
    USART_Transmit('9');
    USART_Transmit('2');
    USART_Transmit('0');

    USART_Transmit('\n');
    USART_Transmit('\r');
    
    while (1) {


        while ((button_1() || button_2() || button_3() || button_4()) == 0) { // Holds the iteration until any further switch is pressed
        };
        while (button_1()) {

            while (button_1()) {
            }
            Transmit_Format();          // Displaying clock data

            for (uint8_t i = 0; i < sizeof (a); i++) {   // Displaying the channel number depending upon switch button pressed
                USART_Transmit(a[i]);
            }
        }
        while (button_2()) {
            
            while (button_2()) {
            }
            Transmit_Format();       // Displaying clock data

            for (uint8_t i = 0; i < sizeof (b); i++) {    // Displaying the channel number depending upon switch button pressed
                USART_Transmit(b[i]);
            }
        }
        while (button_3()) {
            
            while (button_3()) {
            }
            Transmit_Format();      // Displaying clock data

            for (uint8_t i = 0; i < sizeof (c); i++) {    // Displaying the channel number depending upon switch button pressed
                USART_Transmit(c[i]);
            }
        }
        while (button_4()) {
            
            while (button_4()) {
            }
            Transmit_Format();       // Displaying clock data

            for (uint8_t i = 0; i < sizeof (d); i++) {    // Displaying the channel number depending upon switch button pressed
                USART_Transmit(d[i]);
            }
        }
    }
    return (0);
};


void Transmit_Format(void) {

    char Day[] = {'0','0','0'}; // Initializing our Arrays for our clocks  
    char Hours[] = {'0','0'};
    char Minutes[] = {'0','0'};
    char Seconds[] = {'0','0'};
    char Dec_Second[] = {'0'};


    itoa(D, Day, 10);
    for (uint8_t i = 0; i < sizeof Day; i++) {

        USART_Transmit(Day[i]);
    }
    USART_Transmit(':');

    itoa(H, Hours, 10);
    for (uint8_t i = 0; i < sizeof Hours; i++) {

        USART_Transmit(Hours[i]);
    }
    USART_Transmit(':');

    itoa(M, Minutes, 10);
    for (uint8_t i = 0; i < sizeof Minutes; i++) {

        USART_Transmit(Minutes[i]);
    }
    USART_Transmit(':');

    itoa(S, Seconds, 10);
    for (uint8_t i = 0; i < sizeof Seconds; i++) {

        USART_Transmit(Seconds[i]);
    }
    USART_Transmit(':');


    itoa(T, Dec_Second, 10);
    for (uint8_t i = 0; i < sizeof Dec_Second; i++) {
        USART_Transmit(Dec_Second[i]);
    }
    USART_Transmit(' ');
};

void button_init(){
    DDRB &= ~(1 << PORTB2); // PB2,PB3,PB4 as inputs
    DDRB &= ~(1 << PORTB3); //
    DDRB &= ~(1 << PORTB4); //
    DDRB &= ~(1 << PORTB5); //

    PORTB |= (1 << PORTB5); // Turn off the pullups
    PORTB |= (1 << PORTB4); // 
    PORTB |= (1 << PORTB3); //
    PORTB |= (1 << PORTB2); //
};

void USART_init(){
    int BRC = 0x2;
    UBRRH = (BRC >> 8); // upper 8 bit shifted in upper register
    UBRRL = (BRC);

    //Setting up the transmitter
    UCSRB |= (1 << TXEN) | (1 << TXCIE);
    UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);
};

void wavegenT1_init(){
    // Function for Generation of our required waveform used for Timing purposes

    TCCR1A = 0x40; // Wave generation in CTC mode and toggle after comparison for Timer 1
    OCR1A = 23039;
    TIMSK = 0x40; // Enabling Timer Interrupts with interrupt at output compare match value OCIE1A enabled
    TIFR = 0x40; // Interrupt Flags Enabled
    TCCR1B = 0x0B;
};


void USART_Transmit(unsigned char data) {
    /* Wait for empty transmit buffer */
    while (!(UCSRA & (1 << UDRE)))
        ;
    /* Put data into buffer, sends the data */
    UDR = data;
    return 0;
};

unsigned char USART_Receive(void) {
    /* Wait for data to be received */
    while (!(UCSRA & (1 << RXC)))
        ;
    /* Get and return received data from buffer */
    return UDR;
};

int button_1() {
    int q;
    q = !(PINB & (1 << PINB2));
    return (q);
};

int button_2() {
    int q;
    q = !(PINB & (1 << PINB3));
    return (q);
};

int button_3() {
    int q;
    q = !(PINB & (1 << PINB4));
    return (q);
};

int button_4() {
    int q;
    q = !(PINB & (1 << PINB5));
    return (q);
};



