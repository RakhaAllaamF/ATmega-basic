/*
 * Phase Correct PWM.c
 * Created: 15/09/2022 23.29.09
 * Author : Abdan Subekti
 */ 
#define F_CPU 16000000L // Selecting MCU clock speed in Hertz
#include <avr/io.h> // Microcontroller i/o library
#include <util/delay.h> // Delay functions library
#include <avr/interrupt.h> // Interrupt library

// Duty cycle variable declaration, use this to change duty cycle percentage
double duty = 50; 

int main(void)
{
	DDRB = (1 << PORTB3); // Data Direction Register PORT B3 set as output
	TCCR0 = (1 << WGM00)|(1 << COM01); // Set PWM signal generation mode Phase Correct PWM
	TIMSK = (1 << OCIE0); // Output Interrupt Compare Enable
	
	sei(); // Global interrupt mask
	
	TCCR0 |= (1 << CS02)|(1 << CS00); // Set clock with Prescaler 1024
	
    while (1) 
    {
		_delay_ms(2000); // delay 2 seconds
		duty++; // up increment
	    
	    	// When duty variable reach 100, set duty to 50 again
		if (duty > 100)
		{
			duty = 50;
		}
    }
}

ISR(TIMER0_COMP_vect) // Interrupt service routine timer 0
{
	OCR0 = (duty/100)*255; // counting OCR
}

