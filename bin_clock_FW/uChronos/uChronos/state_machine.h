#ifndef H_STATE_MACHINE
#define H_STATE_MACHINE

typedef enum
{
	MINIMAL_TIME,
	FULL_TIME,
	SLEEPING
} State;

extern State state;

#endif