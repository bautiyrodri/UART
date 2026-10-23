#include "uart.h"
#include "CLK_MAXIMIZER.h"
#define PA9 9
#define PA10 10
#define PA2 2
#define PA3 3
#define PB10 10
#define PB11 11

int pclk = 0;
void usart_init(USART_TypeDef * USARTx, uint32_t baudrate){
    if(USARTx == USART1){
        pclk=72000000;

        RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
        RCC->APB2ENR|=RCC_APB2ENR_IOPAEN; 

        GPIOA->CRH &=~ (0XF<<(PA9%8)*4);//TX
        GPIOA->CRH |= (0XB<<(PA9%8)*4); 
    
        GPIOA->CRH &=~ (0XF<<(PA10%8)*4);//RX
        GPIOA->CRH |= (0X4<<(PA10%8)*4);

    }
    else if(USARTx == USART2){
        pclk=36000000;

        RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
        RCC->APB2ENR|=RCC_APB2ENR_IOPAEN; 

        GPIOA->CRL &=~ (0XF<<PA2*4);//tx
        GPIOA->CRL |= (0XB<<PA2*4); 
    
        GPIOA->CRL &=~ (0XF<<PA3*4);//rx
        GPIOA->CRL |= (0X4<<PA3*4);


    }
      
    else if(USARTx == USART3){
        pclk=36000000;

        RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
        RCC->APB2ENR|=RCC_APB2ENR_IOPBEN; 

        GPIOB->CRH &=~ (0XF<<(PB10%8)*4);
        GPIOB->CRH |= (0XB<<(PB10%8)*4); 
    
        GPIOB->CRH &=~ (0XF<<(PB11%8)*4);
        GPIOB->CRH |= (0X4<<(PB11%8)*4);

    
    
    }
float vel= (pclk/(16*baudrate));
int mantissa=vel;
int fraction=((vel-mantissa)*100);
USARTx->BRR=((fraction&0xf)|(mantissa<<4));
USARTx->CR1|=USART_CR1_UE|USART_CR1_TE|USART_CR1_RE;

}

void usart_send_char(USART_TypeDef * USARTx, uint8_t data){
    USARTx->DR=data;
    while(!(USARTx->SR & USART_SR_TXE)); 
}
void usart_send_string(USART_TypeDef* USARTx, char* TXT){
 while(*TXT){
    usart_send_char(USARTx, *TXT);
    TXT++;
}
}
uint8_t usart_receive_char(USART_TypeDef * USARTx){
    while(!(USARTx->SR & USART_SR_RXNE)); 
    return USARTx->DR;
}