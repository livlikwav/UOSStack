/* LED�� X-mas Tree ����� */
#include <avr/io.h> // ATmega128 register ���� 
#include <stdlib.h> // rand() ����ϱ� ����
void delay_sec(int sec) 
{
    volatile int i, j, k;
    for (i=0; i<sec; i++) 
        for (j=0; j<1000; j++) 
            for (k=0; k<1000; k++) ;
}

int main( ) 
{ 
    DDRA = 0xff; // ��Ʈ A�� ��� ��Ʈ�� ��� 
    while(1) // ���ѷ��� ���� 
    { 
        PORTA = rand( ); // 0~255 ���� �߻� �� LED ǥ�� 
        delay_sec(rand()%3); // 0~2 ���� delay �ð� �߻� �� �ð� ����
    } 
}
