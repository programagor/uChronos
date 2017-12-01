#include <avr/io.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "state_machine.h"

#include "disp_utils.h"



States states[STATES_NUM];
uint8_t state;


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


void init_states()
{
	/* First clear the whole array */
	for(uint8_t i=0;i<STATES_NUM;i++)
	{
		states[i].init=&do_nothing;
		
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
	states[5].btn_down_next[1]=7;
	states[5].btn_down_next[2]=6;
	
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
	
	/* State 9 - Set Year */
	states[9].init=&do_nothing;
	states[9].btn_down_next[1]=10;
	
	/* State 10 - Set Month */
	states[10].init=&do_nothing;
	states[10].btn_down_next[1]=11;
	
	/* State 11 - Set Day */
	states[11].init=&do_nothing;
	states[11].btn_down_next[1]=12;
	
	/* State 12 - Set Hour */
	states[12].init=&do_nothing;
	states[12].btn_down_next[1]=13;
	
	/* State 13 - Set minute */
	states[13].init=&do_nothing;
	states[13].btn_down_next[1]=14;
	
	/* State 14 - Set seconds */
	states[14].init=&do_nothing;
	states[14].btn_down_next[1]=7; /* Back to time menu */
	
	
	
		
}

