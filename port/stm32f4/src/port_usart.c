/**
 * @file port_usart.c
 * @brief Portable functions to interact with the USART FSM library.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Macafee
 * @date 18/03/2024
 */
/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <string.h>
#include <stdlib.h>
#include "port_system.h"
#include "port_usart.h"
/* HW dependent libraries */

/* Global variables */
/**
 * @brief Array of elements that represents the HW characteristics of the USARTs \n
 * This is an **extern** variable that is defined in port_usart.c . It represents an array of HWs USARTs \n 
 * This is an **extern** variable that is declared in port_usart.h
 * 
 */
port_usart_hw_t usart_arr[] = {
[USART_0_ID] = {
    .p_usart = USART_0,
    .p_port_tx = USART_0_GPIO_TX,
    .p_port_rx = USART_0_GPIO_RX,
    .pin_tx = USART_0_PIN_TX,
    .pin_rx = USART_0_PIN_RX,
    .alt_func_tx = USART_0_AF_TX,
    .alt_func_rx = USART_0_AF_RX,
    .i_idx = 0,
    .read_complete = false,
    .o_idx = 0,
    .write_complete = false}
};

/* Private functions */
/**
 * @brief Reset a buffer to a default value
 * 
 * @param buffer Pointer to the buffer to be reseted
 * @param length Length of the buffer
 */
void _reset_buffer(char * buffer, uint32_t length){
    memset(buffer, EMPTY_BUFFER_CONSTANT, length);
}

/* Public functions */


void port_usart_init(uint32_t usart_id)
{
    USART_TypeDef *p_usart = usart_arr[usart_id].p_usart;
    GPIO_TypeDef *p_port_tx = usart_arr[usart_id].p_port_tx;
    GPIO_TypeDef *p_port_rx = usart_arr[usart_id].p_port_rx;
    uint8_t pin_tx = usart_arr[usart_id].pin_tx;
    uint8_t pin_rx = usart_arr[usart_id].pin_rx;
    uint8_t alt_func_tx = usart_arr[usart_id].alt_func_tx;
    uint8_t alt_func_rx = usart_arr[usart_id].alt_func_rx;


  

    // Enable USART interrupts globally
    if (p_usart == USART3)
    {
        NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
        NVIC_EnableIRQ(USART3_IRQn);
    }

    //configure USART TX and RX pins as ALTERNATE and PULL UP
    port_system_gpio_config(p_port_tx, pin_tx, GPIO_MODE_ALTERNATE, GPIO_PUPDR_PUP);
    port_system_gpio_config(p_port_rx, pin_rx, GPIO_MODE_ALTERNATE, GPIO_PUPDR_PUP);
    port_system_gpio_config_alternate(p_port_tx, pin_tx, alt_func_tx);
    port_system_gpio_config_alternate(p_port_rx, pin_rx, alt_func_rx);
    //Enable the clock for the USART (USART3) peripheral
    RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;   
    //Disable the USART3
    usart_arr[usart_id].p_usart -> CR1 &= ~USART_CR1_UE;
    /*Configure 9600-8-N-1 */ 
    // DATA LENGTH: 8
    usart_arr[usart_id].p_usart -> CR1 &= ~USART_CR1_M;
    // 1 BIT STOP
    usart_arr[usart_id].p_usart -> CR2 &= ~USART_CR2_STOP;
    // NOT PARITY BIT
    usart_arr[usart_id].p_usart -> CR1 &= ~USART_CR1_PCE;
    // OVERSAMPLING TO 16
    usart_arr[usart_id].p_usart -> CR1 &= ~USART_CR1_OVER8;
    // Configure baud rate
    /* Baudrate = 9600. f_clock = 16 MHz. OVER8 = 0.
    USART_DIV = 104,167
    104 -> 0x0068.
    0,167 x 2 = 0,334 BIT '0'
    0,334 x 2 = 0,668 BIT '0'
    0,668 x 2 = 1,336 BIT '1'
    0,336 x 2 = 0,672 BIT '0'
    0b0010 -> 2
    USART_DIV = 0x0682
    */
    usart_arr[usart_id].p_usart -> BRR = 0x0682;
    //Enable TX and RX
    usart_arr[usart_id].p_usart -> CR1 |= USART_CR1_TE | USART_CR1_RE;
    //Disable TX and RX interrupt
    usart_arr[usart_id].p_usart -> CR1 &= ~USART_CR1_RXNEIE; 
    usart_arr[usart_id].p_usart -> CR1 &= ~USART_CR1_TXEIE; 
    //Clear RXNE interrupt flag USART3 -> ICR |= USART_ICR_RXNECF;
    //Read the DR register to clear the RXNE interrupt flag
    usart_arr[usart_id].p_usart -> DR;
    //Enable the USART
    usart_arr[usart_id].p_usart -> CR1 |= USART_CR1_UE;
    //reset buffer
    _reset_buffer(usart_arr[usart_id].input_buffer, USART_INPUT_BUFFER_LENGTH);
    _reset_buffer(usart_arr[usart_id].output_buffer, USART_OUTPUT_BUFFER_LENGTH);
}


void port_usart_get_from_input_buffer(uint32_t usart_id, char * p_buffer){
    memcpy(p_buffer, usart_arr[usart_id].input_buffer, USART_INPUT_BUFFER_LENGTH);
}


bool port_usart_get_txr_status(uint32_t usart_id ){
    // port_usart_hw_t *USART3 = &usart_arr[usart_id];
    if(( usart_arr[usart_id].p_usart -> SR & USART_SR_TXE) == 0){
        return false;
    } else {
        return true;
    }
}


void port_usart_reset_input_buffer( uint32_t usart_id ){
    _reset_buffer(usart_arr[usart_id].input_buffer, USART_INPUT_BUFFER_LENGTH);
    usart_arr[usart_id].read_complete = false;
}


void port_usart_reset_output_buffer( uint32_t usart_id ){
    _reset_buffer(usart_arr[usart_id].output_buffer, USART_OUTPUT_BUFFER_LENGTH);
    usart_arr[usart_id].write_complete = false;
}


bool port_usart_rx_done( uint32_t usart_id ){
    return usart_arr[usart_id].read_complete;
}


bool port_usart_tx_done( uint32_t usart_id ){
    return usart_arr[usart_id].write_complete;
}


void port_usart_store_data( uint32_t usart_id ){
   //Retrieve data from DR register
   char data =  usart_arr[usart_id].p_usart -> DR; 

   if( data != END_CHAR_CONSTANT){
    //Retrieve input data index
    uint8_t i_idx = usart_arr[usart_id].i_idx;
    if(i_idx >= USART_INPUT_BUFFER_LENGTH){
        //Reset input buffer index
        usart_arr[usart_id].i_idx = 0;
    }
    //Load data in input buffer and update input buffer index
   usart_arr[usart_id].input_buffer[i_idx] = data;
   usart_arr[usart_id].i_idx++;
   } else {
    //Data has been read. Reset input buffer index
    usart_arr[usart_id].read_complete = true;
    usart_arr[usart_id].i_idx = 0;
   }
  
}


void port_usart_write_data(uint32_t usart_id){
    //Retrieve output buffer index and data at index
    uint8_t o_idx = usart_arr[usart_id].o_idx;
    char data = usart_arr[usart_id].output_buffer[o_idx];
    if( o_idx == USART_OUTPUT_BUFFER_LENGTH - 1 || data == END_CHAR_CONSTANT){
        //Load data in DR Register
        usart_arr[usart_id].p_usart -> DR = data;
        //Disable TX interrupt
        usart_arr[usart_id].p_usart -> CR1 &= ~USART_CR1_TXEIE; 
        //Reset output buffer index. Update write_complete
        usart_arr[usart_id].o_idx = 0;
        usart_arr[usart_id].write_complete = true;
    } else {
        if (data != EMPTY_BUFFER_CONSTANT){ 
        //Load data in DR register and update o_idx
        usart_arr[usart_id].p_usart -> DR = data;
        usart_arr[usart_id].o_idx++;}
    }
}


void port_usart_enable_rx_interrupt( uint32_t usart_id ){

    usart_arr[usart_id].p_usart -> CR1 |= USART_CR1_RXNEIE;
}


void port_usart_enable_tx_interrupt( uint32_t usart_id ){

    usart_arr[usart_id].p_usart -> CR1 |= USART_CR1_TXEIE;
    }


void port_usart_disable_rx_interrupt( uint32_t usart_id ){
    usart_arr[usart_id].p_usart -> CR1 &= ~USART_CR1_RXNEIE;
}


void port_usart_disable_tx_interrupt( uint32_t usart_id ){
    usart_arr[usart_id].p_usart -> CR1 &= ~USART_CR1_TXEIE;
}

void port_usart_copy_to_output_buffer (uint32_t usart_id, char * p_data, uint32_t length )	{
    memcpy( usart_arr[usart_id].output_buffer, p_data, length);
}	
