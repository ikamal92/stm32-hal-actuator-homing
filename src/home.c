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
 
static bool timed_out(const Homing_t *h)
{
    return (get_tick_ms() - h->phase_start_ms) >= 10000u;
}

/*  API */

void Homing_start(home_t h*)
{
    h->state= EXTEND_TO_END;
    h->start_time =0;
    h->travel_time=0;
    h->debounce = 0;
    h->is_switch_presed=false;
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

       if (h->start_time  == 0) {
            h->start_time  = now;
            set_backward(true);
            break;
        }
        if ((get_tick_ms() - h->phase_start_ms) >= 10000u) /* timeout*/
        {
            h->state = HOMING_ERROR;
            break;
        }
       if (check_switch(read_forward_switch(), h)) {
            h->state= SHRINKED_FULL;
            h->phase_start_ms = 0;
        }
        break;

    case EXTEND_TO_MIDDLE:

        if (h->start_time  == 0) 
        {
            h->start_time  = now;
            set_forward(true);
            break;
        }

        if ((get_tick_ms() - h->phase_start_ms) >= 10000u) /* timeout*/
        {
            h->state = HOMING_ERROR;
            break;
        }

        {
        unsigned int passed = now - h->start_time ;
        unsigned int target_mid  = h->travel_time / 2u;
 
        if ( passed >= target_mid) 
        {
            h->state =  HOMING_DONE;
        }
        }
        break;

    case SHRINKED_FULL:
        if (h->start_time  == 0) {
            h->start_time  = now;
            set_backward(true);
            break;
        }

        if ((get_tick_ms() - h->phase_start_ms) >= 10000u) /* timeout*/
        {
            h->state = HOMING_ERROR;
            break;
        }

 
        if (check_switch(read_backward_switch(), h)) {
            h->travel_time = now - h->start_time;
            h->state= HOMING_FORWARD_TO_MIDDLE;
            h->start_time  = 0;
        }
        break;
  }
 
}

void Homing_abort(home_t h*)
{   
    h->state= IDLE;
    h->start_time = 0;
    h->travel_time = 0;

}
