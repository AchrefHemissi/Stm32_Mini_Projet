#include "serial.h"
#include "stm32_wrapper_gpio.h"
#include <string.h>
char Receive_Buffer[20];  // Fixed-size buffer
	void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
int main() {


	/*read
	OOlayer::Serial serial;

  while(1)
	{
		strcpy(Receive_Buffer, serial.readchaine(20)); // Copy data into Receive_Buffer
 // Copy data into Receive_Buffer
	}			
*/
    OOlayer::Serial serial1;
    
    // 2. Second Serial object - COM1 with custom baud rate
    OOlayer::Serial serial2(COM1, PA_9, PA_10, SPEED_115200);
    
    // 3. Third Serial object - COM3 with full custom configuration
    OOlayer::Serial serial3(
        COM3,           // COM port
        PB_10,          // TX pin
        PB_11,          // RX pin
        SPEED_19200,    // Baud rate
        CONFIG_9E1,     // Configuration (9-bit, even parity, 1 stop bit)
        TX_MODE       // Transmission mode
    );

    // Messages for each UART
    const char* message1 = "UART2";
    const char* message2 = "UART1";
    const char* message3 = "UART3";

    // Demonstrate sending messages on each UART
    while(1) {
        // Send messages on each UART
        serial1.printchaine(message1, 5);
        delay(100000);  // Small delay between transmissions

        serial2.printchaine(message2, 5);
        delay(100000);

        serial3.printchaine(message3, 5);
        delay(100000);
    }


}
