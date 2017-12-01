/*
 * uChronos.c
 *
 * Optimised for uChronos_v0.3
 * Created: 23/09/2017 7:18:21 PM
 * Author : pmg
 */ 

/* Includes */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "bin_utils.h"
#include "disp_utils.h"
#include "btn_utils.h"
#include "state_machine.h"
#include "time_utils.h"

/* Definitions */
#define USE_ASYNC 0







int main(void)
{
	/* Initialise ports immediately (fixed in v0.4) */
	PORTC=0b00111111; /* Shut down displays...  */
	DDRC =0b00111111; /* ...before being output */
	
	
	PORTD=0b00000000;
	DDRD =0b11111111;
	
	PORTB=0b11111111;
	DDRB =0b11111111;
	
	//Default display memory
	disp_clear(0b00111111);
	
	//Default time
	t_y=17;
	t_mth=11;
	t_d=21;
	t_h=02;
	t_min=03;
	t_s=00;
	
	SMCR=SMCR|1<<SE;
	
	//Now, set up the 10ms timer
	if(USE_ASYNC)
	{
		
		OCR2A=220;
		TIMSK2=TIMSK2|1<<OCIE2A;
		TCCR2A=TCCR2A|1<<WGM21;
		TCCR2B=TCCR2B|1<<CS22|1<<CS21|1<<CS20;
		
	}
	else
	{
		OCR2A=155;
		TIMSK2=TIMSK2|1<<OCIE2A;
		TCCR2A=TCCR2A|1<<WGM21;
		TCCR2B=TCCR2B|1<<CS22;
	}
	
	
	//All is ready, let's go!
	init_states();
	state_goto(2);
	sei();
	
    while (1) 
    {
		
		for(int c=0;c<6;c++)
		{
			for(uint16_t i=5*4;--i;);
			disp_refresh();
			
			
			
			
			
		}
		
		
		
		
    }	/* main() must never end! */
}		/* Keep these two brackets together */





ISR(TIMER2_COMPA_vect)
{
	tick10ms();
	btn_read();
}