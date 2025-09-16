/**
 * @file fsm_buzzer.h
 * @brief Header for fsm_buzzer.c file.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Mac Afee
 * @date 30/04/2024
 */

#ifndef FSM_BUZZER_H_
#define FSM_BUZZER_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include <fsm.h>
#include "melodies.h"

/* Other includes */

/* HW dependent includes */


/* Defines and enums ----------------------------------------------------------*/
/* Enums */
/**
 * @brief Enumerator for the buzzer finite state machine.
 * \n
 * This enumerator defines the different states that the buzzer finite state machine can be in.
 * Each state represents a specific condition or step in the buzzer playing process.
 * 
 */
enum FSM_BUZZER {
  WAIT_START = 0, /*!< Starting state. Also comes here when a melody has been played*/ 
  PLAY_NOTE, /*!< State to play a note*/
  PAUSE_NOTE, /*!< State to pause the player*/
  WAIT_NOTE, /*!< State to wait for the duration of the note*/
  WAIT_MELODY /*!< State to wait for a new melody*/
};

/**
 * @brief Enumeration of possible states actions on the player, either from the user or from the player itself.
 * 
 */
enum USER_ACTIONS {
  STOP = 0, /*!< Player is stopped or requested to stop */
  PLAY, /*!< Player is playing or requested to play */
  PAUSE /*!<  Player is requested to pause*/
};
 

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure to define the Buzzer FSM.
 * 
 */
typedef struct {
    fsm_t f; /*!< Buzzer melody player FSM*/
    melody_t *p_melody; /*!< Pointer to the melody to play*/
    uint32_t note_index; /*!< Index of the current note of the melody to play*/
    uint8_t buzzer_id; /*!< Buzzer melody player ID. Must be unique. */
    uint8_t user_action; /*!< Action to perform on the player. Can indicate if the user has stopped, paused or started the player, or if the player has stopped itself*/
    double player_speed; /*!< Speed of the player. 1.0 is normal speed. 0.5 is half speed. 2.0 is double speed*/
} fsm_buzzer_t;

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Set the melody to play. \n
 * This function sets the melody to play. The user must pass a pointer to the melody to play.
 * 
 * @param p_this 	Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param p_melody Pointer to the melody to play
 */
void fsm_buzzer_set_melody (fsm_t *p_this, const melody_t *p_melody);

/**
 * @brief 
 * Set the speed of the player. \n 
 * This function sets the speed of the player. 
 * The user must pass a double value with the speed of the player.
 * 
 * @param p_this 	Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param speed Speed of the player
 */
void fsm_buzzer_set_speed (fsm_t *p_this, double speed);

/**
 * @brief Set the action to perform on the player. \n 
 * This function sets the action to perform on the player. 
 * The user must pass a USER_ACTIONS value with the action desired. These serve as flags to indicate if the user has stopped, paused or started the player, or if the player has stopped itself.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param action Action to perform on the player
 */
void fsm_buzzer_set_action (fsm_t *p_this, uint8_t action);

/**
 * @brief Get the action of the user. \n 
 * This function returns the action performed on the player. This is useful to know if the 
 * player is playing, paused or stopped and a melody has ended.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @return uint8_t Action to perform on the player.
 */
uint8_t fsm_buzzer_get_action (fsm_t *p_this);

/**
 * @brief Creates a new buzzer finite state machine.
 * 
 * @param buzzer_id Unique buzzer identifier number.
 * @return fsm_t* A pointer to the new buzzer finite state machine.
 */
fsm_t * fsm_buzzer_new (uint32_t buzzer_id);

/**
 * @brief Initialize a buzzer finite state machine. \n 
 * This function initializes the default values of the FSM
 *  struct and calls to the port to initialize the HW of associated to the given ID.
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param buzzer_id Unique buzzer identifier number.
 */
void fsm_buzzer_init (fsm_t *p_this, uint32_t buzzer_id);

/**
 * @brief Check if the buzzer finite state machine is playing a melody.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @return true 
 * @return false 
 */
bool fsm_buzzer_check_activity (fsm_t *p_this);

#endif /* FSM_BUZZER_H_ */