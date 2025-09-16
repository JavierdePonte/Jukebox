/**
 * @file fsm_usart.h
 * @brief Header for fsm_usart.c file.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Mac Afee
 * @date 18/03/2024
 */

#ifndef FSM_USART_H_
#define FSM_USART_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include <fsm.h>
#include "port_usart.h"

/* Other includes */

/* HW dependent includes */


/* Defines and enums ----------------------------------------------------------*/
/* Enums */
/**
 * @brief Enumerator for the USART finite state machine \n 
 * This enumerator defines the different states that the USART finite
 * state machine can be in. Each state represents a specific 
 * condition or step in the USART communication process.
 * 
 */
enum FSM_USART {
  WAIT_DATA = 0, /*!< Starting state. Also comes here when data has been sent or read*/
  SEND_DATA /*!< .*/
};

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure to define the USART FSM
 * 
 */
typedef struct {
    fsm_t f; /*!< USART FSM*/
    bool data_received; /*!< Flag to indicate that a data has been received*/
    char in_data [USART_INPUT_BUFFER_LENGTH]; /*!< Input data */
    char out_data [USART_OUTPUT_BUFFER_LENGTH]; /*!< Output data */
    uint32_t usart_id; /*!< USART identifier. Must be unique */
}fsm_usart_t;

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Creates a new USART FSM \n 
 * This FSM implements a USART communication protocol. It is a state
 * machine that sends and receives data. \n 
 * The FSM stores the received data in the **in_data** array. The user
 * should ask for it using the function **fsm_usart_get_in_data()**: \n 
 * At start and reset, the **in_data** array must be empty. An empty array means 
 * there has not been new data. 
 * 
 * @attention  The user is required to reset the **in_data** array once it has been read.
 * Otherwise, this value may be misinterpreted by the user, if successive calls are made
 * without having received new data. In such a case we would be reading past information.
 * In order to reset the value, the function **fsm_usart_reset_input_data()** must be called.
 * 
 * @brief In other words, the status flag of this FSM is the variable **in_data**. 
 * An empty array means that no new data has been received, a value other than 0 means that it 
 * has been received and the value is its duration, so it is the user's responsibility to clear this status flag. \n 
 * The FSM contains Information of the USART ID. This ID is a unique identifier that is managed by the user in the **port**.
 * That is where the user provides identifiers and HW information for all the USARTs on his system. The FSM does not have to 
 * know anything of the underlying HW.
 * @param usart_id Unique USART identifier number.
 * @return fsm_t* A pointer to the USART FSM.
 */
fsm_t * fsm_usart_new (uint32_t usart_id);

/**
 * @brief Initialize a USART FSM. \n 
 * This function initializes the default values of the FSM struct and calls to the port to initialize the HW of associated to the given ID.
 * 
 * @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct
 * @param usart_id Unique USART identifier number. 
 */
void fsm_usart_init (fsm_t *p_this, uint32_t usart_id);

/**
 * @brief Check if data has been received. \n 
 * This function checks if data has been received. If so, it returns true and the user can read the data using the function **fsm_usart_get_in_data()**.
 * @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct
 * @return true 
 * @return false 
 */
bool fsm_usart_check_data_received (fsm_t *p_this);

/**
 * @brief Get the data received. \n 
 * This function returns the data received by the USART.
 * @note It copies the content from source in_data of size USART_INPUT_BUFFER_LENGTH to the destination array p_data using the function memcpy()
 * @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct
 * @param p_data Pointer to the array where the data will be copied from the **in_data** array
 */
void fsm_usart_get_in_data (fsm_t *p_this, char *p_data);

/**
 * @brief Set the data to send. \n 
 * This function sets the data to send by the USART.
 * 
 * @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct
 * @param p_data Pointer to the array where the data will be copied from the **in_data** array
 */
void fsm_usart_set_out_data (fsm_t *p_this, char *p_data);

/**
 * @brief Reset the input data buffer
 * 
 * @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct 
 */
void fsm_usart_reset_input_data (fsm_t *p_this);

/**
 * @brief Check if the USART FSM is active, or not. \n 
 * The USART is active either when it is in the state SEND_DATA or there is data to be read (indicated as true in the field data_received).
 * 
 * @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct
 * @return true if any of the elements (button, USART, or buzzer) is active
 * @return false 
 */
bool fsm_usart_check_activity (fsm_t *p_this);

/**
 * @brief Disable the USART RX interrupt.
 * 
* @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct
 */
void fsm_usart_disable_rx_interrupt (fsm_t *p_this);

/**
 * @brief Disable the USART TX interrupts.
 * 
* @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct
 */
void fsm_usart_disable_tx_interrupt (fsm_t *p_this);

/**
 * @brief Enable the USART RX interrupt.
 * 
* @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct
 */
void fsm_usart_enable_rx_interrupt (fsm_t *p_this);

/**
 * @brief Enable the USART TX interrupts.
 * 
* @param p_this Pointer to an **fsm_t** struct that contains a **fsm_usart_t** struct
 */
void fsm_usart_enable_tx_interrupt (fsm_t *p_this);


#endif /* FSM_USART_H_ */
