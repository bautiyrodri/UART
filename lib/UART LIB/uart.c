#include "uart.h"
#include "CLK_MAXIMIZER.H"

void usart_init(USART_TypeDef * USARTx, uint32_t baudrate);
RCC->APB2ENR|=RCC_APB2ENR_