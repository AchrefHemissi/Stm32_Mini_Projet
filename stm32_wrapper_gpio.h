#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "Pin_Mode_Names.h"
#include <Serial_Config.h>  // Fichier o� sont d�finis les #define COM1, COM2, COM3, CONFIG_8N1, etc.
#include "CircularBuffer.h"

#ifndef __STM32_WRAPPER_GPIO_H
#define __STM32_WRAPPER_GPIO_H

// Buffers circulaires pour g�rer les donn�es des interruptions USART
extern CircularBuffer<char, 256> tx_buffer_usart1;
extern CircularBuffer<char, 256> rx_buffer_usart1;

extern CircularBuffer<char, 256> tx_buffer_usart2;
extern CircularBuffer<char, 256> rx_buffer_usart2;

extern CircularBuffer<char, 256> tx_buffer_usart3;
extern CircularBuffer<char, 256> rx_buffer_usart3;

// Handler pour USART1
void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
        if (!tx_buffer_usart1.isEmpty()) {
            USART_SendData(USART1, tx_buffer_usart1.pop());
        } else {
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
        }
    }

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        char data = USART_ReceiveData(USART1);
        rx_buffer_usart1.push(data);
    }
}

// Handler pour USART2
void USART2_IRQHandler(void) {
    if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET) {
        if (!tx_buffer_usart2.isEmpty()) {
            USART_SendData(USART2, tx_buffer_usart2.pop());
        } else {
            USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
        }
    }

    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        char data = USART_ReceiveData(USART2);
        rx_buffer_usart2.push(data);
    }
}

// Handler pour USART3
void USART3_IRQHandler(void) {
    if (USART_GetITStatus(USART3, USART_IT_TXE) != RESET) {
        if (!tx_buffer_usart3.isEmpty()) {
            USART_SendData(USART3, tx_buffer_usart3.pop());
        } else {
            USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
        }
    }

    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
        char data = USART_ReceiveData(USART3);
        rx_buffer_usart3.push(data);
    }
}

// Configuration des interruptions NVIC pour les USART
void configure_usart_interrupts(USART_TypeDef* usart) {
    NVIC_InitTypeDef NVIC_InitStructure;

    if (usart == USART1) {
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    } else if (usart == USART2) {
        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    } else if (usart == USART3) {
        NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    }

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Activer les interruptions RXNE
    USART_ITConfig(usart, USART_IT_RXNE, ENABLE);
}


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
void serial_init(COMPort comport, PinName tx, PinName rx, Speed speed, Config config, Mode mode);
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
