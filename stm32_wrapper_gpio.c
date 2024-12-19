/* ***************************************************************************/
/* WRAPPER LAYER : ADAPT OO Pin REPRESENTATION (mbed) TO ST Firmware Libraray*/
/* OO Representation : PA_0 = 0x01, PA_1=0x01, ...., PA_15=0x0F              */
/*                   : PB_0 = 0x11, PB_1=0x11, ...., PB_15=0x1F              */
/*																																           */
/* OO --> ST Firmware  : PA_0 --> GPIOA, GPIO_Pin_0 							           */
/*											 PB_12 --> GPIOB, GPIO_Pin_12							           */
/* Emir DAMERGI  -  INSAT 2021                                               */

/* ***************************************************************************/

#include "stm32_wrapper_gpio.h"
#include "CircularBuffer.h"
#include <cstring>  // For memset and strlen
#include <cstdlib>  // For malloc and free



// Définition des buffers circulaires pour les USART
CircularBuffer<char, 256> tx_buffer_usart1;
CircularBuffer<char, 256> rx_buffer_usart1;

CircularBuffer<char, 256> tx_buffer_usart2;
CircularBuffer<char, 256> rx_buffer_usart2;

CircularBuffer<char, 256> tx_buffer_usart3;
CircularBuffer<char, 256> rx_buffer_usart3;


/*================================================*/
/*     Part 1: Functions For PinAsInput Class     */
/*================================================*/


/*=== Functions Called by The PinAsInput Constructors ===*/

/*Constructor Without Mode = Default = Floating*/
void gpio_init_in_def(PinName pin) 
{
    gpio_init_in (pin, InDefault);
}

/*Constructor With Mode */
void gpio_init_in (PinName pin, PinInMode mode)
{
    _gpio_init_in(pin, mode);
}


/*=== Function To get gpio mode for ST FW lib === */
static int get_gpio_in_mode (PinInMode mode)
{	
	switch (mode){
		case 0: return GPIO_Mode_IN_FLOATING;
		case 1: return GPIO_Mode_IPU;
		case 2: return GPIO_Mode_IPD;
		default: return GPIO_Mode_IN_FLOATING; 
		}
}

/*=== Function To read Pin Value from IDR ====== */
	int gpio_read(PinName pin)
{
	int pinID = (pin & 0x0F);
	int pinValue =  (get_gpioport(pin)->IDR) & (1<<pinID);
	return (pinValue) ;
}

/*--------------------------------------------------------------*/
/*   INITIALLIZATION FUNCTION for PinAsInput Objects :          */          
/*      - Translates OO Pin Represetation (Px_i) to ST FWL      */
/*      - And Calls ST FWLibrary Functions                      */
/*--------------------------------------------------------------*/
static void _gpio_init_in(PinName pin, PinInMode mode)
{

		//get the gpioID from PinName (0 for GPIOA, 1 for GPIOB, ...) 	
	int gpioID = (pin & 0xF0) >> 4; 
	
	RCC_APB2PeriphClockCmd( 1<<(gpioID+2) , ENABLE);	
	
	  //convert gpioID to GPIOx
	GPIO_TypeDef* GPIOx = get_gpioport(pin);


		//Fills GPIO Structure and Calls GPIO_Init (ST FW Lib)
	GPIO_InitTypeDef GPIO_InitStruct; 

	GPIO_InitStruct.GPIO_Pin = 1<<(pin & 0x0F);
	
	GPIO_InitStruct.GPIO_Mode = (GPIOMode_TypeDef)get_gpio_in_mode(mode);

	GPIO_Init( GPIOx,  &GPIO_InitStruct);		
	}

/*=========== End PinAsInput Class Functions =============*/


	
/*-------------------------------------------------*/
	/* Common Function : To get GPIOx From PinName Value */
/*_________________________________________________*/
	
static GPIO_TypeDef* get_gpioport (PinName pin)
{
	int gpioID = (pin & 0xF0) >> 4; 
		
	GPIO_TypeDef* GPIOx;
	
	switch (gpioID){
		case 0x00: GPIOx=GPIOA; break;
		case 0x01: GPIOx=GPIOB; break;
		case 0x02: GPIOx=GPIOC; break;
		case 0x03: GPIOx=GPIOD; break;
		default: break;
		}
	return GPIOx;
}










/*=============SERIAL=============*/
/*
void serial_init(COMPort comport, PinName tx, PinName rx, Speed speed, Config config, Mode mode)
{

}
void serial_print(const char *chaine, uint16_t length)
{
}
char* serial_read(uint16_t length)
{
	
}
*/
// Mapping function for Word Length
uint16_t get_word_length(Config config) {
    switch (config & 0x30) {  // Check bits 4-5 for word length
        case 0x00:  // 8-bit word length
        case 0x10:  // 8-bit with even parity
        case 0x20:  // 8-bit with odd parity
            return USART_WordLength_8b;
        
        case 0x30:  // 9-bit word length
        case 0x40:  // 9-bit with even parity
        case 0x50:  // 9-bit with odd parity
            return USART_WordLength_9b;
        
        default:
            return USART_WordLength_8b;
    }
}

// Mapping function for Stop Bits
uint16_t get_stop_bits(Config config) {
    switch (config & 0x01) {  // Check least significant bit for stop bits
        case 0x00:  // 1 stop bit
            return USART_StopBits_1;
        
        case 0x01:  // 2 stop bits
            return USART_StopBits_2;
        
        default:
            return USART_StopBits_1;
    }
}

// Mapping function for Parity
uint16_t get_parity(Config config) {
    switch ((config & 0x20) >> 5) {  // Check bit 5 for parity type
        case 0x00:  // No parity
            return USART_Parity_No;
        
        case 0x01:  // Parity enabled
            switch ((config & 0x10) >> 4) {
                case 0x00:  // Even parity
                    return USART_Parity_Even;
                case 0x01:  // Odd parity
                    return USART_Parity_Odd;
                default:
                    return USART_Parity_No;
            }
        
        default:
            return USART_Parity_No;
    }
}

// Mapping function for Mode (Transmission/Reception)
uint16_t get_mode(Mode mode) {
    switch (mode) {
        case TX_MODE:
            return USART_Mode_Tx;
        case RX_MODE:
            return USART_Mode_Rx;
        case TXRX_MODE:
            return USART_Mode_Tx | USART_Mode_Rx;
        default:
            return USART_Mode_Tx | USART_Mode_Rx;
    }
}

USART_TypeDef* get_usart_instance(COMPort comport) {
    switch (comport) {
        case COM1: return USART1;
        case COM2: return USART2;
        case COM3: return USART3;
        default: return USART2;
    }
}
// Updated serial_init function using the mapping functions
void serial_init(COMPort comport, PinName tx, PinName rx, Speed speed, Config config, Mode mode) {
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    // Clock configuration (same as before)
    switch (comport) {
        case COM1:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
            break;
        case COM2:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
            break;
        case COM3:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            break;
        default:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
            break;
    }

    // GPIO configuration (same as before)
    GPIO_InitStructure.GPIO_Pin = 1 << (tx & 0x0F);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(get_gpioport(tx), &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = 1 << (rx & 0x0F);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(get_gpioport(rx), &GPIO_InitStructure);

    // USART configuration using mapping functions
    USART_InitStructure.USART_BaudRate = speed;
    USART_InitStructure.USART_WordLength = get_word_length(config);
    USART_InitStructure.USART_StopBits = get_stop_bits(config);
    USART_InitStructure.USART_Parity = get_parity(config);
    USART_InitStructure.USART_Mode = get_mode(mode);
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    // Initialize and enable USART
    USART_Init(get_usart_instance(comport), &USART_InitStructure);
    USART_Cmd(get_usart_instance(comport), ENABLE);
}
// Fonction pour envoyer une chaîne de caractères via un USART donné en mode polling
void serial_print(const char *chaine, uint16_t length, USART_TypeDef* usart) {
    for (uint16_t i = 0; i < length; i++) {
        // Attendre que le registre de données soit vide
        while (USART_GetFlagStatus(usart, USART_FLAG_TXE) == RESET);
        // Envoyer un caractère
        USART_SendData(usart, (uint16_t)chaine[i]);
    }
}

char* serial_read(uint16_t length, USART_TypeDef* usart)
{
    static char* Rcv_Buffer = NULL; // Pointer to the buffer
    static uint8_t i = 0;

    // Allocate memory for the buffer if not already allocated
    if (Rcv_Buffer == NULL)
    {
        Rcv_Buffer = (char*)malloc(length + 1);
        if (Rcv_Buffer == NULL)
        {
            // Handle memory allocation failure
            return NULL;
        }
    }

    // Polling for data reception
    if (USART_GetFlagStatus(usart, USART_FLAG_RXNE) != RESET)
    {
        // Read received data
        char received_char = USART_ReceiveData(usart);

        // Store the received character into the buffer
        if (i < length)
        {
            Rcv_Buffer[i++] = received_char;
        }
        else
        {
            // If buffer is full, reset index and null-terminate the string
            Rcv_Buffer[i] = '\0';
            i = 0;
            
            // Once data is received, free the buffer if you're done
    if (Rcv_Buffer != NULL)
    {
        free(Rcv_Buffer);
        Rcv_Buffer = NULL;
    }        }
    }
    return Rcv_Buffer;
}



void config1()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* ================  Configure the Periph Clocks ===================== */
    /* Enable GPIOx and AFIO clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

    /* ================  Configure the GPIO ports ===================== */
    /* Configure PA5 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ---------------------------------------------------------- */
    // Configure USART1 to Receive Data using polling method
    /* Enable USART1 clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* Configure USART1 Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ====================  USART1 configuration ======================*/
    /* 
      - BaudRate = 9600 baud 
      - Word Length = 8 Bits
      - One Stop Bit
      - No parity
      - Receive enabled
    */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);

    /* Enable the USART1 */
    USART_Cmd(USART1, ENABLE);
}

void config()
{
  // Déclaration des structures GPIO et USART
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* ===================== Enable Clocks ====================== */
  // Activer les horloges pour GPIOA, GPIOC et AFIO
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

  /* ===================== Configure GPIOA pour USART2_TX ====================== */
  // Configurer PA2 comme USART2_TX (fonction alternative push-pull)gpio_read(PA_2)
  GPIO_InitStructure.GPIO_Pin =1<<(PA_2 & 0x0F) ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* ===================== Activer l'horloge de l'USART2 ====================== */
  // Activer l'horloge de l'USART2
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  /* ===================== Configuration de l'USART2 ====================== */
  // Configurer l'USART2 pour la transmission
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;

  // Initialiser l'USART2 avec la configuration définie
  USART_Init(USART2, &USART_InitStructure);

  /* ===================== Activer l'USART2 ====================== */
  // Activer l'USART2
  USART_Cmd(USART2, ENABLE);
}

