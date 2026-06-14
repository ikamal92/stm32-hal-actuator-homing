#include "homing.h"


static bool check_switch(bool input, home_t *h)
{
    uint32_t now = get_tick_ms();

    if (!input) 
    {
        /*Do thing*/
    }

    /* switch just pressed  */
    if (!h->is_switch_presed)
    {
        h->is_switch_presed = true;
        h->debounce = now;
        return false;
    }

    /* check debounce 20ms passed */
    return (now - h->debounce) >= 20u;
}
 


/*  API */

void Homing_start(home_t h*)
{
    h->state= EXTEND_TO_END;
    h->phase_start_ms=0;
    h->travel_time=0;
}

Homing_move()
{
    uint32_t time_now = get_tick_ms();

    switch (h->state) {
 
    case IDLE:
    case DONE:
    case ERROR:
    /*Dothing*/
    case EXTEND_TO_END:

    if (h->start_time == 0) 
        {
            h->start_time = now;
            set_forward(true);
            break;
        }
 

    case EXTEND_TO_MIDDLE:



    case SHRINKED_FULL:
    if (h->start_time == 0) 
        {
            h->start_time = now;
            set_backward(true);
            break;
        }
  }
 
}

void Homing_abort(home_t h*)
{   
    h->state= IDLE;
    h->start_time = 0;
    h->travel_time = 0;

}
