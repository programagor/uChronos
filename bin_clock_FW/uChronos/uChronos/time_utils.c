#include <avr/io.h>

#include "disp_utils.h"
#include "time_utils.h"
#include "state_machine.h"


uint8_t t_y,t_mth,t_d,t_h,t_min,t_s;



void tick10ms()
{
	static uint8_t t_10ms=0;
	if(++t_10ms==100)
	{
		t_10ms=0;
		if(!disable_tick)inc1s();
		
		disp_time(time_mask); /* Displayed time needs to be refreshed every second */
	}
}

void inc1s()
{
	if(++t_s==60)
	{
		t_s=0;
		inc1min();
	}
}

void inc1min()
{
	if(++t_min==60)
	{
		t_min=0;
		inc1h();
	}
}

void inc1h()
{
	
	if(++t_h==24)
	{
		t_h=0;
		inc1d();
	}
}

uint8_t mthlen()
{
	if(t_mth==1||t_mth==3||t_mth==5||t_mth==7||t_mth==8||t_mth==10||t_mth==12) return(31);
	if(t_mth!=2) return(30);
	if((t_y % 4) || ((t_y % 100 == 0) && (t_y % 400))) return(28);
	return(29);
}

void inc1d()
{
	
	if(t_d==mthlen())
	{
		t_d=1;
		inc1mth();
	}
	else
	{
		t_d++;
	}
}

void inc1mth()
{
	if(++t_mth==13)
	{
		t_mth=1;
		inc1y();
	}
}

void inc1y()
{
	t_y=(t_y+1)%100;
}


void dec1s()
{
	if(t_s--==0)
	{
		t_s=59;
		dec1min();
	}
}

void dec1min()
{
	if(t_min--==0)
	{
		t_min=59;
		dec1h();
	}
}

void dec1h()
{
	if(t_h--==0)
	{
		t_h=23;
		dec1d();
	}
}

void dec1d()
{
	if(t_d--==1)
	{
		dec1mth();
		t_d=mthlen();
	}
}

void dec1mth()
{
	if(t_mth--==1)
	{
		t_mth=12;
		dec1y();
	}
}

void dec1y()
{
	t_y=(t_y-1)%100;
}