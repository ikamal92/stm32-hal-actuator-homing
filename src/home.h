#ifndef HOME_H
#define HOME_H

#define DEBOUNCE  20u       
#define TIMEOUT  10000u    


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
    unsigned int debounce;
    bool is_switch_presed;
} home_t;

/*  API */

void Homing_start(home_t h*);


void Homing_move(home_t h*);

void Homing_abort(home_t h*);

#endif 
