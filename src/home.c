#include "homing.h"




/*  API */

void Homing_start(home_t h*)
{
    h->state= EXTEND_TO_END;
    h->phase_start_ms=0;
    h->full_travel_ms=0;
}

Homing_move()
{
    switch (h->state) {
 
    case IDLE:
    case EXTEND_TO_END:
    case EXTEND_TO_MIDDLE:
    case SHRINKED_FULL:
    case DONE:
    case ERROR:


  }
 
}

void Homing_abort(home_t h*)
{   
    h->state= IDLE;
    h->phase_start_ms = 0;
    h->full_travel_ms = 0;

}
