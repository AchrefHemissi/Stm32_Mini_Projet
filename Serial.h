#ifndef SERIAL_H
#define SERIAL_H
#include "CircularBuffer.h"
#include <stdint.h>
#include <stm32_wrapper_gpio.h>

namespace OOlayer {

class Serial {
private:
	
    USART_TypeDef* usart;

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
        serial_init(COMDEFAULT, PA_2, PA_3, SPEEDDEFAULT, CONFIGDEFAULT, MODEDEFAULT);
						//config1();

			}

    // Constructeur avec spécification du port COM, des pins Tx et Rx
    Serial(COMPort comport, PinName tx, PinName rx) {
				this->usart=get_usart_instance(comport);
        serial_init(comport, tx, rx, SPEEDDEFAULT, CONFIGDEFAULT, MODEDEFAULT);
    }

    // Constructeur avec port COM, pins Tx/Rx et vitesse (baudRate)
    Serial(COMPort comport, PinName tx, PinName rx, Speed speed) {
				this->usart=get_usart_instance(comport);
        serial_init(comport, tx, rx, speed, CONFIGDEFAULT, MODEDEFAULT);
    }

    // Constructeur avec port COM, pins Tx/Rx, vitesse et configuration
    Serial(COMPort comport, PinName tx, PinName rx, Speed speed, Config config) {
				this->usart=get_usart_instance(comport);
        serial_init(comport, tx, rx, speed, config, MODEDEFAULT);
    }

    // Constructeur avec tous les paramètres (port, pins, vitesse, configuration, mode)
    Serial(COMPort comport, PinName tx, PinName rx, Speed speed, Config config, Mode mode) {
				this->usart=get_usart_instance(comport);
        serial_init(comport, tx, rx, speed, config, mode);
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
		
		void ITprintchaine(const char *chaine, uint16_t length, USART_TypeDef* usart) {
			// Choose the appropriate tx_buffer based on USART instance
			CircularBuffer<char, 256>* tx_buffer;

			if (usart == USART1) {
					tx_buffer = &tx_buffer_usart1;
			} else if (usart == USART2) {
					tx_buffer = &tx_buffer_usart2;
			} else if (usart == USART3) {
					tx_buffer = &tx_buffer_usart3;
			}

			if (tx_buffer) {
					for (uint16_t i = 0; i < length; ++i) {
							tx_buffer->push(chaine[i]); // Ajouter chaque caractère au buffer d'envoi
					}

					// Activer l'interruption TXE si le buffer n'est pas vide
					if (!tx_buffer->isEmpty()) {
							USART_ITConfig(usart, USART_IT_TXE, ENABLE); // Activer l'interruption TXE
					}
			}
	}

		char* ITreadchaine(uint16_t length, USART_TypeDef* usart) {
    static char buffer[256]; // Buffer temporaire pour stocker les données
    uint16_t i = 0;

    // Choisir le buffer de réception approprié selon l'USART
    CircularBuffer<char, 256>* rx_buffer ;

    if (usart == USART1) {
        rx_buffer = &rx_buffer_usart1;
    } else if (usart == USART2) {
        rx_buffer = &rx_buffer_usart2;
    } else if (usart == USART3) {
        rx_buffer = &rx_buffer_usart3;
    }

    if (rx_buffer) {
        while (i < length && !rx_buffer->isEmpty()) {
            buffer[i++] = rx_buffer->pop(); // Lire les données depuis le buffer RX
        }
        buffer[i] = '\0'; // Ajouter le caractère nul à la fin de la chaîne
    }

    return buffer;
}


};

}  // namespace OOlayer

#endif // SERIAL_H
