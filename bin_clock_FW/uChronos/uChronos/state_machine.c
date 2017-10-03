#include <avr/io.h>
#include "state_machine.h"

#include "disp_utils.h"



States states[STATES_NUM];
uint8_t state=0;


/* Init functions*/
void init0()
{
	time_mask=0;
	disp_clear(0b00111111);
	disp_time(time_mask);
}
void init1()
{
	time_mask=0b110;
	disp_clear(0b00111111);
	disp_time(time_mask);
}
void init2()
{
	time_mask=0b111111;
	disp_time(time_mask);
}
void init3()
{
	time_mask=0b000000;
	disp_clear(0b00111111);
	disp_text("fun");
}
void init4()
{
	time_mask=0b000000;
	disp_clear(0b00111111);
	disp_text("set");
}
void init5()
{
	time_mask=0b000000;
	disp_clear(0b00111111);
	disp_text("snake");
}
void init6()
{
	time_mask=0b000000;
	disp_clear(0b00111111);
	disp_text("other");
}



void do_nothing(uint8_t arg)
{
	
}

void init_nothing()
{
	
}

void state_goto(uint8_t arg)
{
	if(arg!=0xff)
	{
		state=arg;
		states[state].init();
	}
}

void init_states()
{
	/* First clear the whole array */
	for(uint8_t i=0;i<STATES_NUM;i++)
	{
		states[i].init=&init_nothing;
		
		states[i].btn_down_arg[0]=0xff;
		states[i].btn_down_arg[1]=0xff;
		states[i].btn_down_arg[2]=0xff;
		
		states[i].btn_up_arg[0]=0xff;
		states[i].btn_up_arg[1]=0xff;
		states[i].btn_up_arg[2]=0xff;
	}
	/* State 0 */
	states[0].init=&init0;
	
	states[0].btn_down_arg[2]=1;
	
	
	/* State 1 */
	states[1].init=&init1;
	
	states[1].btn_down_arg[0]=0;
	states[1].btn_down_arg[2]=2;
	
	
	/* State 2 */
	states[2].init=&init2;
	
	states[2].btn_down_arg[0]=1;
	states[2].btn_down_arg[2]=3;
	
	
	/* State 3 */
	states[3].init=&init3;
	
	states[3].btn_down_arg[0]=2;
	states[3].btn_down_arg[1]=5;
	states[3].btn_down_arg[2]=4;
	
	
	/* State 4 */
	states[4].init=&init4;
	
	states[4].btn_down_arg[0]=3;
	//states[4].btn_down_arg[1]=4;
	//states[4].btn_down_arg[2]=4;
	
	
	/* State 5 */
	states[5].init=&init5;
	
	states[5].btn_down_arg[0]=3;
	states[5].btn_down_arg[1]=7;
	states[5].btn_down_arg[2]=6;
	
	/* State 6 */
	states[6].init=&init6;
	
	states[6].btn_down_arg[0]=5;
	//states[6].btn_down_arg[1]=6;
	//states[6].btn_down_arg[2]=6;
		
}

