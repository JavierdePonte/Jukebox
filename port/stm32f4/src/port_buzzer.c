/**
 * @file port_buzzer.c
 * @brief Portable functions to interact with the Buzzer melody player FSM library.
 * @author Javier de Ponte Hernando
 * @author Roberto Maldonado Macafee
 * @date 15/04/2024
 */
/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <math.h>
/* HW dependent libraries */
#include "port_buzzer.h"
#define ALT_FUNC2_TIM3 2
#define TIM_AS_PWM1_MASK 0x0060 
/* Global variables */
port_buzzer_hw_t buzzers_arr [] = {
    [BUZZER_0_ID] = {.p_port = BUZZER_0_GPIO, .pin = BUZZER_0_PIN, .alt_func = BUZZER_PWM_DC, .note_end = false}, 
};


/* Private functions */
/**
 * @brief Configure the timer that controls the duration of the note.
 * 
 * @param buzzer_id Buzzer melody player ID. This index is used to select the element of the buzzers_arr[] array.
 */
static void _timer_duration_setup(uint32_t buzzer_id)
{
  if (buzzer_id == BUZZER_0_ID)
  {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2 -> CR1 &= ~TIM_CR1_CEN;
    TIM2 -> CR1 |= TIM_CR1_ARPE;

    TIM2 -> SR = ~TIM_SR_UIF;

    TIM2 -> DIER |= TIM_DIER_UIE;

    /* Configure interruptions */
    NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 3, 0)); 
    NVIC_EnableIRQ(TIM2_IRQn);                                                          
  }
}

/**
 * @brief Configure the timer that controls the PWM of the buzzer.
 * 
 * @param buzzer_id Buzzer melody player ID. This index is used to select the element of the buzzers_arr[] array
 */
static void _timer_pwm_setup	(	uint32_t 	buzzer_id	)	{
  if (buzzer_id == BUZZER_0_ID) 
  {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3 -> CR1 &= ~TIM_CR1_CEN;
    TIM3 -> CR1 = TIM_CR1_ARPE;

    TIM3 -> CNT = 0;
    TIM3->ARR = 0;
    TIM3->PSC = 0;

    TIM3->EGR = TIM_EGR_UG;
    
    TIM3->CCER &= ~TIM_CCER_CC1E;
    
    TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_2;
    TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_1;
    TIM3 -> CCMR1 |= TIM_CCMR1_OC1PE;
  }
}






/* Public functions -----------------------------------------------------------*/


/**
 * @brief Configure the HW specifications of a given buzzer melody player.
 * 
 * @param buzzer_id Buzzer melody player ID. This index is used to select the element of the buzzers_arr[] array.
 */
void port_buzzer_init(uint32_t buzzer_id)
{
  port_buzzer_hw_t buzzer = buzzers_arr[buzzer_id];
  port_system_gpio_config(buzzer.p_port, buzzer.pin, GPIO_MODE_ALTERNATE, GPIO_PUPDR_NOPULL);
  port_system_gpio_config_alternate(buzzer.p_port, buzzer.pin, GPIO_MODE_ALTERNATE);
  _timer_duration_setup(buzzer_id);
  _timer_pwm_setup(buzzer_id);
}

/**
 * @brief Set the duration of the timer that controls the duration of the note.
 * 
 * @param buzzer_id Buzzer melody player ID. This index is used to select the element of the buzzers_arr[] array
 * @param duration_ms Duration of the note in ms
 */

void port_buzzer_set_note_duration(uint32_t buzzer_id, uint32_t duration_ms){
if(buzzer_id == BUZZER_0_ID) {
  //1) disable the timer and reset the counteR

  TIM2 -> CR1 &= ~TIM_CR1_CEN;
  TIM2 -> CNT = 0;

  //2) Convert duration_ms and SystemCoreClock to double
  // and store them in a local variable

  double sysclk_double = (double)SystemCoreClock; 
  double ms_double = (double)duration_ms;
  double a_milis = 1000.0;


  // 3) Compute an initial value for the PSC considering the maximum 
  // value of ARR (65535.0). Store it as double

  double psc_computed = round(((((sysclk_double/a_milis) * ms_double)/(65535.0 +1.0))-1.0));

  
  // 4) Recompute the value of ARR register with the PSC calculated

  double arr_computed = round((((sysclk_double/a_milis) * ms_double)/(psc_computed +1.0))-1.0);


  //5) Check if the new value of ARR is greater than 65535 and if so, increment psc
  // by 1 and recalculate ARR

  if(arr_computed > 65535.0){
    psc_computed++;
    arr_computed = round((((sysclk_double/a_milis) * ms_double)/(psc_computed +1.0))-1.0);
  }

  //6) Load the values computed into the corresponding registers of the timer

  TIM2 -> PSC = (uint32_t)(psc_computed);
  TIM2 -> ARR = (uint32_t)(arr_computed);

  //7) Load them into the active registers with an update event
  TIM2->EGR = TIM_EGR_UG;

  //8) Set the note_end flag to the appropiate value
  buzzers_arr[buzzer_id].note_end = false;

  //9) Enable the timer
  TIM2 -> CR1 |= TIM_CR1_CEN;
 
}
}

/**
 * @brief Retrieve the status of the note end flag.
 * 
 * @param buzzer_id Buzzer melody player ID. This index is used to select the element of the buzzers_arr[] array.
 * @return true 
 * @return false 
 */
bool port_buzzer_get_note_timeout	(	uint32_t 	buzzer_id	)	{
  if (buzzer_id == BUZZER_0_ID){
    return buzzers_arr[buzzer_id].note_end;
  }
  else{
    return false;
  }
}
/**
 * @brief Set the PWM frequency of the timer that controls the frequency of the note.
 * 
 * @param buzzer_id Buzzer melody player ID. This index is used to select the element of the buzzers_arr[] array.
 * @param frequency_hz Frequency of the note in Hz.
 */
void port_buzzer_set_note_frequency	(uint32_t 	buzzer_id, double frequency_hz)	{
//Asegurar que es la nota que toca
if(buzzer_id == BUZZER_0_ID){
  //Si la frecuencia es 0, disable timer and reset counter and return 
  
  if(frequency_hz == 0){
    TIM3 -> CR1 &= ~TIM_CR1_CEN;
    TIM3 -> CNT = 0;
    return;
  }

  //Resto de casos donde la frecuencia no es 0
  else {
    //Configure the values of PSC and ARR
    //Primero pasar la f_clk a double
    TIM3 -> CR1 &= ~TIM_CR1_CEN;
    TIM3 -> CNT = 0;

    double sysclk_double = (double)SystemCoreClock;

    // Le damos un valor inicial al PSC contando con que ARR vale 65535.0

    double psc_pwm = round(((sysclk_double / frequency_hz)/(65535.0 + 1.0)) - 1.0);
    // Recalculamos el valor de ARR con el psc obtenido

    double arr_pwm = round(((sysclk_double / frequency_hz)/(psc_pwm + 1.0)) - 1.0);

    // Check if the value of ARR is greater than 65535.0

    if(arr_pwm > 65535.0){
      // If so, increment psc
      psc_pwm++;
      // recalculate arr
      arr_pwm = round(((sysclk_double / frequency_hz)/(psc_pwm + 1.0)) - 1.0);
    }

    // Set the PWM pulse width to BUZZER_PWM_DC

    TIM3 -> CCR1 = (uint32_t)(BUZZER_PWM_DC * (arr_pwm + 1.0));
    
    // PSC and ARR into the active registers
    TIM3 -> PSC = (uint32_t)psc_pwm;
    TIM3 -> ARR = (uint32_t)arr_pwm;

    //by an update event

    TIM3 -> EGR |= TIM_EGR_UG;

    // Enable the output compare in the capture/compare register

    TIM3->CCER |= TIM_CCER_CC1E;

    //Enable the timer

    TIM3 -> CR1 |= TIM_CR1_CEN;

  }
}
}


/**
 * @brief Disable the PWM output of the timer that controls the frequency of the note and the timer that controls the duration of the note.
 * 
 * @param buzzer_id Buzzer melody player ID. This index is used to select the element of the buzzers_arr[] array.
 */
void port_buzzer_stop	(	uint32_t 	buzzer_id	) {
if (buzzer_id == BUZZER_0_ID){
  TIM3->CR1 &= ~TIM_CR1_CEN;
  TIM2 -> CR1 &= ~TIM_CR1_CEN;
}
}	


