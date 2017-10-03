#ifndef H_STATE_MACHINE
#define H_STATE_MACHINE

#define STATES_NUM 16

void state_goto(uint8_t arg);

void init_states();

typedef struct
{
	void (*init)();
	void (*btn_down_fcn[3])(uint8_t arg);
	uint8_t btn_down_arg[3];
	void (*btn_up_fcn[3])(uint8_t arg);
	uint8_t btn_up_arg[3];
} States;


extern States states[STATES_NUM];
extern uint8_t state;

#endif