#include <avr/io.h> // ATmega128 register 정의 
#define F_CPU 16000000UL
#include <util/delay.h>
unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67};
unsigned char fnd[4] = {0x08, 0x04, 0x02, 0x01};

// GPIO로 FND 1개 표시하기 0~9 DISPLAY
int main()
{
    int i = 0;
    DDRC = 0xff; // C 포트는 모두 출력 
    DDRG = 0x0f; // G 포트도 4개는 출력
    while(1)
	{
        for (i=0; i<4; i++)
    	{ 
            PORTG = fnd[i]; // 차례로 fnd선택
    	    PORTC = digit[i + 1]; //숫자 '1'-'4'를 차례로 출력
    		_delay_ms(10); //잔상효과 위해서는 33ms 넘어서는 안됨
    	}
	}
}
