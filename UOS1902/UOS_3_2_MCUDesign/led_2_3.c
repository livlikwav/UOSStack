/* GPIO로 LED 켜고 끄기 1번 예 
LED 8개가 연결되어 있는 포트 : Port A(PA)
- 비트7 : LED7(LD1), 비트6 : LED6(LD2) 
- … 
- 비트1 : LED1(LD7), 비트0 : LED0(LD8) */ 

#include <avr/io.h> // ATmega128 register 정의 

/* 1초 delay 함수 구현 : 중복(nested) for 문을 이용하고
적당한 값을 대입하여 찾음 */
void delay_sec(int sec)
{
    volatile int i, j, k;
    for (i=0; i<sec; i++)
    for (j=0; j<1000; j++)
    for (k=0; k<1000; k++)
    ;
}

/* 16Mhz 클록이므로 1600만개 정도의 명령어 수행이면 약 1초가 걸림 
C언어 1줄은 어셈블리 명령어로 약 1~10개에 해당하므로 평균 5개로 가정하고 계산해도 무방 */

int main() 
{
    unsigned char count = 1; // LED용 count는 양수 1 바이트
	//count 초기값 = 0
    DDRA = 0xff; // 포트 A를 출력 포트로 사용 

	while(1)
	{
        PORTA = count; // LED에 숫자 표시
        delay_sec(1); // 1초 기다림
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
