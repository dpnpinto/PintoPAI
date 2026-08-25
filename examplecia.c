#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define Network Parameters
// Network Dimensions
#define INPUT_NODES 2
#define HIDDEN_NODES 4 
#define OUTPUT_NODES 1

// Simple XOR Training Data
double train_inputs[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
double train_outputs[4][1] = {{0}, {1}, {1}, {0}};

// Weights and Biases
// Notice that the matematical model you have one weight for each conection to the node and just  a bias for each node
// The node calculates the linear combination of all incoming data.
// It multiplies every input value by its corresponding connection weight, adds all those products together, 
// and then adds the node's bias.
// The weights are initialized randomly, and the biases are initialized to zero.
double weight1[INPUT_NODES][HIDDEN_NODES];
double weight2[HIDDEN_NODES][OUTPUT_NODES];
double bias_HN[HIDDEN_NODES];
double bias_ON[OUTPUT_NODES];

// Activation Functions
double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); } // Sigmoid Activation Function
double sigmoid_derivative(double x) { return x * (1.0 - x); } // Sigmoid Derivative

// Training Function
void train(double input[INPUT_NODES], double target[OUTPUT_NODES]) {
    double hidden[HIDDEN_NODES];
    double output_layer[OUTPUT_NODES];
    double learning_rate = 0.5;

    // 1. Feedforward
    // Calculate hidden layer values
    for (int i = 0; i < HIDDEN_NODES; i++) {
        double sum = bias_HN[i];
        for (int j = 0; j < INPUT_NODES; j++) sum += input[j] * weight1[j][i];
        hidden[i] = sigmoid(sum);
    }
    // Calculate output layer values
    for (int i = 0; i < OUTPUT_NODES; i++) {
        double sum = bias_ON[i];
        for (int j = 0; j < HIDDEN_NODES; j++) sum += hidden[j] * weight2[j][i];
        output_layer[i] = sigmoid(sum);
    }

    // 2. Backpropagation
	// Calculate output layer error and delta
    double output_error[OUTPUT_NODES];
    double output_delta[OUTPUT_NODES];
    for (int i = 0; i < OUTPUT_NODES; i++) {
        output_error[i] = target[i] - output_layer[i];
        output_delta[i] = output_error[i] * sigmoid_derivative(output_layer[i]);
    }

    // Calculate hidden layer error and delta
    double hidden_delta[HIDDEN_NODES];
    for (int i = 0; i < HIDDEN_NODES; i++) {
        double error = 0;
        for (int j = 0; j < OUTPUT_NODES; j++) error += output_delta[j] * weight2[i][j];
        hidden_delta[i] = error * sigmoid_derivative(hidden[i]);
    }

    // 3. Update Weights
    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < OUTPUT_NODES; j++) weight2[i][j] += learning_rate * output_delta[j] * hidden[i];
        bias_HN[i] += learning_rate * hidden_delta[i];
    }
    for (int i = 0; i < INPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) weight1[i][j] += learning_rate * hidden_delta[j] * input[i];
    }
    for (int i = 0; i < OUTPUT_NODES; i++) bias_ON[i] += learning_rate * output_delta[i];
}

int main() {
    // Random Initialization
	// Initialize weights and biases
    for (int i = 0; i < INPUT_NODES; i++) 
        for (int j = 0; j < HIDDEN_NODES; j++) weight1[i][j] = ((double)rand()/RAND_MAX); 
    for (int i = 0; i < HIDDEN_NODES; i++) {
        bias_HN[i] = ((double)rand()/RAND_MAX);
        weight2[i][0] = ((double)rand()/RAND_MAX);
    }
    bias_ON[0] = ((double)rand()/RAND_MAX);

    // Train for 10,000 times_train
    for (int times_train = 0; times_train < 10000; times_train++) {
        for (int i = 0; i < 4; i++) train(train_inputs[i], train_outputs[i]);
    }

    // Test
    printf("Results after training:\n");
    for (int i = 0; i < 4; i++) {
	    // Simple forward pass to print result
        double h[HIDDEN_NODES], out;
        // Hidden layer calculation
        for(int j=0; j<HIDDEN_NODES; j++) {
            double s = bias_HN[j];
            for(int k=0; k<INPUT_NODES; k++) s += train_inputs[i][k] * weight1[k][j];
            h[j] = sigmoid(s);
        }
        // Output layer calculation
        double s = bias_ON[0];
        for(int j=0; j<HIDDEN_NODES; j++) s += h[j] * weight2[j][0];
        out = sigmoid(s);
        printf("Input: %0.f %0.f | Target: %0.f | Predicted: %.4f\n", 
                train_inputs[i][0], train_inputs[i][1], train_outputs[i][0], out);
    }
    return 0;
}
