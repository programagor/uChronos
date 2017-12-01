#ifndef H_TIME_UTILS
#define H_TIME_UTILS

extern uint8_t t_y,t_mth,t_d,t_h,t_min,t_s;

void tick10ms();

void inc1s();
void inc1min();
void inc1h();
void inc1d();
void inc1mth();
void inc1y();

void dec1s();
void dec1min();
void dec1h();
void dec1d();
void dec1mth();
void dec1y();

#endif