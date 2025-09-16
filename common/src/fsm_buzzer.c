/**
 * @file fsm_buzzer.c
 * @brief Buzzer melody player FSM main file.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Macafee
 * @date 15/04/2024
 */

/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <stdlib.h>
#include "port_buzzer.h"
#include "fsm_buzzer.h"
#include "melodies.h"
/* Other libraries */

/* State machine input or transition functions */

/**
 * @brief 
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 * @param freq 
 * @param duration 
 */
static void _start_note	(fsm_t *p_this, double freq, uint32_t duration) {
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    double duration2 = (double)duration/(p_fsm -> player_speed);
    port_buzzer_set_note_frequency (p_fsm -> buzzer_id, freq);
    port_buzzer_set_note_duration (p_fsm -> buzzer_id, (uint32_t) duration2);
}

/**
 * @brief Check a melody is set to start.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 * @return true 
 * @return false 
 */
static bool check_melody_start	(fsm_t *p_this) {
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    if ((p_fsm -> p_melody != NULL) && (p_fsm -> user_action == PLAY)) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Check if the player is set to start.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 * @return true 
 * @return false 
 */
static bool check_player_start	(fsm_t *p_this)	{
    
    return check_melody_start(p_this);
}

/**
 * @brief Check if it has been reached the end of the melody.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 * @return true 
 * @return false 
 */
static bool check_end_melody(fsm_t * p_this	){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    if ((p_fsm->note_index) < (p_fsm->p_melody->melody_length)){
        return false;
    }
    else{
        return true;
    }
}	

/**
 * @brief Check if the note has ended.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 * @return true 
 * @return false 
 */
static bool check_note_end	(	fsm_t * 	p_this	)	{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return port_buzzer_get_note_timeout(p_fsm->buzzer_id);
}


/**
 * @brief Check if the player is set to pause.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.

 * @return true 
 * @return false 
 */
static bool check_pause	(	fsm_t * 	p_this	)	{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    if(p_fsm->user_action == PAUSE){
        return true;
    }
    else{
        return false;
    }
}

/**
 * @brief Check if the player is set to play a note.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 * @return true 
 * @return false 
 */

static bool check_play_note	(	fsm_t * 	p_this	)	{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    if((p_fsm->user_action == PLAY) && (check_end_melody(p_this) == false)){
        return true;
    }
    else{
        return false;
    }
}


/**
 * @brief Check if the player is set to stop.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 * @return true 
 * @return true 
 * @return false 
 */
static bool check_player_stop	(	fsm_t * 	p_this	){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    if(p_fsm->user_action == STOP){
        return true;
    }
    else{
        return false;
    }
}


/**
 * @brief Check if the player is set to play.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 * @return true 
 * @return true 
 * @return false 
 */
static bool check_resume (	fsm_t * 	p_this	){
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    if(p_fsm->user_action == PLAY){
        return true;
    }
    else{
        return false;
    }
}




/* State machine output or action functions */
/**
 * @brief Stop the player. \n 
 * This function stops the player by stopping the PWM and the timer. This function is called when the player is set to stop.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 */
static void do_end_melody	(	fsm_t * 	p_this	)	{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    port_buzzer_stop(p_fsm -> buzzer_id);
    p_fsm ->note_index = 0;
    p_fsm ->user_action = STOP;
}

/**
 * @brief Start a melody. \n 
 * This function starts a melody player by setting the PWM frequency and the timer duration of the first note. This function is called when the player is set to play only.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 */
static void do_melody_start	(fsm_t *p_this)	{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    double freq = p_fsm -> p_melody -> p_notes[0];
    uint32_t duration = p_fsm -> p_melody -> p_durations[0];
    _start_note(p_this, freq, duration);
    p_fsm -> note_index++;
}

/**
 * @brief End the note. \n 
 * This function ends the note by stopping the PWM and the timer. This function is called when the note has ended.
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 */
static void do_note_end	(fsm_t *p_this)	{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    port_buzzer_stop(p_fsm -> buzzer_id);
}

/**
 * @brief Pause the player. \n 
 * This function pauses the player by stopping the PWM and the timer. This function is called when the player is set to pause.
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 */
static void do_pause (fsm_t *p_this) {
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    port_buzzer_stop(p_fsm -> buzzer_id);
}

/**
 * @brief Update the player with a new note. \n 
 * This function updates the player retrieving the frequency and the duration of the next note of the melody. This function is called when the player is set to play a new note.
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 */

static void do_play_note (fsm_t *p_this) {

    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);

    // conseguir la frecuencia de la siguiente nota
    
    //recuperar indice de la nota actual
    
    uint32_t actual_note_index = (p_fsm -> note_index);

    //indice de la nota siguiente
    // uint32_t next_note_index = (actual_note_index + 1);

    // conseguir la frecuencia de next_note_index
    melody_t *pp_melody = (p_fsm -> p_melody);
    double freq = (pp_melody -> p_notes[(actual_note_index)]);
    
    // lo mismo con la duracion
    uint32_t duration = (pp_melody -> p_durations[(actual_note_index)]);

    // llamar a _start_note
    _start_note(p_this, freq, duration);

    // Update the index of the melody
    p_fsm -> note_index +=1;
}    

/*
static void do_play_note (fsm_t *p_this) {
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    uint32_t actual_note_index = p_fsm -> note_index;
    //indice de la nota siguiente
    uint32_t next_note_index = actual_note_index + 1;
    double freq = p_fsm -> p_melody -> p_notes[next_note_index];
    uint32_t duration = p_fsm -> p_melody -> p_durations[next_note_index];
    _start_note(p_this, freq, duration);
    p_fsm -> note_index = next_note_index;
}	
*/

/**
 * @brief Start the player. \n 
 * This function starts the player by starting a melody.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 */
static void do_player_start	(fsm_t *p_this) {
    do_melody_start(p_this);
}

/**
 * @brief Stop the player. \n 
 * This function stops the player by stopping the PWM and the timer. This function is called when the player is set to stop.
 *  
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t.
 */
static void do_player_stop(fsm_t *p_this) {
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    port_buzzer_stop(p_fsm -> buzzer_id);
    p_fsm ->note_index = 0;
}

/**
 * @brief Array representing the transitions table of the fsm_buzzer.
 * 
 */
static fsm_trans_t fsm_trans_buzzer[] = {
//{ESTADO_INICIAL, funcion_comprueba_Condicion, ESTADO_SIGUIENTE, funcion_si_transicion}
    {WAIT_START, check_player_start, WAIT_NOTE, do_player_start},
    {WAIT_NOTE, check_note_end, PLAY_NOTE, do_note_end},
    {PLAY_NOTE, check_player_stop, WAIT_START, do_player_stop},
    {PLAY_NOTE, check_play_note, WAIT_NOTE, do_play_note},
    {PLAY_NOTE, check_pause, PAUSE_NOTE, do_pause},
    {PLAY_NOTE, check_end_melody, WAIT_MELODY, do_end_melody},
    {PAUSE_NOTE, check_resume, PLAY_NOTE, NULL},
    {WAIT_MELODY, check_melody_start, WAIT_NOTE, do_melody_start},
    {-1, NULL, -1, NULL}
};


/* Public functions */





/**
 * @brief Creates a new buzzer finite state machine.
 * 
 * @param buzzer_id Unique buzzer identifier number.
 * @return fsm_t* A pointer to the new buzzer finite state machine.
 */
fsm_t *fsm_buzzer_new(uint32_t buzzer_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_buzzer_t));
    fsm_buzzer_init(p_fsm, buzzer_id);
    return p_fsm;
}

/**
 * @brief Set the melody to play. \n
 * This function sets the melody to play. The user must pass a pointer to the melody to play.
 * 
 * @param p_this 	Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param p_melody Pointer to the melody to play
 */
void fsm_buzzer_set_melody (fsm_t *p_this, const melody_t *p_melody) {
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    melody_t *p_melothis = (melody_t *)(p_melody);
    p_fsm -> p_melody = p_melothis;
}	

/**
 * @brief 
 * Set the speed of the player. \n 
 * This function sets the speed of the player. 
 * The user must pass a double value with the speed of the player.
 * 
 * @param p_this 	Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param speed Speed of the player
 */
void fsm_buzzer_set_speed (fsm_t *p_this, double speed)	{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    p_fsm -> player_speed = speed;
}	

/**
 * @brief Set the action to perform on the player. \n 
 * This function sets the action to perform on the player. 
 * The user must pass a USER_ACTIONS value with the action desired. These serve as flags to indicate if the user has stopped, paused or started the player, or if the player has stopped itself.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param action Action to perform on the player
 */
void fsm_buzzer_set_action (fsm_t *p_this, uint8_t action) {
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    p_fsm -> user_action = action;
    if (action == STOP) {
        p_fsm -> note_index = 0;
    }
}	

/**
 * @brief Get the action of the user. \n 
 * This function returns the action performed on the player. This is useful to know if the 
 * player is playing, paused or stopped and a melody has ended.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @return uint8_t Action to perform on the player.
 */
uint8_t fsm_buzzer_get_action (fsm_t * p_this) {
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    return p_fsm -> user_action;
}

/**
 * @brief Initialize a buzzer finite state machine. \n 
 * This function initializes the default values of the FSM
 * struct and calls to the port to initialize the HW of associated to the given ID.
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param buzzer_id Unique buzzer identifier number.
 */
void fsm_buzzer_init(fsm_t *p_this, uint32_t buzzer_id)
{
    fsm_buzzer_t *p_fsm = (fsm_buzzer_t *)(p_this);
    fsm_init(p_this, fsm_trans_buzzer);
    p_fsm -> buzzer_id = buzzer_id;
    p_fsm -> p_melody = NULL;
    p_fsm -> note_index = 0;
    p_fsm -> user_action = STOP;
    p_fsm -> player_speed = 1.0;
    port_buzzer_init (p_fsm -> buzzer_id); 
}


/**
 * @brief Check if the buzzer finite state machine is playing a melody.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @return true 
 * @return false 
 */
bool fsm_buzzer_check_activity(fsm_t *p_this){
    return check_resume(p_this);
}	
