#include "stm32f103xb.h"
#include "clk_maximizer.h"
#include "uart.h"
int main(){
    
    clock_72MHz();
    usart_init(USART1,9600);
    usart_send_string(USART1, "cuidate rey, te habla gemini");
    
}