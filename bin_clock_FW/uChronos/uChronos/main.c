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

/* Definitions */
#define USE_ASYNC 0


/* This is used in the refresher routine. No buffering */
extern uint8_t disp_mem[];


/* Here, the time is stored */
uint8_t t_y,t_mth,t_d,t_h,t_min,t_s;


int main(void)
{
	/* Initialise ports immediately (fixed in v0.4) */
	PORTC=0b00111111; /* Shut down displays...  */
	DDRC =0b00111111; /* ...before being output */
	
	
	PORTD=0b00000000;
	DDRD =0b11111111;
	
	//Default display memory
	clear_disp();
	
	//Default time
	t_y=17;
	t_mth=9;
	t_d=29;
	t_h=2;
	t_min=27;
	t_s=24;
	
	SMCR=SMCR|1<<SE;
	
	//Now, set up the 1s timer
	if(USE_ASYNC)
	{
		
		OCR2A=220;
		TIMSK2=TIMSK2|1<<OCIE2A;
		TCCR2A=TCCR2A|1<<WGM21;
		TCCR2B=TCCR2B|1<<CS22|1<<CS21|1<<CS20;
		
	}
	else
	{
		OCR2A=220;
		TIMSK2=TIMSK2|1<<OCIE2A;
		TCCR2A=TCCR2A|1<<WGM21;
		TCCR2B=TCCR2B|1<<CS22|1<<CS21|1<<CS20;
	}
	
	
	//All is ready, let's go!
	sei();
	
    while (1) 
    {
		for(int c=0;c<6;c++)
		{
			PORTC=0b00111111&~(1<<c);
			//PORTD=(cntr>>(8*(5-c)))&0xff;
			PORTD=disp_mem[c];
			
			//PORTD=cntr&&0xff;
			for(uint16_t i=5*4;--i;);
			PORTD=0b00000000;
			PORTC=0b00111111;
			for(uint16_t i=5*4*1;--i;);
		}
		
		
		
/* main() must never end! */
    }
}
/* Keep these two brackets together */




ISR(TIMER2_COMPA_vect)
{
	if(++t_s==60)
	{
		t_s=0;
		if(++t_min==60)
		{
			t_min=0;
			if(++t_h==24)
			{
				t_h=0;
				
			}
		}
}
disp_time((uint8_t)0b000111);
}