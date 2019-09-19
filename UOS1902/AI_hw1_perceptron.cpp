/*
입력은 00 01 10 11으로 정해져있음
맨 처음에 가중치1, 2, 임계값 랜덤으로 초기화함
매 라운드 가중치1, 2, 임계값 입력받게 함.
이번 과제는 N = 2 이지만, N 값을 입력받을 수 있도록 만들기.
*/

#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

//전역변수 선언
int N = 2; //perceptron's N
vector<int> WEIGHT; //가중치
int theta; //임계값
int flag; //적합한 퍼셉트론을 찾았는지 여부

int INPUT[][4] = { {0,0}, {0,1}, {1,0}, {1,1} }; //정해진 INPUT 값
int AND_GATE[4] = {0, 0, 0, 1}; //정해진 AND_GATE OUTPUT 값

//함수
void init_perceptron(); //랜덤한 가중치와 임계값을 대입합니다.
void set_perceptron(); //사용자가 가중치와 임계값을 입력합니다.
void do_perceptron(); //정해진 변수값대로 출력과 AND_GATE가 동일한지 체크를 수행합니다.
void check_perceptron(int []); //AND_GATE의 출력값과 동일한지 체크합니다.

int main()
{

    cout << "인공지능 과제 1 : Perceptron 구현 \n"; 

	cout << "랜덤한 weight와 theta를 대입합니다 \n\n";
	init_perceptron();
	do_perceptron();
	if (flag == 0) {
		cout << "이 퍼셉트론은 AND GATE와 동일하게 작동합니다. \n\n";
	}
	else {
		cout << "틀린 갯수는 " << flag << "개입니다.\n\n";
	}

	for (;;) {//무한 loop
		set_perceptron();
		do_perceptron();
		if (flag == 0) {
			cout << "이 퍼셉트론은 AND GATE와 동일하게 작동합니다. \n\n";
			break;
		}
		else {
			cout << "틀린 갯수는 " << flag << "개입니다.\n\n";
		}
	}
	
}

void init_perceptron() {
	int init_w;
	srand((unsigned int)time(NULL)); //씨드값으로 현재 시간 입력

	for (int i = 0; i < N; i++) { //가중치 랜덤 초기화
		init_w = rand() % 100;
		WEIGHT.push_back(init_w);
		cout << "w" << i << " = " << init_w << "\n";
	}
	theta = rand() % 100; //임계값 랜덤 초기화
	cout << "theta = " << theta << "\n";
}

void set_perceptron() {
	//가중치 입력
	for (int i = 0; i < N; i++) {
		cout << "w" << i << "는 : ";
		cin >> WEIGHT[i];
	}
	//임계값 입력
	cout << "theta는 : ";
	cin >> theta;
}

void do_perceptron() {
	int OUTPUT[4];
	int signal;

	for (int i = 0; i < 4; i++) {
		signal = 0;

		for (int j = 0; j < N; j++) {
			signal = signal + WEIGHT[j] * INPUT[i][j];
		}

		if (signal >= theta) {
			OUTPUT[i] = 1;
			cout << "1 ";
		}
		else {
			OUTPUT[i] = 0;
			cout << "0 ";
		}
	}
	cout << "\n";

	check_perceptron(OUTPUT);
}

void check_perceptron(int OUTPUT[]) {
	flag = 0; //플래그값 초기화

	for (int i = 0; i < 4; i++) {
		if (OUTPUT[i] != AND_GATE[i]) {
			flag++;
		}
	}
}
