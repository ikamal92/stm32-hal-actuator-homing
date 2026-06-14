#ifndef HOME_H
#define HOME_H


typedef enum {
    IDLE = 0,
    EXTEND_TO_END,   /*forward*/
    SHRINKED_FULL,  /*backwards*/  
    EXTEND_TO_MIDDLE, /*middle*/
    DONE,
    ERROR
} state_t;




/*  API */

void Homing_start();


void Homing_move();

void Homing_abort();

#endif 
