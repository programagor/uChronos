#include <avr/io.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "disp_utils.h"
#include "bin_utils.h"

uint8_t disp_mem[6]={0};

static uint8_t disp_ctr=0;

uint8_t time_mask=0b111111;

const char alphabet[] PROGMEM =
{
	0b10000000,
	0b11000000,
	0b10001000,
	0b10001100,
	0b10000100,
	0b11001000,
	0b11001100,
	0b11000100,
	0b01001000,
	0b01001100,
	0b10100000,
	0b11100000,
	0b10101000,
	0b10101100,
	0b10100100,
	0b11101000,
	0b11101100,
	0b11100100,
	0b01101000,
	0b01101100,
	0b10100010,
	0b11100010,
	0b01001110,
	0b10101010,
	0b10101110,
	0b10100110
};

void disp_refresh()
{
	PORTD=0b00000000;
	PORTC=0b00111111;
	
	PORTC=0b00111111^(1<<disp_ctr);
	PORTD=disp_mem[disp_ctr];
	disp_ctr=(disp_ctr+1)%6;

}

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

void disp_text(char str[])
{
	uint8_t len=strlen(str);
	len=len>6?6:len;
	for(uint8_t c=0;c<len;c++)
	{
		disp_mem[c]=pgm_read_byte(&alphabet[str[c]-'a']);
	}
}


