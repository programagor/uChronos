/*
 * uChronos.c
 *
 * Optimised for uChronos_v0.3
 * Created: 23/09/2017 7:18:21 PM
 * Author : pmg
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>




/* This is used in the refresher routine. No buffering */
uint8_t disp_mem[6]=
{
	0b11111111,
	0b11111111,
	0b11111111,
	0b10101110,
	0b10100100,
	0b10100010
};

/* Here, the time is stored */
uint8_t t_yr,t_mth,t_d,t_h,t_min,t_s;


int main(void)
{
	/* Initialise ports immediately (fixed in v0.4) */
	PORTC=0b00111111; /* Shut down displays...  */
	DDRC =0b00111111; /* ...before being output */
	
	
	PORTD=0b00000000;
	DDRD =0b11111111;
	
	//Default time
	t_yr=17;
	t_mth=9;
	t_d=29;
	t_h=2;
	t_min=27;
	t_s=24;
	
	SMCR=SMCR|1<<SE;
	
	//Now, set up the 1s timer
	if(useAsync)
	{
		
		OCR2A=220;
		TIMSK2=TIMSK2|1<<OCIE2A;
		TCCR2A=TCCR2A|1<<WGM21;
		TCCR2B=TCCR2B|1<<CS22|1<<CS21|1<<CS20;
		sei();
		
	}
	
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
disp_mem[5]=(t_s%10)|(t_s/10)<<4;
disp_mem[4]=(t_min%10)|(t_min/10)<<4;
disp_mem[3]=(t_h%10)|(t_h/10)<<4;
}