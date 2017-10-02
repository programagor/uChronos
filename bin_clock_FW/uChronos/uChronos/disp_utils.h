#ifndef H_DISP_UTILS
#define H_DISP_UTILS

extern uint8_t disp_mem[];
extern uint8_t t_y,t_mth,t_d,t_h,t_min,t_s;

extern uint8_t time_mask;

void disp_fill(uint8_t mask);
void disp_clear(uint8_t mask);
void disp_time(uint8_t mask);

#endif