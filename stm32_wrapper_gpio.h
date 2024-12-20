#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "Pin_Mode_Names.h"
#include <Serial_Config.h>  // Fichier où sont définis les #define COM1, COM2, COM3, CONFIG_8N1, etc.

#ifndef __STM32_WRAPPER_GPIO_H
#define __STM32_WRAPPER_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* =======================================*/
/* 1 : Functions For PinAsInput Class --- */
/*----------------------------------------*/
void config();
void config1();

void gpio_init_in_def(PinName pin);	
	
void gpio_init_in(PinName pin, PinInMode mode);

static void _gpio_init_in(PinName pin, PinInMode mode );

int gpio_read (PinName thepin);	
	
static int get_gpio_in_mode (PinInMode mode);	
/*==========================================*/


	
/* --- 2 : Common Functions ---- */

/*  Get the GPIOx From PinName  */
static GPIO_TypeDef* get_gpioport (PinName pin);
	
/* Serial*/
void serial_init(COMPort comport, PinName tx, PinName rx, Speed speed, Config config, Mode mode, USART_TypeDef* usart);
void serial_print(const char *chaine, uint16_t length,USART_TypeDef* usart);
char* serial_read(uint16_t length,USART_TypeDef* usart);
USART_TypeDef* get_usart_instance(COMPort comport);
uint16_t get_mode(Mode mode);
uint16_t get_parity(Config config);
uint16_t get_stop_bits(Config config);
uint16_t get_word_length(Config config) ;
#ifdef __cplusplus
}
#endif


#endif //__STM32_WRAPPER_GPIO_H
