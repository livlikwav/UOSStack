#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

int N = 2; //퍼셉트론의 입력 차원
int flag = 0;//무한 loop 빠져나오기 위한 flag
double INPUT[][4] = { {0,0}, {0,1}, {1,0}, {1,1} }; //정해진 INPUT 값


class perceptron {
private :
	vector<double> WEIGHT; //가중치
	vector<double> GOAL;    //GATE별 목표 출력값

	double theta; //임계값
	double OUTPUT[4];    //퍼셉트론 출력 값 ( != SIGNAL)
	double grad;    //기울기
	double bias;    //편향
	int error; //signal과 gate의 값이 상이한 횟수

public :
	perceptron(int n) {    // GATE 설정
		switch (n) {
		case 0:    // AND GATE
			cout << "AND GATE \n";
			this->GOAL = { 0, 0, 0, 1 };
			break;
		case 1:    // OR GATE
			cout << "OR GATE \n";
			this->GOAL = { 0, 1, 1, 1 };
			break;
		case 2:    // XOR GATE
			cout << "XOR GATE \n";
			this->GOAL = { 0, 1, 1, 0 };
			break;
		default:    // AND GATE
			cout << "AND GATE \n";
			this->GOAL = { 0, 0, 0, 1 };
			break;
		}

		//결과 파일 생성
		fstream fs;
		fs.open("result.csv", ios::out);
		fs << "w0,w1,theta, gradient, bias" << endl;
		fs.close();

		//에러파일 생성
		fs.open("error.csv", ios::out);
		fs << "error" << endl;
		fs.close();
	}
	void init() {//랜덤한 가중치와 임계값을 대입합니다.
		int init_w;
		srand((unsigned int)time(NULL)); //씨드값으로 현재 시간 입력

		for (int i = 0; i < N; i++) { //가중치 랜덤 초기화
			init_w = rand() % 100;
			this->WEIGHT.push_back(init_w);
			cout << "w" << i << " = " << init_w << "\n";
		}
		this->theta = rand() % 100; //임계값 랜덤 초기화
		cout << "theta = " << this->theta << "\n";
	}
	void optimize() {    //각 가중치를 학습시킵니다.
		for (int i = 0; i < 4; i++) {
			this->WEIGHT[0] = this->WEIGHT[0] + 1*(this->GOAL[i] - this->OUTPUT[i])*INPUT[i][0];
			this->WEIGHT[1] = this->WEIGHT[1] + 1*(this->GOAL[i] - this->OUTPUT[i])*INPUT[i][1];
		}
		cout << "w0 = " << this->WEIGHT[0] << "\n";
		cout << "w1 = " << this->WEIGHT[1] << "\n";
		cout << "theta = " << this->theta << "\n";
	}
	void signal() {//정해진 변수값대로 출력을 수행합니다.
		int signal;

		for (int i = 0; i < 4; i++) {
			signal = 0;

			for (int j = 0; j < N; j++) {
				signal = signal + this->WEIGHT[j] * INPUT[i][j];
			}

			if (signal >= theta) {
				this->OUTPUT[i] = 1;
				cout << "1 ";
			}
			else {
				this->OUTPUT[i] = 0;
				cout << "0 ";
			}
		}
		cout << " output finished \n";
	}
	void check() {//GATE의 출력값과 동일한지 체크합니다.
		this->error = 0;

		for (int i = 0; i < 4; i++) {
			if (this->OUTPUT[i] != this->GOAL[i]) {
				this->error++;
			}
		}

		if (this->error == 0) {
			cout << "이 퍼셉트론은 GATE와 동일하게 작동합니다. \n\n";
			flag = 1;
		}
		else {
			cout << "틀린 갯수는 " << this->error << "개입니다.\n\n";
		}
	}
	void write_file() {
		this->grad = -(this->WEIGHT[0] / this->WEIGHT[1]);
		this->bias = this->theta / this->WEIGHT[1];
		//결과파일 생성
		fstream fs;
		fs.open("result.csv", ios::app);
		fs << this->WEIGHT[0] << "," << this->WEIGHT[1] << "," << this->theta << "," << this->grad << "," << this->bias << endl;
		fs.close();
		//에러파일 생성
		fs.open("error.csv", ios::app);
		fs << this->error << endl;
		fs.close();
	}
};

int main()
{

	cout << "인공지능 과제 2 : n차원퍼셉트론 학습 \n";

	perceptron perc(0);


	perc.init();
	for (;;) {
		perc.signal();
		perc.check();
		perc.write_file();
		if (flag == 1) {
			cout << "flag is " << flag << endl;
			cout << "optimization finished" << endl;
			break;
		}
		perc.optimize();
	}
}

/*
void set_perceptron() {//사용자가 가중치와 임계값을 입력합니다.
	//가중치 입력
	for (int i = 0; i < N; i++) {
		cout << "w" << i << "는 : ";
		cin >> WEIGHT[i];
	}
	//임계값 입력
	cout << "theta는 : ";
	cin >> theta;
}
*/