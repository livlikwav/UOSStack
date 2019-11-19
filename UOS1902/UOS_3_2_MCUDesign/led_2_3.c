/* GPIO�� LED �Ѱ� ���� 1�� �� 
LED 8���� ����Ǿ� �ִ� ��Ʈ : Port A(PA)
- ��Ʈ7 : LED7(LD1), ��Ʈ6 : LED6(LD2) 
- �� 
- ��Ʈ1 : LED1(LD7), ��Ʈ0 : LED0(LD8) */ 

#include <avr/io.h> // ATmega128 register ���� 

/* 1�� delay �Լ� ���� : �ߺ�(nested) for ���� �̿��ϰ�
������ ���� �����Ͽ� ã�� */
void delay_sec(int sec)
{
    volatile int i, j, k;
    for (i=0; i<sec; i++)
    for (j=0; j<1000; j++)
    for (k=0; k<1000; k++)
    ;
}

/* 16Mhz Ŭ���̹Ƿ� 1600���� ������ ��ɾ� �����̸� �� 1�ʰ� �ɸ� 
C��� 1���� ����� ��ɾ�� �� 1~10���� �ش��ϹǷ� ��� 5���� �����ϰ� ����ص� ���� */

int main() 
{
    unsigned char count = 1; // LED�� count�� ��� 1 ����Ʈ
	//count �ʱⰪ = 0
    DDRA = 0xff; // ��Ʈ A�� ��� ��Ʈ�� ��� 

	while(1)
	{
        PORTA = count; // LED�� ���� ǥ��
        delay_sec(1); // 1�� ��ٸ�
		if(count == 128)
		{
		    count = 1;
		}
		else
		{
            count = count * 2; // 1, 2, 4, 8, 16, 32, 64, 128
		}
	}

}
