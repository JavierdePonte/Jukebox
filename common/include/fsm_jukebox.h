/**
 * @file fsm_jukebox.h
 * @brief Header for fsm_jukebox.c file.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Mac Afee
 * @date 14/05/2024
 */
#ifndef FSM_JUKEBOX_H_
#define FSM_JUKEBOX_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <fsm.h>
#include "melodies.h"

/* Other includes */


/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define MELODIES_MEMORY_SIZE 6 /*!< Array of melodies length*/

/* Enums */
/**
 * @brief Enumerator for the Jukebox finite state machine.
 * This enumerator defines the different states that the Jukebox finite state machine can be in. Each state represents a specific 
 * condition or step in the playing process of the Jukebox.
 * 
 */
enum FSM_JUKEBOX {
  OFF = 0, /*!< Starting state. Also comes here when the button has been pressed for the required time to turn OFF the Jukebox*/
  START_UP, /*!< State to play the intro melody and initialize the Jukebox*/
  WAIT_COMMAND, /*!< State to wait for a command from the USART*/
  SLEEP_WHILE_OFF, /*!< State to start the low power mode while the Jukebox is OFF*/
  SLEEP_WHILE_ON, /*!< State to start the low power mode while the Jukebox is ON*/
  PLAYING_LAST_SONG /*!< State to play the final song before turning off*/
  
};

/* Typedefs ------------------------------------------------------------------*/
/**
 * @brief Structure that contains the information of a melody.
 * 
 */
typedef struct {
fsm_t f; /*!< Jukebox FSM*/
melody_t melodies [MELODIES_MEMORY_SIZE]; /*!< Array of melody names of size MELODIES_MEMORY_SIZE*/
uint8_t melody_idx; /*!< Index of the melody to playing*/
char *p_melody; /*!< Pointer to the name of the melody playing*/
fsm_t *p_fsm_button; /*!< Pointer to the button FSM*/
uint32_t on_off_press_time_ms; /*!< Time in ms to consider ON/OFF*/
fsm_t *p_fsm_usart; /*!< Pointer to the USART FSM*/
fsm_t *p_fsm_buzzer; /*!< Pointer to the buzzer FSM*/
uint32_t next_song_press_time_ms; /*!< Time in ms to consider next song*/
double 	speed; /*!< Speed of the melody playing*/
} fsm_jukebox_t;

/* Function prototypes and explanation ---------------------------------------*/
/**
 * @brief Create a new jukebox FSM.
 * 
 * @param p_fsm_button 
 * @param on_off_press_time_ms 
 * @param p_fsm_usart 
 * @param p_fsm_buzzer 
 * @param next_song_press_time_ms 
 * @return fsm_t* 
 */
fsm_t * fsm_jukebox_new (fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms);

/**
 * @brief Initialize a jukebox FSM.
 * 
 * @param p_this 
 * @param p_fsm_button 
 * @param on_off_press_time_ms 
 * @param p_fsm_usart 
 * @param p_fsm_buzzer 
 * @param next_song_press_time_ms 
 */
void fsm_jukebox_init (fsm_t *p_this, fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms);


#endif /* FSM_JUKEBOX_H_ */