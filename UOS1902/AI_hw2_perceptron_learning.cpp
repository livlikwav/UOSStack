#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

int N = 2; //�ۼ�Ʈ���� �Է� ����
int flag = 0;//���� loop ���������� ���� flag
double INPUT[][4] = { {0,0}, {0,1}, {1,0}, {1,1} }; //������ INPUT ��


class perceptron {
private :
	vector<double> WEIGHT; //����ġ
	vector<double> GOAL;    //GATE�� ��ǥ ��°�

	double theta; //�Ӱ谪
	double OUTPUT[4];    //�ۼ�Ʈ�� ��� �� ( != SIGNAL)
	double grad;    //����
	double bias;    //����
	int error; //signal�� gate�� ���� ������ Ƚ��

public :
	perceptron(int n) {    // GATE ����
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

		//��� ���� ����
		fstream fs;
		fs.open("result.csv", ios::out);
		fs << "w0,w1,theta, gradient, bias" << endl;
		fs.close();

		//�������� ����
		fs.open("error.csv", ios::out);
		fs << "error" << endl;
		fs.close();
	}
	void init() {//������ ����ġ�� �Ӱ谪�� �����մϴ�.
		int init_w;
		srand((unsigned int)time(NULL)); //���尪���� ���� �ð� �Է�

		for (int i = 0; i < N; i++) { //����ġ ���� �ʱ�ȭ
			init_w = rand() % 100;
			this->WEIGHT.push_back(init_w);
			cout << "w" << i << " = " << init_w << "\n";
		}
		this->theta = rand() % 100; //�Ӱ谪 ���� �ʱ�ȭ
		cout << "theta = " << this->theta << "\n";
	}
	void optimize() {    //�� ����ġ�� �н���ŵ�ϴ�.
		for (int i = 0; i < 4; i++) {
			this->WEIGHT[0] = this->WEIGHT[0] + 1*(this->GOAL[i] - this->OUTPUT[i])*INPUT[i][0];
			this->WEIGHT[1] = this->WEIGHT[1] + 1*(this->GOAL[i] - this->OUTPUT[i])*INPUT[i][1];
		}
		cout << "w0 = " << this->WEIGHT[0] << "\n";
		cout << "w1 = " << this->WEIGHT[1] << "\n";
		cout << "theta = " << this->theta << "\n";
	}
	void signal() {//������ ��������� ����� �����մϴ�.
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
	void check() {//GATE�� ��°��� �������� üũ�մϴ�.
		this->error = 0;

		for (int i = 0; i < 4; i++) {
			if (this->OUTPUT[i] != this->GOAL[i]) {
				this->error++;
			}
		}

		if (this->error == 0) {
			cout << "�� �ۼ�Ʈ���� GATE�� �����ϰ� �۵��մϴ�. \n\n";
			flag = 1;
		}
		else {
			cout << "Ʋ�� ������ " << this->error << "���Դϴ�.\n\n";
		}
	}
	void write_file() {
		this->grad = -(this->WEIGHT[0] / this->WEIGHT[1]);
		this->bias = this->theta / this->WEIGHT[1];
		//������� ����
		fstream fs;
		fs.open("result.csv", ios::app);
		fs << this->WEIGHT[0] << "," << this->WEIGHT[1] << "," << this->theta << "," << this->grad << "," << this->bias << endl;
		fs.close();
		//�������� ����
		fs.open("error.csv", ios::app);
		fs << this->error << endl;
		fs.close();
	}
};

int main()
{

	cout << "�ΰ����� ���� 2 : n�����ۼ�Ʈ�� �н� \n";

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
void set_perceptron() {//����ڰ� ����ġ�� �Ӱ谪�� �Է��մϴ�.
	//����ġ �Է�
	for (int i = 0; i < N; i++) {
		cout << "w" << i << "�� : ";
		cin >> WEIGHT[i];
	}
	//�Ӱ谪 �Է�
	cout << "theta�� : ";
	cin >> theta;
}
*/