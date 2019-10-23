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
double sigmoid_derivative(double x);
double loss_MSE(vector<double> target, vector<double>output);
double makeRandomNum(int min, int max);
double dotProduct(vector<double> first, vector<double> second);
void printSingleVector(vector<double> vec);
void printDoubleVector(vector<vector<double>> vec);


class Node{
private:
	vector<double> input;    // size (input_size)
	vector<double> weight;    // size (input_size)
	int input_size;

	int node_id;
	double bias;
	double learning_rate;

	double net;
	double output;
	double delta;
public:
	Node(int node_id, int input_size, double learning_rate) {
		this->node_id = node_id;
		this->input_size = input_size;
		this->learning_rate = learning_rate;

		// randomize weight vector and bias
		for (int i = 0; i < input_size; i++) {
			weight.push_back(makeRandomNum(-1, 1));    //weight scope is -1~ +1 real number 
		}
		bias = makeRandomNum(-1, 1);

		cout << "Node " << node_id << ": "; //DEBUG
		cout << "input size " << this->input_size << endl; //DEBUG
	}
	int getNodeID() {
		return this->node_id;
	}
	double getNet() {
		return this->net;
	}
	double getDelta() {
		return this->delta;
	}
	double getBias() {
		return this->bias;
	}
	vector<double> getWeight() {
		return this->weight;
	}
	void setDelta(double delta) {
		this->delta = delta;
	}
	double forward(vector<double> input) {
		//save for backpropagation
		this->input = input;
		this->net = dotProduct(weight, input) + this->bias;
		this->output = sigmoid(net);

		return output;
	}
	void update_delta(vector<Node *> pro_node) {
		// summation ( pro_node delta * f'(pro_node net) * pro_node weight
		double pro_delta = 0;
		double pro_net = 0;
		double pro_weight = 0;
		double sum = 0;

		for (int i = 0; i < pro_node.size(); i++) {
			pro_delta = pro_node[i]->getDelta();
			pro_net = pro_node[i]->getNet();
			pro_weight = pro_node[i]->getWeight()[this->node_id];

			sum += pro_delta * sigmoid_derivative(pro_net) * pro_weight;
		}

		delta = sum;
	}
	void update_w() {
		// weight = weight - delta * f'(my net) * my net
		for (int i = 0; i < weight.size(); i++) {
			this->weight[i] -= this->delta * sigmoid_derivative(this->net) * this->input[i];
		}
	}
	void update_bias() {
		this->bias -= this->delta * sigmoid_derivative(this->net) * 1;
	}
};


class Layer {
private:
	vector<Node *> layer;

	vector<double> input;    // size (input_size)
	vector<double> output;    // size (node_N)

	int layer_id;
	int input_size;    // number of input nodes
	int node_N;    // node number of this layer

	double learning_rate;

public:
	Layer(int layer_id, int input_size, int node_N, double learning_rate) {
		this->layer_id = layer_id;
		this->input_size = input_size;
		this->node_N = node_N;
		this->learning_rate = learning_rate;

		cout << "Layer input size " << this->input_size << endl; //DEBUG

		for (int i = 0; i < node_N; i++) {
			Node * node_address = new Node(i, input_size, learning_rate);
			layer.push_back(node_address);
		}
	}
	vector<Node *> getLayer() {
		return layer;
	}
	vector<double> getInput() {
		return input;
	}
	vector<double> forward(vector<double> input) {
		this->input = input;
		vector<double> output;

		for (int i = 0; i < node_N; i++) {
			output.push_back(layer[i]->forward(input));
		}

		return output;
	}
	void update_delta(vector<Node *> pro_node) {
		for (int i = 0; i < node_N; i++) {
			layer[i]->update_delta(pro_node);
		}
	}
	void update_nodes() {
		for (int i = 0; i < node_N; i++) {
			layer[i]->update_w();
			layer[i]->update_bias();
		}
	}
	void set_output_delta(double output_delta) {
		// output delta will be ( -( t - o ) )
		this->layer[0]->setDelta(output_delta);
	}
	vector<Node *> getNodeList() {
		return layer;
	}
};


class Network {
private:
	vector<Layer *> network;

	vector<vector<double>> input;    // batch, 2-d vector
	int input_N;    // decide number of train 
	int input_size;
	vector<double> target;

	vector<int> layers;    // vector :: node number of each layer
	int layer_N;    // number of layer

	double learning_rate;
	double toleration;
	int epoch = 0;

	// DEBUG, for print
	vector<vector<double>> output_container;
	vector<double> MSE_container;
public:
	vector<double> layer_container;

	Network(enum inputs mode, double learning_rate, double toleration, vector<int> layers) {
		//initialize
		this->input = getInput(mode);
		this->target = getTarget(mode);
		this->learning_rate = learning_rate;
		this->toleration = toleration;
		this->layers = layers;
		//set property
		this->input_size = (int)input[0].size();
		this->input_N = (int)input.size();
		this->layer_N = (int)layers.size();

		int node_N;
		for (int i = 0; i < layer_N; i++) {
			cout << "***** Layer" << i << ": ";
			node_N = layers[i];
			Layer * layer_address = new Layer(i, input_size, node_N, learning_rate);
			network.push_back(layer_address);
			// pre to pro layer, pre node_N is pro's input_size
			this->input_size = node_N;
		}
	}

	double forward(vector<double> input) {
		vector<double> output;
		double output_double;
		output = input;

		for (int i = 0; i < layer_N; i++) {
			output = network[i]->forward(output);
		}
		
		// transform to 1 double value, because output node is 1
		output_double = output[0];
		return output_double;
	}

	void backward(double error_derivative) {
		// set first delta
		network[layer_N - 1]->set_output_delta(error_derivative);    // network[layer_N - 1] == output layer

		// update all delta in layer
		for (int i = (layer_N - 2); i >= 0; i--) {    // layer_N - 2 == last hidden layer
			network[i]->update_delta(network[i + 1]->getNodeList());
		}
		// updeta all weight and bias in layer
		for (int j = 0; j < layer_N; j++) {
			network[j]->update_nodes();
		}
	}
	double doEpoch() {
		vector<double> network_output;
		double ith_error_derivative;

		//do epoch each input (4 times)
		for (int i = 0; i < input_N; i++) {   
			network_output.push_back(this->forward(input[i]));
			ith_error_derivative = -(target[i] - network_output[i]);    // dError/dout = -(target - output)
			this->backward(ith_error_derivative);
		}
		//FOR PRINT
		save_containers();

		// return loss function
		output_container.push_back(network_output); //DEBUG
		return loss_MSE(target, network_output);
	}

	void train() {
		double MSE = 0;
		int epoch_count = 0;

		for (;;) {
			if (epoch_count % 100 == 0) {
				cout << "Epoch#: #" << epoch_count << endl; //DEBUG
			}

			MSE = doEpoch();
			MSE_container.push_back(MSE);
			epoch_count++;

			if (MSE < toleration) {
				cout << "MSE < toleration" << endl;
				cout << "MSE = " << MSE << endl;
				cout << "toleration = " << toleration << endl;
				break;
			}
		}

		cout << "this network's output vector: ";//DEBUG
		printDoubleVector(output_container);//DEBUG
		cout << "Epoch# in training: #" << epoch_count << endl; //DEBUG

		//FOR PRINT
		fprint_MSE();
		fprint_network();
	}
	void fprint_MSE() {
		fstream fs;
		fs.open("error.csv", ios::out);

		for (int i = 0; i < MSE_container.size(); i++) {
			fs << MSE_container[i] << endl;
		}

		fs.close();
	}
	void fprint_network() {
		fstream fs;
		int colSize = (int)layer_container.size();
		//grad, bias, grad, bias
		fs.open("weights.csv", ios::out);
		fs << "w0, w1, bias0, w2, w3, bias1" << endl;

		for (int i = 0; i < (colSize / 6); i++) {
			fs << layer_container[i * 6] << ",";
			fs << layer_container[i * 6 + 1] << ",";
			fs << layer_container[i * 6 + 2] << ",";
			fs << layer_container[i * 6 + 3] << ",";
			fs << layer_container[i * 6 + 4] << ",";
			fs << layer_container[i * 6 + 5] << ",";
			fs << endl;
		}
		fs.close();
	}
	void save_containers() {
		double w0, w1, w2, w3, node0_bias, node1_bias;

		//save layer
		w0 = network[0]->getLayer()[0]->getWeight()[0];
		w1 = network[0]->getLayer()[0]->getWeight()[1];
		w2 = network[0]->getLayer()[1]->getWeight()[0];
		w3 = network[0]->getLayer()[1]->getWeight()[1];
		node0_bias = network[0]->getLayer()[0]->getBias();
		node1_bias = network[0]->getLayer()[1]->getBias();
		layer_container.push_back(w0);
		layer_container.push_back(w1);
		layer_container.push_back(node0_bias);
		layer_container.push_back(w2);
		layer_container.push_back(w3);
		layer_container.push_back(node1_bias);
	}
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

double sigmoid_derivative(double x) {
	double y = sigmoid(x);
	return y * (1 - y);
}

double loss_MSE(vector<double> target, vector<double>output) {
	double mse = 0;

	if (target.size() != output.size()) {
		cout << "in loss_MSE(target, output), two vectors' size are different" << endl;
		return 0;
	}
	// sum ( target - output)^2
	for (int i = 0; i < target.size(); i++) {
		mse += pow((target[i] - output[i]), 2);    
	}
	// return = sum( target - output)^2 / 2.0
	return mse / 2.0;
}

double makeRandomNum(int min, int max) {
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(min, max);

	return dist(mt);
}

double dotProduct(vector<double> first, vector<double> second) {
	int first_size = (int)first.size();
	int second_size = (int)second.size();

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
	int size = (int)vec.size();

	cout << "{";
	for (int i = 0; i < size; i++) {
		cout << vec[i] << " ";
	}
	cout << "}" << endl;
}

void printDoubleVector(vector<vector<double>> vec) {
	int size_row = (int)vec.size();
	int size_col = (int)vec[0].size();

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
	double learning_rate = 7;
	double toleration = 0.05;
	vector<int> nodeNumberByLayer = {2, 1};

	Network network = Network(XOR, learning_rate, toleration, nodeNumberByLayer);

	//TEST
	network.train();


}
		