#ifndef H_STATE_MACHINE
#define H_STATE_MACHINE

#define STATES_NUM 24

void state_goto(uint8_t arg);

void init_states();

typedef struct
{
	void (*init)();
	void (*tick)();
	char *init_arg_str;
	uint8_t btn_down_next[3];
	uint8_t btn_up_next[3];
} States;


extern States states[STATES_NUM];
extern uint8_t state;

extern uint8_t disable_tick;

#endif