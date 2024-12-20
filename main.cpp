#include "serial.h"
#include "stm32_wrapper_gpio.h"
#include <string.h>
char Receive_Buffer[20];  // Fixed-size buffer
	void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
//int main() {


	/*read
	OOlayer::Serial serial;

  while(1)
	{
		strcpy(Receive_Buffer, serial.readchaine(20)); // Copy data into Receive_Buffer
 // Copy data into Receive_Buffer
	}			
*/
    //OOlayer::Serial serial1;
    
    // 2. Second Serial object - COM1 with custom baud rate
   // OOlayer::Serial serial2(COM1, PA_9, PA_10, SPEED_115200);
    
    // 3. Third Serial object - COM3 with full custom configuration
   // OOlayer::Serial serial3(
//        COM3,           // COM port
//        PB_10,          // TX pin
//        PB_11,          // RX pin
//        SPEED_19200,    // Baud rate
//        CONFIG_9E1,     // Configuration (9-bit, even parity, 1 stop bit)
//        TX_MODE       // Transmission mode
//    );

    // Messages for each UART
    //const char* message1 = "UART2";
    //const char* message2 = "UART1";
    //const char* message3 = "UART3";

    // Demonstrate sending messages on each UART
   // while(1) {
        // Send messages on each UART
   //     serial1.printchaine(message1, 5);
     //   delay(100000);  // Small delay between transmissions

       // serial2.printchaine(message2, 5);
        //delay(100000);

        //serial3.printchaine(message3, 5);
        //delay(100000);
   // }
	 
volatile uint32_t tx1_count = 0;  // Count of USART1 transmissions
volatile uint32_t rx1_count = 0;  // Count of USART1 receptions
volatile uint32_t tx2_count = 0;  // Count of USART2 transmissions
volatile uint32_t rx2_count = 0;  // Count of USART2 receptions
		
int main() {
	// Test messages
	const char message1[] = "Hello from USART1!";
	const char message2[] = "Response from USART2";

	// Create two Serial objects for testing
	OOlayer::Serial Com1(COM1, PA_9, PA_10, SPEED_9600);  // USART1 on PA9 (TX) and PA10 (RX)
	OOlayer::Serial Com2(COM2, PA_2, PA_3, SPEED_9600);   // USART2 on PA2 (TX) and PA3 (RX)

	// Flag to track message reception
	volatile bool messageReceived = false;

	// Function prototypes
	void Delay(uint32_t time);
    
    while(1)
    {
        // Send message from USART1
        Com1.ITprintchaine((char*)message1, strlen(message1));
        
        // Wait for transmission to complete
        Delay(1000);
        
        // Start receiving on USART2
        char* received = Com2.ITreadchaine(strlen(message1));
        
        // Wait for reception
        Delay(1000);
        
        // Send response from USART2
        Com2.ITprintchaine((char*)message2, strlen(message2));
        
        // Wait for transmission
        Delay(1000);
        
        // Receive on USART1
        received = Com1.ITreadchaine(strlen(message2));
        
        // Wait for reception
        Delay(1000);
         
        // Wait before next cycle
        Delay(2000);
    }
}
void Delay(uint32_t time)
{
    while(time--);
}

