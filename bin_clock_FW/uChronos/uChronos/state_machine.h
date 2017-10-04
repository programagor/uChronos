#ifndef H_STATE_MACHINE
#define H_STATE_MACHINE

#define STATES_NUM 24

void state_goto(uint8_t arg);

void init_states();

typedef struct
{
	void (*init)();
	char* init_arg;
	uint8_t btn_down_next[3];
	uint8_t btn_up_next[3];
} States;


extern States states[STATES_NUM];
extern uint8_t state;

#endif