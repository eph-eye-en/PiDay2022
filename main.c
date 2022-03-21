#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "pi.c"

unsigned int oldN = -1;
volatile unsigned int n = 0;

ISR(INT7_vect) {
	n++;
}

void updateDigit() {
	if(oldN == n)
		return;

	oldN = n;

	PORTD &= ~0xf;

	if(oldN == 0) {
		PORTD |= 0x3;
		return;
	}

	//Calculate nth digit, turning in-built LED on during calculation
	PORTD |= (1 << PD4);
	int digit = nthDigit(oldN - 1);
	PORTD &= ~(1 << PD4);
	//Output digit (mod 16) onto PORTD pins 0-3
	PORTD |= digit & 0xF;
}

int main() {
	DDRD |= 0x1F;	//Set PORTD pins 0-4 as output

	EICRB |= (1 << ISC71) | (1 << ISC70);	//Do interrupt on button rising edge
	EIMSK |= (1 << INT7);	//Enable interrupts for button
	sei();	//Global enable interrupts
	
	while(1) {
		updateDigit();

		//Enter idle to wait for next interrupt
		set_sleep_mode(SLEEP_MODE_IDLE);
		sleep_enable();
		sleep_cpu();
		sleep_disable();
	}
}
