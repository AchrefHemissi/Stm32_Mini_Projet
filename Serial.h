#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stm32_wrapper_gpio.h>

namespace OOlayer {

class Serial {
private:
	
		char* txBuffer ;        // Buffer for transmit data
    char* rxBuffer;        // Buffer for receive data
    uint16_t txLength;     // Length of data to transmit
    uint16_t rxLength;     // Length of data to receive
    uint16_t txCount;      // Current transmit position
    uint16_t rxCount;      // Current receive position
    USART_TypeDef* usart; // USART instance
		

public:
    // Constructeur par défaut (COM2, PA_2, PA_3, 9600, CONFIG_8N1, TxRxMode)
    Serial() {
			
			/*test print
			this->usart=get_usart_instance(COMDEFAULT);
			config1();
			*/
			/* test read
													this->usart=get_usart_instance(COM1);
			config1();
*/
			
			/*
        serial_init(COMDEFAULT, PA_2, PA_3, SPEEDDEFAULT, CONFIGDEFAULT, MODEDEFAULT);

    */

			  this->usart=get_usart_instance(COMDEFAULT);
        serial_init(COMDEFAULT, PA_2, PA_3, SPEEDDEFAULT, CONFIGDEFAULT, MODEDEFAULT, this->usart);
						//config1();

			}

    // Constructeur avec spécification du port COM, des pins Tx et Rx
    Serial(COMPort comport, PinName tx, PinName rx) {
				this->usart=get_usart_instance(comport);
        serial_init(comport, tx, rx, SPEEDDEFAULT, CONFIGDEFAULT, MODEDEFAULT,this->usart);
    }

    // Constructeur avec port COM, pins Tx/Rx et vitesse (baudRate)
    Serial(COMPort comport, PinName tx, PinName rx, Speed speed) {
				this->usart=get_usart_instance(comport);
        serial_init(comport, tx, rx, speed, CONFIGDEFAULT, MODEDEFAULT,this->usart);
    }

    // Constructeur avec port COM, pins Tx/Rx, vitesse et configuration
    Serial(COMPort comport, PinName tx, PinName rx, Speed speed, Config config) {
				this->usart=get_usart_instance(comport);
        serial_init(comport, tx, rx, speed, config, MODEDEFAULT,this->usart);
    }

    // Constructeur avec tous les paramètres (port, pins, vitesse, configuration, mode)
    Serial(COMPort comport, PinName tx, PinName rx, Speed speed, Config config, Mode mode) {
				this->usart=get_usart_instance(comport);
        serial_init(comport, tx, rx, speed, config, mode,this->usart);
    }

    // Méthode pour envoyer une chaîne de caractères en mode polling
    void printchaine(const char *chaine, uint16_t length) {
        serial_print(chaine, length,this->usart);
    }

    // Méthode pour recevoir une chaîne de caractères en mode polling
    char* readchaine(uint16_t length) {
        return serial_read(length,this->usart);
    }
		USART_TypeDef* getUsart()
		{
			return usart;
		}
		
		void ITprintchaine(char* chaine, uint16_t length){
					// Store buffer information
				txBuffer = chaine;
				txLength = length;
				txCount = 0;
				
				// Enable USART TX interrupt
				USART_ITConfig(usart, USART_IT_TXE, ENABLE);
		}
		
		char* ITreadchaine(uint16_t length){
					// Allocate receive buffer
				rxBuffer = new char[length + 1];
				rxLength = length;
				rxCount = 0;
				
				// Enable USART RX interrupt
				USART_ITConfig(usart, USART_IT_RXNE, ENABLE);
				
				return rxBuffer;
		}
};

}  // namespace OOlayer

#endif // SERIAL_H
