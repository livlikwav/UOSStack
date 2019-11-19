#include <avr/io.h> // ATmega128 register ���� 
#define F_CPU 16000000UL
#include <util/delay.h>
unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67};

// GPIO�� FND 1�� ǥ���ϱ� 0~9 DISPLAY
int main()
{
    int i = 0;
    DDRC = 0xff; // C ��Ʈ�� ��� ��� 
    DDRG = 0x0f; // G ��Ʈ�� 4���� ��� 
    PORTG = 0x01; // ���� ������ digit ���� 
	
    for (i=0; i<10; i++)
	{
	    PORTC = digit[i]; //���� '0'-'9'�� ���ʷ� ���
		_delay_ms(1000);
	}
}
