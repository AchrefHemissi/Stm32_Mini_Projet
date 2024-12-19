/*********************************************************************************/
/* OO STM32 Library : PinAsInput CLASS DECLARATION To configure GPIO Pins as Input 
	 E.D INSA TNov 2021 
	      Default Constructor: Floating
 
        Use:  PinAsInput  ObjectName (PA_i) , 
              where X is for GPIOX (A, B, C or D)
			        i is the pin Number (0 to 15)

		Example:  PinAsInput MyButton (PA_0);
************************************************************************************/

#include <stm32_wrapper_gpio.h>

namespace OOlayer {

class PinAsInput {
/**** Atribute to save PinName + to read Object (Pin) state (gpio_read()).  */
		PinName thepin;
public:



/***** Create a PinAsInput connected to the specified pin
     *
     *  @param pin PinAsInput pin to connect to
     */
		PinAsInput(PinName pin) :thepin(pin) { 
			gpio_init_in_def  (pin); 
		}
    

/***** Create a PinAsInput connected to the specified pin
     *
     *  @param pin PinAsInput pin to connect to
     *  @param mode the initial mode of the pin
     */
    PinAsInput(PinName pin, PinInMode mode):thepin(pin) {
        gpio_init_in (pin, mode);
    }
		
		
/***** Read the input, represented as 0 or 1 (int)
     *
     *  @returns
     *    An integer representing the state of the input pin,
     *    0 for logical 0, 1 for logical 1
     */
    int read() {
        return gpio_read(thepin);
    }
		
		
/***** An operator shorthand for read()
--> To Read an Input, use only The object Name
		Example:  int BtnState = MyButton;
     */
    operator int() {
        return read();
    }
}; //Class End

} //namespace
