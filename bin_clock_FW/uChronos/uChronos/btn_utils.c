#include <avr/io.h>
#include "btn_utils.h"
#include "state_machine.h"

uint8_t btn_mem[1]={0};

void btn_read()
{
	uint8_t btns=~PINB & 0b111;
	uint8_t p=btns^btn_mem[0];
	if(p)
	{
		uint8_t i;
		for(i=0;!(p&(1<<i));i++); //Find the button that changed
		btn_mem[0]=btns;
		
		uint8_t next_state;
		if(btn_mem[0]&(1<<i))
		{
			next_state=states[state].btn_down_arg[i];
		}
		else
		{
			
			next_state=states[state].btn_up_arg[i];
		}
		
		state_goto(next_state);
		
	}
}
