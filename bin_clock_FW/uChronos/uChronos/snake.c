#include <avr/io.h>

#include "snake.h"
#include "state_machine.h"
#include "disp_utils.h"


uint8_t snake_area[48];/*0=top left;1=top second left;47=bottom right */
uint8_t snake_idx;
uint8_t snake_len;
uint8_t snake_dir; /* 0=up;1=right;2=down;3=left */

void snake_draw()
{
	disp_clear(0b111111);
	for(uint8_t i=0;i<snake_len;i++)
	{
		uint8_t s=snake_area[(snake_idx-i)%48];
		uint8_t p=1<<(3-(s%24)/6);
		disp_mem[s<24?(s/2)%3:((s-24)/2)%3+3]|=s%2?p:p<<4;
	}
}

void snake_init()
{
	snake_idx=1;
	snake_area[0]=27;
	snake_area[1]=28;
	snake_len=2;
	snake_dir=0;
	state_goto(SNAKE_SLOT+1);
}

void snake_left()
{
	snake_dir=(snake_dir-1)%4;
	state_goto(SNAKE_SLOT+1);
}

void snake_right()
{
	snake_dir=(snake_dir+1)%4;
	state_goto(SNAKE_SLOT+1);
}

void snake_advance()
{
	/* Here most of the snake magic happens */
	static uint8_t advance_ctr=0;
	if(++advance_ctr==100)
	{
		advance_ctr=0;
		uint8_t next;
		if /* we hit the walls; remove to allow wrapping */
		(
			(snake_dir==0&&snake_area[snake_idx]<6) ||
			(snake_dir==1&&snake_area[snake_idx]%6==5) ||
			(snake_dir==2&&snake_area[snake_idx]>41) ||
			(snake_dir==3&&snake_area[snake_idx]%6==0)
		)
		{
			state_goto(SNAKE_SLOT+4);
			return;
		}
		switch(snake_dir)
		{
			case 0:
				next=snake_area[snake_idx]-6;
				break;
			case 1:
				next=snake_area[snake_idx]+1;
				break;
			case 2:
				next=snake_area[snake_idx]+6;
				break;
			default:
				next=snake_area[snake_idx]-1;
				break;
		}
		snake_area[snake_idx=(snake_idx+1)%48]=next%48;
		
		for(uint8_t i=1;i<snake_len;i++) /* did we hit the tail? */
		{
			if(snake_area[snake_idx]==snake_area[snake_idx-i])
			{
				state_goto(SNAKE_SLOT+4);
				return;
			}
		}
		snake_draw();
		
	}
}



void init_states_snake()
{
	/* Snake init */
	states[SNAKE_SLOT].init=&snake_init;
	
	/* Snake game */
	states[SNAKE_SLOT+1].tick=&snake_advance;
	states[SNAKE_SLOT+1].btn_down_next[0]=SNAKE_SLOT+2;
	states[SNAKE_SLOT+1].btn_down_next[2]=SNAKE_SLOT+3;
	
	/* Turn left */
	states[SNAKE_SLOT+2].init=&snake_left;
	
	/* Turn right */
	states[SNAKE_SLOT+3].init=&snake_right;
	
	/* Game over */
	states[SNAKE_SLOT+4].init=&init_text;
	states[SNAKE_SLOT+4].init_arg_str="over";
	states[SNAKE_SLOT+4].btn_down_next[1]=5;
	
	
}