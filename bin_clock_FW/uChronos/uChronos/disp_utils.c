#include <avr/io.h>
#include "disp_utils.h"
#include "bin_utils.h"

uint8_t disp_mem[6]={0};
uint8_t t_y,t_mth,t_d,t_h,t_min,t_s;

uint8_t time_mask=0b111111;

void disp_fill(uint8_t mask)
{
	for (uint8_t i=0;i<6;i++)
	{
		if(mask&(1<<i)) disp_mem[i]=0xff;
	}
}

void disp_clear(uint8_t mask)
{
	for (uint8_t i=0;i<6;i++)
	{
		if(mask&(1<<i)) disp_mem[i]=0x00;
	}
}

void disp_time(uint8_t mask)
{
	if(mask&(1<<0)) disp_mem[5]=bin2bcd(t_s);
	if(mask&(1<<1)) disp_mem[4]=bin2bcd(t_min);
	if(mask&(1<<2)) disp_mem[3]=bin2bcd(t_h);
	if(mask&(1<<3)) disp_mem[2]=bin2bcd(t_d);
	if(mask&(1<<4)) disp_mem[1]=bin2bcd(t_mth);
	if(mask&(1<<5)) disp_mem[0]=bin2bcd(t_y);
}