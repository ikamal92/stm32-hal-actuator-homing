#include "homing.h"


static bool check_switch(bool input, home_t *h)
{
    uint32_t now = get_tick_ms();

    if (!input) 
    {   
        /*reset debounce*/
        h->is_switch_presed = false;
        h->debounce = 0;

        return false;
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
    h->start_time =0;
    h->travel_time=0;
    h->debounce = 0;
    h->is_switch_presed=false;
}

void Homing_move(home_t h*)
{
    uint32_t now= get_tick_ms();

    switch (h->state) {
 
    case IDLE:
    case DONE:
    case ERROR:
         set_forward(false);
         set_backward(false);
        break;
    case EXTEND_TO_END:

       if (h->start_time  == 0) 
       {
            h->start_time = now;
            h->is_switch_presed = false;
            h->debounce = 0;
            set_backward(false);
            set_forward(true);
            break;
        }
        if ((get_tick_ms() - h->start_time) >= TIMEOUT) /* timeout*/
        {   set_forward(false);
            h->state = HOMING_ERROR;
            break;
        }
       if (check_switch(read_extended_switch(), h)) {

            /* next step*/
            h->state= SHRINKED_FULL;
            h->start_time = 0;
        }
        break;

    case EXTEND_TO_MIDDLE:

        if (h->start_time  == 0) 
        {
            h->start_time  = now;
            h->is_switch_presed = false;
            h->debounce = 0;
            set_backward(false);
            set_forward(true);
            break;
        }

        if ((get_tick_ms() - h->start_time) >= TIMEOUT) /* timeout*/
        {
            h->state = HOMING_ERROR;
            set_forward(false);
            break;
        }

        {
        unsigned int passed = now - h->start_time ;
        unsigned int target_mid  = h->travel_time / 2u;
 
        if ( passed >= target_mid) 
        {   set_forward(false);
            h->state =  HOMING_DONE;
        }
        }
        break;

    case SHRINKED_FULL:
        if (h->start_time  == 0) {
            h->start_time  = now;
            h->is_switch_presed = false;
            h->debounce = 0;
            set_forward(false);
            set_backward(true);
            break;
        }

        if ((get_tick_ms() - h->start_time) >= TIMEOUT) /* timeout*/
        {
            set_backward(false);
            h->state = HOMING_ERROR;
            break;
        }

 
        if (check_switch(read_SHRINKED_switch(), h)) {
            h->travel_time = now - h->start_time;
            /* next step*/
            h->state= HOMING_FORWARD_TO_MIDDLE; 
            h->start_time  = 0;
        }
        break;
  }
 
}

void Homing_abort(home_t h*)
{   
    h->state= IDLE;
    set_forward(false);
    set_backward(false);
    h->start_time = 0;
    h->travel_time = 0;

}
