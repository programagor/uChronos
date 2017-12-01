#include <avr/io.h>

#include "disp_utils.h"


uint8_t t_y,t_mth,t_d,t_h,t_min,t_s;

static uint8_t t_10ms=0;

void tick10ms()
{
	
	if(++t_10ms==100)
	{
		t_10ms=0;
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
		
		disp_time(time_mask); /* Displayed time needs to be refreshed every second */
	}
}