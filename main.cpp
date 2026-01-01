#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>
#include <bitset>
#include <iomanip>

class NeuralNetwork {
private:
	int input_nodes;
	int hidden_nodes;
	int output_nodes;
	double learning_rate;

	std::vector<std::vector<double>> weights_ih; 
	std::vector<std::vector<double>> weights_ho; 
	std::vector<double> bias_h;
	std::vector<double> bias_o;

	double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
	double sigmoid_derivative(double x) { return x * (1.0 - x); }

public:
	NeuralNetwork(int input, int hidden, int output, double lr)
		: input_nodes(input), hidden_nodes(hidden), output_nodes(output), learning_rate(lr) {
		
		std::default_random_engine gen(std::random_device{}());
		
		// Xavier/Glorot Initialization
		auto xavier_init = [&](int fan_in, int fan_out) {
			double limit = sqrt(6.0 / (fan_in + fan_out));
			return std::uniform_real_distribution<double>(-limit, limit);
		};

		auto dist_ih = xavier_init(input_nodes, hidden_nodes);
		weights_ih.resize(hidden_nodes, std::vector<double>(input_nodes));
		for (auto& row : weights_ih) for (auto& val : row) val = dist_ih(gen);

		auto dist_ho = xavier_init(hidden_nodes, output_nodes);
		weights_ho.resize(output_nodes, std::vector<double>(hidden_nodes));
		for (auto& row : weights_ho) for (auto& val : row) val = dist_ho(gen);

		bias_h.assign(hidden_nodes, 0.0);
		bias_o.assign(output_nodes, 0.0);
	}

	std::vector<double> feedForward(const std::vector<double>& input) {
		std::vector<double> hidden(hidden_nodes);
		for (int i = 0; i < hidden_nodes; i++) {
			double sum = 0;
			for (int j = 0; j < input_nodes; j++) sum += input[j] * weights_ih[i][j];
			hidden[i] = sigmoid(sum + bias_h[i]);
		}

		std::vector<double> output(output_nodes);
		for (int i = 0; i < output_nodes; i++) {
			double sum = 0;
			for (int j = 0; j < hidden_nodes; j++) sum += hidden[j] * weights_ho[i][j];
			output[i] = sigmoid(sum + bias_o[i]);
		}
		return output;
	}

	void train(const std::vector<double>& input, const std::vector<double>& target) {
		// --- Forward Pass ---
		std::vector<double> hidden(hidden_nodes);
		for (int i = 0; i < hidden_nodes; i++) {
			double sum = 0;
			for (int j = 0; j < input_nodes; j++) sum += input[j] * weights_ih[i][j];
			hidden[i] = sigmoid(sum + bias_h[i]);
		}

		std::vector<double> output(output_nodes);
		for (int i = 0; i < output_nodes; i++) {
			double sum = 0;
			for (int j = 0; j < hidden_nodes; j++) sum += hidden[j] * weights_ho[i][j];
			output[i] = sigmoid(sum + bias_o[i]);
		}

		// --- Backpropagation ---

		// 1. Calculate Output Gradients (Delta Output)
		std::vector<double> output_deltas(output_nodes);
		for (int i = 0; i < output_nodes; i++) {
			double error = target[i] - output[i];
			output_deltas[i] = error * sigmoid_derivative(output[i]);
		}

		// 2. Calculate Hidden Gradients (Delta Hidden)
		std::vector<double> hidden_deltas(hidden_nodes);
		for (int i = 0; i < hidden_nodes; i++) {
			double error_sum = 0;
			for (int j = 0; j < output_nodes; j++) {
				error_sum += output_deltas[j] * weights_ho[j][i];
			}
			hidden_deltas[i] = error_sum * sigmoid_derivative(hidden[i]);
		}

		// 3. Update Weights and Biases (Output Layer)
		for (int i = 0; i < output_nodes; i++) {
			for (int j = 0; j < hidden_nodes; j++) {
				weights_ho[i][j] += output_deltas[i] * hidden[j] * learning_rate;
			}
			bias_o[i] += output_deltas[i] * learning_rate;
		}

		// 4. Update Weights and Biases (Hidden Layer)
		for (int i = 0; i < hidden_nodes; i++) {
			for (int j = 0; j < input_nodes; j++) {
				weights_ih[i][j] += hidden_deltas[i] * input[j] * learning_rate;
			}
			bias_h[i] += hidden_deltas[i] * learning_rate;
		}
	}
};


int bitreadings_8(int& cnt, std::ifstream& tgt){
	int varSize = 0;
	int maxCount = cnt + 4;
	while(cnt < maxCount){
		unsigned char cur = 0;
		tgt.read((char*)&cur, sizeof(cur));
		varSize = (varSize << 8);
		varSize += (unsigned int)cur;
		cnt+=1;
	}
	return varSize;
}

int main() {
	// 28*28 = 784 input, 128 hidden, 10 output
	NeuralNetwork nn(784, 128, 10, 0.1);

	std::ifstream image;
	std::ifstream label;
	image.open("train-images-idx3-ubyte/train-images.idx3-ubyte", std::ios::binary);
	label.open("train-labels-idx1-ubyte/train-labels.idx1-ubyte", std::ios::binary);

	if (!image.is_open() || !label.is_open()) {
		std::cerr << "Error: Could not open MNIST files. Check your paths." << std::endl;
		return 1;
	}

	int cnt=0;
	bitreadings_8(cnt, image);
	
	unsigned int imgBatchSize = 0;
	imgBatchSize = bitreadings_8(cnt, image);
	std::cout << "Batch Size: " << imgBatchSize << "\n";
	
	int imgHeight = 0;
	imgHeight = bitreadings_8(cnt, image);
	std::cout << "Height: " << imgHeight << "\n";

	int imgWidth = 0;
	imgWidth = bitreadings_8(cnt, image);
	std::cout << "Width: " << imgWidth << "\n\n";
	
	
	int labelcnt = 0;
	bitreadings_8(labelcnt, label);
	bitreadings_8(labelcnt, label);

	std::cout << "Training started..." << std::endl;

	for(int i=0; i<imgBatchSize; i++){

		// Input Init
		std::vector<double> input(784);
		for(int k=0; k<784; k++){
			unsigned char cur;
			image.read((char*)&cur, sizeof(cur));
			input[k] = (double)cur / 255.0; 
		}

		// Target Init
		std::vector<double> target(10, 0.0);
		unsigned char curlabel;
		
		label.read((char*)&curlabel, sizeof(curlabel));
		target[curlabel] = 1.0;

		nn.train(input, target);

		if (i % 1000 == 0) {
			auto pred = nn.feedForward(input);
			
			int maxIndex = 0;
			double maxVal = 0.0;
			for(int p=0; p<10; p++) {
				if(pred[p] > maxVal) {
					maxVal = pred[p];
					maxIndex = p;
				}
			}

			std::cout << "Step " << i 
					  << " | Target: " << (int)curlabel 
					  << " | Prediction: " << maxIndex 
					  << " | Conf: " << std::fixed << std::setprecision(4) << maxVal << std::endl;
		}
	}

	return 0;
}