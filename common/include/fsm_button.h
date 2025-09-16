/**
 * @file fsm_button.h
 * @brief Header for fsm_button.c file.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Mac Afee
 * @date 18/03/2024
 */

#ifndef FSM_BUTTON_H_
#define FSM_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
/* Other includes */
#include "fsm.h"

/* Defines and enums ----------------------------------------------------------*/
/* Enums */ 
/**
 * @brief States of the finite state machine of the button
 * 
 */
enum FSM_BUTTON {
  BUTTON_RELEASED = 0,  /*!< Starting state. Constantly looking for a falling edge. If the button is pressed (falling edge) saves time and calculates next timeout */
  BUTTON_RELEASED_WAIT, /*!< Waits debounce_time ms. Maintains in this state until actual time is higher than the timeout. Returns null */
  BUTTON_PRESSED, /*!< While button is pressed. Maintains in this state until it detects a rising edge. Calculates the duration of the button press */
  BUTTON_PRESSED_WAIT /*!<  Waits debounce_time ms. Maintains in this state until actual time is higher than the timeout. Returns null */
};

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure of a button FSM
 * 
 */
typedef struct {
    fsm_t f;  /*!< Button FSM */
    uint32_t debounce_time;  /*!< Button debounce time in ms */
    uint32_t next_timeout; /*!< Next timeout for the debounce in ms */
    uint32_t tick_pressed; /*!< Number of system ticks when the button was pressed*/
    uint32_t duration; /*!< Duration of the button press */
    uint32_t button_id; /*!< Button identifier */
} fsm_button_t;


/* Function prototypes and explanation -------------------------------------------------*/

/**
 * @brief Creates a new button FSM
 * 
 * @param debounce_time 
 * @param button_id 
 * @return fsm_t* 
 */
fsm_t * fsm_button_new (uint32_t debounce_time, uint32_t button_id); 

/**
 * @brief Initialize a button FSM
 * 
 * @param p_this 
 * @param debounce_time 
 * @param button_id 
 */
void 	fsm_button_init (fsm_t *p_this, uint32_t debounce_time, uint32_t button_id);

/**
 * @brief Returns the duration of the last button press
 * 
 * @param p_this 
 * @return uint32_t 
 */
uint32_t 	fsm_button_get_duration (fsm_t *p_this);

/**
 * @brief Resets the duration field
 * 
 * @param p_this 
 */
void 	fsm_button_reset_duration (fsm_t *p_this);

/**
 * @brief Checks if the button FSM is active or not
 * 
 * @param p_this 
 * @return true 
 * @return false 
 */
bool 	fsm_button_check_activity (fsm_t *p_this);

#endif
