/**
 * @file interr.c
 * @brief Interrupt service routines for the STM32F4 platform.
 * @author Sistemas Digitales II
 * @date 2024-01-01
 */
// Include HW dependencies:
#include "port_system.h"
 
// Include headers of different port elements:
 //#include "port_system.h"
 #include "port_button.h"
 #include "port_usart.h"
 #include "port_buzzer.h"
//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
/**
 * @brief Interrupt service routine for the System tick timer (SysTick).
 *
 * @note This ISR is called when the SysTick timer generates an interrupt.
 * The program flow jumps to this ISR and increments the tick counter by one millisecond.
 * @warning **The variable `msTicks` must be declared volatile!** Just because it is modified by a call of an ISR, in order to avoid [*race conditions*](https://en.wikipedia.org/wiki/Race_condition). **Added to the definition** after *static*.
 *
 */
void SysTick_Handler()
{
    //declaramos ms y guardamos el valor de msTicks
    uint32_t msTicks = port_system_get_millis(); 
    //almacenamos en msTicks ms + 1
    port_system_set_millis(msTicks + 1);
    //msTicks++;
}
/**
 * @brief This function handles Px10-Px15 global interrupts \n 
 * First, this function identifies the line/pin which has raised the interruption. 
 * Then, it performs the desired action. Before leaving it, cleans the interrupt pending register.
 * 
 */
void EXTI15_10_IRQHandler (void) {
    port_system_systick_resume();
    if (EXTI -> PR & BIT_POS_TO_MASK(buttons_arr[BUTTON_0_ID].pin))
    {
        if (port_system_gpio_read(buttons_arr[BUTTON_0_ID].p_port, buttons_arr[BUTTON_0_ID].pin))
        {
            buttons_arr[BUTTON_0_ID].flag_pressed = false;
        }
        else {
            buttons_arr[BUTTON_0_ID].flag_pressed = true;
        }
        EXTI -> PR |= BIT_POS_TO_MASK(buttons_arr[BUTTON_0_ID].pin);
    }
}	

/**
 * @brief This function handles USART3 global interrupt. \n 

First, this function identifies the line/ pin which has raised the interruption. Then, perform the desired action.
Before leaving it cleans the interrupt pending register. \n 

The program flow jumps to this ISR when the USART3 generates an interrupt. It can be due to: 

- Reception of a new byte (RXNE)
- Transmission of a byte has finished (TC)
- Transmission buffer is empty (TXE)
 * 
 */
void USART3_IRQHandler(void ){
    port_system_systick_resume();
    //if there has been received a new data
    if(USART3 -> CR1 & USART_CR1_RXNEIE){
        //Check that the flag is set
        if(USART3 -> SR & USART_SR_RXNE){
            port_usart_store_data(USART_0_ID);
        }    
    }
        //if buffer is empty
        if(USART3 -> CR1 & USART_CR1_TXEIE){
        //Check that the flag is set
        if(USART3 -> SR & USART_SR_TXE){
            port_usart_write_data(USART_0_ID);
        }    
    }
        //if TX is completed
        if(USART3 -> CR1 & USART_CR1_TCIE){
        //Check that the flag is set
        if(USART3 -> SR & USART_SR_TC){
            USART3 -> SR &= ~USART_SR_TC;
        }    
    }

}

/**
 * @brief This function handles TIM2 global interrupt. \n 
 * This timer is used to control the duration of the note. When the timer expires, it generates an interrupt. The code jumps to this ISR when the timer generates an interrupt.
 */
void TIM2_IRQHandler ( void ) {
    TIM2 -> SR &= ~TIM_SR_UIF;
    buzzers_arr[BUZZER_0_ID].note_end = true;
}	
