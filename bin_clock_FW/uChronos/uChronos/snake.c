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
		/* this code goes through all segments of the tail, and writes them onto display 
		
		
		Sequence number    ->    Display memory
		 0  1  2  3  4  5        a7 a3 b7 b3 c7 c3
		 6  7  8  9 10 11        a6 a2 b6 b2 c6 c2
		12 13 14 15 16 17        a5 a1 b5 b1 c5 c1
		18 19 20 21 22 23        a4 a0 b4 b0 c4 c0

		24 25 26 27 28 29        d7 d3 e7 e3 f7 f3
		30 31 32 33 34 35        d6 d2 e6 e2 f6 f2
		36 37 38 39 40 41        d5 d1 e5 e1 f5 f1
		42 43 44 45 46 47        d4 d0 e4 e0 f4 f0

		disp_mem[0]=a
		..
		disp_mem[5]=f

		
		*/
		
		uint8_t s=snake_area[(snake_idx-i+48)%48];
		disp_mem[s<24?(s/2)%3:((s-24)/2)%3+3]|=1<<(3-(s%24)/6)<<(s%2?0:4);
	}
}

void snake_init()
{
	snake_idx=0;
	snake_area[42]=8;
	snake_area[43]=9;
	snake_area[44]=10;
	snake_area[45]=11;
	snake_area[46]=5;
	snake_area[47]=4;
	snake_area[0]=3;
	//snake_area[1]=2;
	snake_len=7;
	snake_dir=3;
	state_goto(SNAKE_SLOT+1);
}

void snake_left()
{
	snake_dir=(snake_dir-1+4)%4;
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
			case 3:
			default:
				next=snake_area[snake_idx]-1;
				break;
		}
		snake_area[snake_idx=(snake_idx+1)%48]=(next+48)%48;
		
		for(uint8_t i=1;i<snake_len;i++) /* did we hit the tail? */
		{
			if(snake_area[snake_idx]==snake_area[(snake_idx-i+48)%48])
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