#include <avr/io.h> // ATmega128 register ���� 
#define F_CPU 16000000UL
#include <util/delay.h>
unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67};
unsigned char fnd[4] = {0x08, 0x04, 0x02, 0x01};

// GPIO�� FND 1�� ǥ���ϱ� 0~9 DISPLAY
int main()
{
    int i = 0;
    DDRC = 0xff; // C ��Ʈ�� ��� ��� 
    DDRG = 0x0f; // G ��Ʈ�� 4���� ���
    while(1)
	{
        for (i=0; i<4; i++)
    	{ 
            PORTG = fnd[i]; // ���ʷ� fnd����
    	    PORTC = digit[i + 1]; //���� '1'-'4'�� ���ʷ� ���
    		_delay_ms(10); //�ܻ�ȿ�� ���ؼ��� 33ms �Ѿ�� �ȵ�
    	}
	}
}
