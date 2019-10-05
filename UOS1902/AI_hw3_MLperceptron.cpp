#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <cmath>
#include <random>
using namespace std;

enum inputs {
	AND, OR, XOR, DONUT
};

vector<vector<double>> getInput(enum inputs mode);
vector<double> getTarget(enum inputs mode);
double sigmoid(double x);
double cost_MSE(vector<double> first, vector<double> second);
double makeRandomNum(int min, int max);
double dotProduct(vector<double> first, vector<double> second);
void printSingleVector(vector<double> vec);
void printDoubleVector(vector<vector<double>> vec);


class Node{
private:
	vector<double> input;    // 1-d vector
	vector<double> weight;
	double bias;
	double net;
	double output;
	double learning_rate;

	size_t input_size;

public:
	Node(size_t input_size, double learning_rate) {
		cout << "in Node sang sung ja" << endl;
		this->input_size = input_size;
		cout << "Node input size " << this->input_size << endl;
		this->learning_rate = learning_rate;
	}
	void init() {    // randomize weight vector and bias
		for (int i = 0; i < input_size; i++) {
			weight.push_back(makeRandomNum(-1, 1));    //weight scope is -1~ +1 real number 
			cout << "weight " << i << " = " << weight[i] << endl;
		}
		bias = makeRandomNum(-1, 1);
		cout << "bias = " << bias << endl << endl;
	}
	double signal(vector<double> input) {
		if (input.size() != input_size) {    //check input size 
			return 0;
		}
		this->input = input;

		net = dotProduct(weight, input) + bias;
		output = sigmoid(net);
		return output;

		cout << "net = " << net << endl;
		cout << "output = " << output << endl;
	}
	void train(double error) {
		for (int i = 0; i < input.size(); i++) {
			weight[i] = weight[i] + learning_rate * error * input[i];
		}
	}
};


class Layer {
private:
	vector<Node> layer;

	vector<vector<double>> input;    //batch ,2-d vector
	vector<vector<double>> output;
	vector<double> temp_output_row;

	size_t input_N;    //row number of input y
	size_t input_size;    //column number of input vector
	size_t node_N;

	double learning_rate;

public:
	Layer(size_t input_size, size_t input_N, size_t node_N, double learning_rate) {
		this->input_N = input_N;
		this->input_size = input_size;
		this->node_N = node_N;
		this->learning_rate = learning_rate;

		cout << "in Layer sang sung ja" << endl;
		cout << "Layer input N " << this->input_N << endl;
		cout << "Layer input size " << this->input_size << endl << endl;

		for (int i = 0; i < node_N; i++) {
			cout << "Node " << i << ": ";
			layer.push_back(Node(input_size, learning_rate));
			layer[i].init();
		}
	}
	vector<vector<double>> forward(vector<vector<double>> input) {
		if (input.size() != input_N) {
			cout << "layer input num err" << endl;
			return { {0} };
		}
		if (input[0].size() != input_size) {
			cout << "layer input size err" << endl;
			return { {0} };
		}

		for (int i = 0; i < input_N; i++) {
			temp_output_row.clear();
			for (int j = 0; j < node_N; j++) {
				temp_output_row.push_back(layer[j].signal(input[i]));
				cout << "input " << i << " node " << j << " output " << temp_output_row[j] << endl;
			}
			cout << endl;
			output.push_back(temp_output_row);
		}
		return output;
	}
	void backward();
};


class Network {
private:
	vector<Layer> network;

	vector<vector<double>> input;    // batch, 2-d vector
	size_t input_N;
	size_t input_size;
	vector<double> target;

	vector<size_t> layers;
	size_t layers_N;
	double learning_rate;
	double toleration;
public:
	Network(enum inputs mode, double learning_rate, double toleration, vector<size_t> layers) {
		this->input = getInput(mode);
		this->input_size = input[0].size();
		this->input_N = input.size();
		this->target = getTarget(mode);
		this->learning_rate = learning_rate;
		this->toleration = toleration;
		this->layers = layers;
		this->layers_N = layers.size();

		size_t node_N;
		for (int i = 0; i < layers_N; i++) {
			cout << "***** Layer" << i << ": ";
			node_N = layers[i];
			network.push_back(Layer(input_size, input_N, node_N, learning_rate));
		}
	}

	double cost_function(vector<vector<double>> net) {
		// output layer's node = 1
		// net will be (input_N, 1) 2-d vector. so we must transform the net to (1, input_N) 1-d vector
		vector<double> rotated_net;
		for (int i = 0; i < input_N; i++) {
			rotated_net.push_back(net[i][0]);
		}

		// compare 1 by 1 with target vector
		double cost;
		cost = cost_MSE(target, rotated_net);

		return cost;
	}

	double forward() {
		vector<vector<double>> temp_output;
		double cost;

		temp_output = input;    // setting starting input

		for (int i = 0; i < layers_N; i++) {
			cout << "go over layer " << i << endl;
			temp_output = network[i].forward(temp_output);
			printDoubleVector(temp_output);
		}
		printDoubleVector(temp_output);

		cost = this->cost_function(temp_output);
		return cost;
	}
	void backward();
};


vector<vector<double>> getInput(enum inputs mode) {
	vector<vector<double>> input;
	switch (mode) {
	case AND:
		input = { {0,0}, {1,0}, {0,1}, {1,1} };
		return input;
	case OR:
		input = { {0,0}, {1,0}, {0,1}, {1,1} };
		return input;
	case XOR:
		input = { {0,0}, {1,0}, {0,1}, {1,1} };
		return input;
	case DONUT:
		input = { {0,0},{0,1},{1,0},{1,1},{0.5,1},{1,0.5},{0,0.5},{0.5,0},{0.5,0.5} };
		return input;
	default:    //AND CASE
		input = { {0,0}, {1,0}, {0,1}, {1,1} };
		return input;
	}
}

vector<double> getTarget(enum inputs mode) {
	vector<double> target;
	switch (mode) {
	case AND:
		target = { 0, 0, 0, 1 };
		return target;
	case OR:
		target = { 0, 1, 1, 1 };
		return target;
	case XOR:
		target = { 0, 1, 1, 0 };
		return target;
	case DONUT:
		target = { 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		return target;
	default:    //AND CASE
		target = { 0, 0, 0, 1 };
		return target;
	}
}

double sigmoid(double x) {
	return 1 / (1 + exp(-x));
}

double cost_MSE(vector<double> first, vector<double> second) {
	size_t first_size = first.size();
	size_t second_size = second.size();
	double mse = 0;

	if (first_size != second_size) {
		return 0;
	}
	for (int i = 0; i < first_size; i++) {
		mse += pow((first[i] - second[i]), 2);    // summation of squared error
	}
	mse = mse / first_size;
	
	return mse;
}

double makeRandomNum(int min, int max) {
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(min, max);

	return dist(mt);
}

double dotProduct(vector<double> first, vector<double> second) {
	size_t first_size = first.size();
	size_t second_size = second.size();

	if (first_size != second_size) {
		cout << "vector.size is different" << endl;
		return 0;
	}
	else {
		double sum = 0;
		for (int i = 0; i < first_size; i++) {
			sum += first[i] * second[i];
		}
		return sum;
	}
}

void printSingleVector(vector<double> vec) {
	size_t size = vec.size();

	cout << "Single Vector {";
	for (int i = 0; i < size; i++) {
		cout << vec[i] << " ";
	}
	cout << "}" << endl;
}

void printDoubleVector(vector<vector<double>> vec) {
	size_t size_row = vec.size();
	size_t size_col = vec[0].size();

	cout << "Double Vector { " << endl;
	for (int i = 0; i < size_row; i++) {
		cout << "{ ";
		for (int j = 0; j < size_col; j++) {
			cout << vec[i][j] << " ";
		}
		cout << "}, " << endl;
	}
	cout << "} finished" << endl;

}

int main()
{

	double learning_rate = 0.5;
	double toleration = 0.5;
	vector<size_t> nodeNumberByLayer = { 3, 1 };

	Network network = Network(AND, learning_rate, toleration, nodeNumberByLayer);
	network.forward();

}
