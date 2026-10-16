#include "stm32f103xb.h"
#include "clk_maximizer.h"
#include "uart.h"
int main(){
    usart_init(USART1,9600);
    usart_send_char(USART1, 'h');
    while(1){
    }
}