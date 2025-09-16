/**
 * @file fsm_button.c
 * @brief Button FSM main file.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Macafee
 * @date 18/03/2024
 */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "fsm_button.h"
#include "port_button.h"


/* State machine input or transition functions */


/* State machine output or action functions */


/* Other auxiliary functions */

fsm_t *fsm_button_new(uint32_t debounce_time, uint32_t button_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_button_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_button_init(p_fsm, debounce_time, button_id);
    return p_fsm;
}



/**
 * @brief Check if the button has been pressed
 * 
 * @param p_this Pointer to an fsm_t struct that contains a [fsm_button_t](structfsm__button__t.html)
 * @return true 
 * @return false 
 */
static bool check_button_pressed ( fsm_t *  p_this	) {
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    bool status = port_button_is_pressed(p_fsm -> button_id);
    return status;
}	

/**
 * @brief Check if the button has been released
 * 
 * @param p_this Pointer to an fsm_t struct that contains a [fsm_button_t](structfsm__button__t.html)
 * @return true 
 * @return false 
 */
static bool check_button_released ( fsm_t * p_this ) {
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    bool status = port_button_is_pressed(p_fsm -> button_id);
    return !status;
}

/**
 * @brief Check if the debounce time has passed
 * 
 * @param p_this Pointer to an fsm_t struct that contains a [fsm_button_t](structfsm__button__t.html)
 * @return true 
 * @return false 
 */
static bool check_timeout ( fsm_t * p_this ) {
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    uint32_t current_system_tick = port_button_get_tick();
    if(current_system_tick > (p_fsm -> next_timeout)){
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Store the system tick when the button was pressed
 * 
 * @param p_this Pointer to an fsm_t struct that contains a [fsm_button_t](structfsm__button__t.html)
 * @return * void 
 */
static void do_store_tick_pressed (fsm_t * p_this) {
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    p_fsm -> tick_pressed = port_button_get_tick();
    p_fsm -> next_timeout = p_fsm -> tick_pressed + p_fsm -> debounce_time;
} 	

/**
 * @brief Store the duration of the button press
 * 
 * @param p_this Pointer to an fsm_t struct that contains a [fsm_button_t](structfsm__button__t.html)
 */
static void do_set_duration ( fsm_t * p_this ) {
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    uint32_t current = port_button_get_tick();
    p_fsm -> duration = (current - p_fsm -> tick_pressed);
    p_fsm -> next_timeout = (current + p_fsm -> debounce_time);
}
/**
 * @brief Array representing the transitions table of the FSM button 
 * ![](docs\assets\imgs\tabla_transiciones_Jukebox.PNG)
 * 
 */
static fsm_trans_t fsm_trans_button [] = { 
    {BUTTON_RELEASED, check_button_pressed, BUTTON_PRESSED_WAIT, do_store_tick_pressed},
    {BUTTON_PRESSED_WAIT, check_timeout, BUTTON_PRESSED, NULL},
    {BUTTON_PRESSED, check_button_released, BUTTON_RELEASED_WAIT, do_set_duration},
    {BUTTON_RELEASED_WAIT, check_timeout, BUTTON_RELEASED, NULL},
    {-1, NULL, -1, NULL}
};


uint32_t fsm_button_get_duration ( fsm_t * p_this) {
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    return p_fsm -> duration;
}	


void fsm_button_reset_duration ( fsm_t * p_this) {
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    p_fsm -> duration = 0;
}	


void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    fsm_init(p_this, fsm_trans_button);
    p_fsm -> debounce_time = debounce_time;
    p_fsm -> button_id = button_id;
    p_fsm -> tick_pressed = 0;
    p_fsm -> duration = 0;
    port_button_init (button_id);
}


bool fsm_button_check_activity(fsm_t *p_this){
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);

    // Get the field current_state of the FSM
    int current_state = (p_fsm -> f.current_state);
    
    // return false if it is BUTTON_RELEASED
    if(current_state == BUTTON_RELEASED){
        return false;
    } else {
        return true;
    }

}



