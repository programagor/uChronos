#include <avr/io.h>
#include "state_machine.h"

#include "disp_utils.h"



States states[STATES_NUM];
uint16_t state=0;


/* Init function for state 0 (power saver)*/
void init0()
{
	disp_clear(0b00111111);
	time_mask=0;
}
void init1()
{
	disp_clear(0b00111111);
	time_mask=0b110;
}
void init2()
{
	time_mask=0b111111;
}


void do_nothing(uint16_t arg)
{
	
}

void state_goto(uint16_t arg)
{
	state=arg;
	states[state].init();
}

void init_states()
{
	states[0].init=&init0;
	
	states[0].btn_down_fcn[0]=&do_nothing;
	states[0].btn_down_fcn[1]=&do_nothing;
	states[0].btn_down_fcn[2]=&state_goto;
	states[0].btn_down_arg[2]=1;
	
	states[0].btn_up_fcn[0]=&do_nothing;
	states[0].btn_up_fcn[1]=&do_nothing;
	states[0].btn_up_fcn[2]=&do_nothing;
	
	
	states[1].init=&init1;
	
	states[1].btn_down_fcn[0]=&state_goto;
	states[1].btn_down_arg[0]=0;
	states[1].btn_down_fcn[1]=&do_nothing;
	states[1].btn_down_fcn[2]=&state_goto;
	states[1].btn_down_arg[2]=2;
	
	states[1].btn_up_fcn[0]=&do_nothing;
	states[1].btn_up_fcn[1]=&do_nothing;
	states[1].btn_up_fcn[2]=&do_nothing;
	
	
	states[2].init=&init2;
	
	states[2].btn_down_fcn[0]=&state_goto;
	states[2].btn_down_arg[0]=1;
	states[2].btn_down_fcn[1]=&do_nothing;
	states[2].btn_down_fcn[2]=&do_nothing;
	
	states[2].btn_up_fcn[0]=&do_nothing;
	states[2].btn_up_fcn[1]=&do_nothing;
	states[2].btn_up_fcn[2]=&do_nothing;
	
}

