/**
 * @file port_button.c
 * @brief File containing functions related to the HW of the button.
 *
 * This file defines an internal struct which contains the HW information of the button.
 *
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Macafee
 * @date 18/03/2024
 */

/* Includes ------------------------------------------------------------------*/
#include "port_button.h" 

/* Global variables ------------------------------------------------------------*/
/**
 * @brief Array of elements that represents the HW characteristics of the buttons \n 
 * This is an **extern** variable that is defined in [port_button.c](port_button_8c.html). It represents an array of hardware buttons \n 
 * This is an **extern** variable that is declared in [port_button.h](port_button_8h.html).
 */
port_button_hw_t buttons_arr [] = {
    [BUTTON_0_ID] = {.p_port = BUTTON_0_GPIO, .pin = BUTTON_0_PIN, .flag_pressed = false},
};


void port_button_init(uint32_t button_id)
{
    GPIO_TypeDef *p_port = buttons_arr[button_id].p_port;
    uint8_t pin = buttons_arr[button_id].pin;
    port_system_gpio_config(p_port, pin, GPIO_MODE_IN, GPIO_PUPDR_NOPULL);
    port_system_gpio_config_exti(p_port, pin, (TRIGGER_ENABLE_INTERR_REQ | TRIGGER_FALLING_EDGE | TRIGGER_RISING_EDGE));
    port_system_gpio_exti_enable(pin, 1, 0);
}

bool port_button_is_pressed (uint32_t  button_id) {
    return buttons_arr[button_id].flag_pressed; 
} 	

uint32_t port_button_get_tick () {
    return port_system_get_millis();
}

