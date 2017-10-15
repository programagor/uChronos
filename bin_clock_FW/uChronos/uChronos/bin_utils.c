#include <avr/io.h>
#include "bin_utils.h"

uint8_t bin2bcd(uint8_t bin)
{
	return (bin%10)|(bin/10)<<4;
}