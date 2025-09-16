/**
 * @file port_button.h
 * @brief Header for port_button.c file.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Macafee
 * @date 18/03/2024
 */
#ifndef PORT_BUTTON_H_
#define PORT_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include "port_system.h"
/* HW dependent includes */


/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define BUTTON_0_ID 0 /*!< Button identifier */
#define BUTTON_0_GPIO GPIOC /*!< Button GPIO port*/
#define BUTTON_0_PIN 13 /*!< Button GPIO pin */
#define BUTTON_0_DEBOUNCE_TIME_MS 150 /*!< Button debounce time in ms*/

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure to define de HW dependencies of a button
 * 
 */
typedef struct 
{
    GPIO_TypeDef *p_port; /*!< GPIO where the button is connected*/
    uint8_t pin; /*!< Pin/line where the button is connected*/
    bool flag_pressed; /*!< Flag to indicate that the button has been pressed*/
} port_button_hw_t;

/* Global variables */
/**
 * @brief Array of elements that represents the HW characteristics of the buttons \n 
 * This is an **extern** variable that is defined in [port_button.c](port_button_8c.html). It represents an array of hardware buttons \n 
 * This is an **extern** variable that is declared in [port_button.h](port_button_8h.html).
 */
extern port_button_hw_t buttons_arr []; 

/* Function prototypes and explanation -------------------------------------------------*/

/**
 * @brief Configure the HW specifications of a given button
 * 
 * @param button_id This index is used to select the element of the buttons_arr[] array
 */
void port_button_init (uint32_t button_id);

/**
 * @brief Returns the status of the button (pressed or not)
 * 
 * @param button_id This index is used to select the element of the buttons_arr[] array
 * @return true 
 * @return false 
 */
bool port_button_is_pressed (uint32_t button_id);

/**
 * @brief Return the count of the System tick in ms
 * 
 * @return uint32_t 
 */
uint32_t port_button_get_tick ();

#endif
