#include <avr/io.h>

uint8_t t_y,t_mth,t_d,t_h,t_min,t_s;


void tick10ms(){
	
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
}