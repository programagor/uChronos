#ifndef H_STATE_MACHINE
#define H_STATE_MACHINE

#define STATES_NUM 8

void state_goto(uint16_t arg);

void init_states();

typedef struct
{
	void (*init)();
	void (*btn_down_fcn[3])(uint16_t);
	uint16_t btn_down_arg[3];
	void (*btn_up_fcn[3])(uint16_t);
	uint16_t btn_up_arg[3];
} States;


extern States states[STATES_NUM];
extern uint16_t state;

#endif