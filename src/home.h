#ifndef HOME_H
#define HOME_H


typedef enum {
    IDLE = 0,
    EXTEND_TO_END,   /*forward*/
    EXTEND_TO_MIDDLE, /*middle*/
    SHRINKED_FULL,     /*backwards*/  
    DONE,
    ERROR
} state_t;



typedef struct {
    state_t state;
    unsigned int start_time;
    unsigned int travel_time;
} home_t;

/*  API */

void Homing_start();


void Homing_move();

void Homing_abort();

#endif 
