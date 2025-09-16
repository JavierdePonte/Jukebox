/**
 * @file port_usart.h
 * @brief Header for port_usart.c file.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Macafee
 * @date 18/03/2024
 */
#ifndef PORT_USART_H_
#define PORT_USART_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>


/* HW dependent includes */
#include "stm32f4xx.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define 	USART_0_ID 0 /*!< USART identifier*/
#define 	USART_0 ((USART_TypeDef*) USART3)/*!< USART used connected to the GPIO*/
#define 	USART_0_GPIO_TX GPIOB/*!< USART GPIO port for TX pin*/
#define 	USART_0_GPIO_RX GPIOC/*!< USART GPIO port for RX pin */
#define 	USART_0_PIN_TX 10 /*!< USART GPIO pin for TX*/
#define 	USART_0_PIN_RX 11 /*!< USART GPIO pin for RX*/
#define 	USART_0_AF_TX 7 /*!< USART alternate function for TX*/
#define 	USART_0_AF_RX 7/*!< USART alternate function for RX*/
#define 	USART_INPUT_BUFFER_LENGTH 10 /*!< USART input message length*/
#define 	USART_OUTPUT_BUFFER_LENGTH 100 /*!< USART output message length*/
#define 	EMPTY_BUFFER_CONSTANT 0x0 /*!< Empty char constant*/
#define 	END_CHAR_CONSTANT 0xA /*!< End char constant*/

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure to define the HW dependencies of a USART
 * 
 */
typedef struct{
    USART_TypeDef *p_usart; /*!< USART peripheral*/
    GPIO_TypeDef *p_port_tx; /*!< GPIO where the USART TX is connected*/
    GPIO_TypeDef *p_port_rx; /*!< GPIO where the USART RX is connected*/
    uint8_t pin_tx; /*!< Pin/line where the USART TX is connected*/
    uint8_t pin_rx; /*!< Pin/line where the USART RX is connected*/
    uint8_t alt_func_tx; /*!< Alternate function for the TX pin*/
    uint8_t alt_func_rx; /*!< Alternate function for the RX pin*/
    char input_buffer [USART_INPUT_BUFFER_LENGTH]; /*!< Input buffer*/
    uint8_t i_idx; /*!< Index to the input buffer*/
    bool read_complete; /*!< Flag to indicate that the data has been read*/
    char output_buffer [USART_OUTPUT_BUFFER_LENGTH]; /*!< Output buffer*/
    uint8_t o_idx; /*!< Index to the output buffer*/
    bool write_complete; /*!< Flag to indicate that the data has been sent*/
} port_usart_hw_t; 

/* Global variables */
/**
 * @brief Array of elements that represents the HW characteristics of the USARTs \n
 * This is an **extern** variable that is defined in port_usart.c . It represents an array of HWs USARTs \n 
 * This is an **extern** variable that is declared in port_usart.h
 * 
 */
extern port_usart_hw_t usart_arr[];

/* Function prototypes and explanation -------------------------------------------------*/

/**
 * @brief Configure the HW specifications of a given USART
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array
 */
void port_usart_init (uint32_t usart_id);

/**
 * @brief Check if a transmission is completed
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 * @return true 
 * @return false 
 */
bool port_usart_tx_done (uint32_t usart_id);

/**
 * @brief Check if a reception is completed
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 * @return true 
 * @return false 
 */
bool port_usart_rx_done (uint32_t usart_id);

/**
 * @brief Get the message received through the USART and store it in the buffer passed as an argument \n
 * This function is called from the function do_get_data_rx() of the FSM to store the message received
 * to the buffer of the FSM
 *  
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 * @param p_buffer Pointer to the buffer where the message will be stored
 */
void port_usart_get_from_input_buffer (uint32_t usart_id, char *p_buffer);

/**
 * @brief Check if the USART is ready to receive a new message
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 * @return true 
 * @return false 
 */
bool port_usart_get_txr_status (uint32_t usart_id);

/**
 * @brief Copy the message passed as an argument to the output buffer of the USART \n 
 * This function is called from the function do_set_data_tx() of the FSM to set the message to send to the USART
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 * @param p_data Pointer to the message to send
 * @param length Length of the message to send
 */
void port_usart_copy_to_output_buffer (uint32_t usart_id, char *p_data, uint32_t length);

/**
 * @brief Reset the input buffer of the USART. \n 
 * This function is called from do_get_data_rx() to reset the input buffer of the USART after the message has been read.
 * 
  * @param usart_id This index is used to select the element of the usart_arr[] array.
 */
void port_usart_reset_input_buffer (uint32_t usart_id);

/**
 * @brief Reset the output buffer of the USART. \n 
 * This function is called from do_set_data_tx() and do_tx_end() to reset the output buffer of the USART after the message has been read.
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 */
void port_usart_reset_output_buffer (uint32_t usart_id);

/**
 * @brief Function to read the data from the USART Data Register and store it in the input buffer. \n 
 * This function is called from the ISR USART3_IRQHandler() when the RXNE flag is set \n 
 * ![Implements](docs/assets/imgs/flow_graph_store_data.png)
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 */
void port_usart_store_data (uint32_t usart_id);

/**
 * @brief Function to write the data from the output buffer to the USART Data Register \n 
 * This function is called from the ISR USART3_IRQHandler() when the TXE flag is set
 * ![Implements](docs/assets/imgs/flow_graph_write_data.png)
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 */
void port_usart_write_data (uint32_t usart_id);

/**
 * @brief Disable USART RX interrupt.
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 */
void port_usart_disable_rx_interrupt (uint32_t usart_id);

/**
 * @brief Disable USART TX interrupts
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 */
void port_usart_disable_tx_interrupt (uint32_t usart_id);

/**
 * @brief Enable USART RX interrupt
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 */
void port_usart_enable_rx_interrupt (uint32_t usart_id);

/**
 * @brief Enable USART TX interrupt
 * 
 * @param usart_id This index is used to select the element of the usart_arr[] array.
 */
void port_usart_enable_tx_interrupt (uint32_t usart_id);
#endif