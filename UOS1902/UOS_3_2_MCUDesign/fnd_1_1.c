#include <avr/io.h> // ATmega128 register ���� 

void main()
{
    DDRC = 0xff; // C ��Ʈ�� ��� ��� 
    DDRG = 0x0f; // G ��Ʈ�� 4���� ��� 
    PORTC = 0x3f; // ��0�� ǥ�� 
    PORTG = 0x01; // ���� ������ digit ���� 
}
