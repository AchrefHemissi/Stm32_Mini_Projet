/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/* External variables --------------------------------------------------------*/
extern char *txBuffer;
extern char *rxBuffer;
extern uint16_t txLength;
extern uint16_t rxLength;
extern uint16_t txCount;
extern uint16_t rxCount;

// Keep all existing interrupt handlers (NMI_Handler, HardFault_Handler, etc.)
// ...

/**
 * @brief  This function handles USART1 interrupt requests.
 * @param  None
 * @retval None
 */
void USART1_IRQHandler(void)
{
  if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
    // If there's still data to send
    if (txCount < txLength)
    {
      USART_SendData(USART1, txBuffer[txCount++]);
    }
    else
    {
      // Disable TX interrupt when done
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    }
  }

  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    // If there's space in the buffer
    if (rxCount < rxLength)
    {
      rxBuffer[rxCount++] = USART_ReceiveData(USART1);

      // If we've received all expected data
      if (rxCount == rxLength)
      {
        rxBuffer[rxCount] = '\0'; // Null terminate
        USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
      }
    }
  }
}

/**
 * @brief  This function handles USART2 interrupt requests.
 * @param  None
 * @retval None
 */
void USART2_IRQHandler(void)
{
  if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {
    if (txCount < txLength)
    {
      USART_SendData(USART2, txBuffer[txCount++]);
    }
    else
    {
      USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
    }
  }

  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    if (rxCount < rxLength)
    {
      rxBuffer[rxCount++] = USART_ReceiveData(USART2);

      if (rxCount == rxLength)
      {
        rxBuffer[rxCount] = '\0';
        USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
      }
    }
  }
}

/**
 * @brief  This function handles USART3 interrupt requests.
 * @param  None
 * @retval None
 */
void USART3_IRQHandler(void)
{
  if (USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  {
    if (txCount < txLength)
    {
      USART_SendData(USART3, txBuffer[txCount++]);
    }
    else
    {
      USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    }
  }

  if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
    if (rxCount < rxLength)
    {
      rxBuffer[rxCount++] = USART_ReceiveData(USART3);

      if (rxCount == rxLength)
      {
        rxBuffer[rxCount] = '\0';
        USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
      }
    }
  }
}