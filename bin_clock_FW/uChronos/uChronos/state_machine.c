#include <avr/io.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "state_machine.h"

#include "disp_utils.h"
#include "time_utils.h"
#include "snake.h"



States states[STATES_NUM];
uint8_t state;

uint8_t disable_tick=0;

/* Init functions*/
void init_powersave()
{
	time_mask=0;
	disp_clear(0b00111111);
	disp_time(time_mask);
}
void init_minmode()
{
	time_mask=0b110;
	disp_clear(0b00111111);
	disp_time(time_mask);
}
void init_fullmode()
{
	time_mask=0b111111;
	disp_time(time_mask);
}


static uint8_t timeset_ctr=0;
void init_time_hub()
{
	if(timeset_ctr++<6)
	{
		disp_clear(0b111111);
		time_mask=1<<(6-timeset_ctr);
		disp_time(time_mask);
		
		/* stop time */
		disable_tick=1;
		
		state_goto(10);
	}
	else
	{
		timeset_ctr=0;
		
		/* start time */
		disable_tick=0;
		
		state_goto(7);
	}
	
}
void time_decrement()
{
	switch (timeset_ctr)
	{
		case 1: dec1y(); break;
		case 2: dec1mth(); break;
		case 3: dec1d(); break;
		case 4: dec1h(); break;
		case 5: dec1min(); break;
		case 6: dec1s(); break;
		default: break;
	}
	disp_time(time_mask);
}
void time_increment()
{
	switch (timeset_ctr)
	{
		case 1: inc1y(); break;
		case 2: inc1mth(); break;
		case 3: inc1d(); break;
		case 4: inc1h(); break;
		case 5: inc1min(); break;
		case 6: inc1s(); break;
		default: break;
	}
	disp_time(time_mask);
}


void init_text(char* str)
{
	time_mask=0b000000;
	disp_clear(0b00111111);
	disp_text(str);
}




void do_nothing()
{
	
}

void state_goto(uint8_t arg)
{
	if(arg!=0xff)
	{
		state=arg;
		states[arg].init(states[arg].init_arg_str);
	}
}

void state_tick()
{
	states[state].tick();
}

void init_states()
{
	/* First clear the whole array */
	for(uint8_t i=0;i<STATES_NUM;i++)
	{
		states[i].init=&do_nothing;
		states[i].tick=&do_nothing;
		
		states[i].btn_down_next[0]=0xff;
		states[i].btn_down_next[1]=0xff;
		states[i].btn_down_next[2]=0xff;
		
		states[i].btn_up_next[0]=0xff;
		states[i].btn_up_next[1]=0xff;
		states[i].btn_up_next[2]=0xff;
	}
	/* State 0 - power saver */
	states[0].init=&init_powersave;
	
	states[0].btn_down_next[2]=1;
	
	
	/* State 1 - minimal mode */
	states[1].init=&init_minmode;
	
	states[1].btn_down_next[0]=0;
	states[1].btn_down_next[2]=2;
	
	
	/* State 2 - full mode */
	states[2].init=&init_fullmode;
	
	states[2].btn_down_next[0]=1;
	states[2].btn_down_next[2]=3;
	
	
	/* State 3 - Fun menu */
	states[3].init=&init_text;
	states[3].init_arg_str="fun";
	
	states[3].btn_down_next[0]=2;
	states[3].btn_down_next[1]=5;
	states[3].btn_down_next[2]=4;
	
	
	/* State 4 - Settings menu*/
	states[4].init=&init_text;
	states[4].init_arg_str="set";
	
	states[4].btn_down_next[0]=3;
	states[4].btn_down_next[1]=7;
	//states[4].btn_down_next[2]=4;
	
	
	/* State 5 - Snake menu*/
	states[5].init=&init_text;
	states[5].init_arg_str="snake";
	
	states[5].btn_down_next[0]=3;
	states[5].btn_down_next[1]=SNAKE_SLOT;
	states[5].btn_down_next[2]=6;
	init_states_snake();
	
	/* State 6 - Other game menu */
	states[6].init=&init_text;
	states[6].init_arg_str="other";
	
	states[6].btn_down_next[0]=5;
	//states[6].btn_down_arg[1]=6;
	//states[6].btn_down_arg[2]=6;		
	
	
	/* State 7 - Time menu */
	states[7].init=&init_text;
	states[7].init_arg_str="time";
	
	states[7].btn_down_next[0]=4;
	states[7].btn_down_next[1]=9;
	states[7].btn_down_next[2]=8;
	
	/* State 8 - Other setting */
	states[8].init=&init_text;
	states[8].init_arg_str="other";
	
	states[8].btn_down_next[0]=7;
	
	/* State 9 - Set time hub */
	states[9].init=&init_time_hub;
	
	/* State 10 - Set time */
	states[10].init=&do_nothing;
	states[10].btn_down_next[0]=11;
	states[10].btn_down_next[1]=9;
	states[10].btn_down_next[2]=12;
	
	/* State 11 - Decrement time */
	states[11].init=&time_decrement;
	states[11].btn_up_next[0]=10;
	
	/* State 12 - Increment time */
	states[12].init=&time_increment;
	states[12].btn_up_next[2]=10;
	
	
	
	
	
		
}

