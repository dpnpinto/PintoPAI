// KISS form AI by Duarte Pedro Pinto
// https://dpnpinto.github.io
// https://www.youtube.com/@dpinto.engenharia
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // need math for exponecial exp

// Define Neural Network dimension
#define INPUT_NODES 2
#define HIDDEN_NODES 4 
#define OUTPUT_NODES 1

// Simple XOR Training Data
// The complete dataset for XOR consists of just 4 samples of 2 inputs and 1 output
#define TRAIN_SAMPLES 4
double train_inputs[TRAIN_SAMPLES][INPUT_NODES] = {{0,0}, {0,1}, {1,0}, {1,1}};
double train_outputs[TRAIN_SAMPLES][OUTPUT_NODES] = {{0}, {1}, {1}, {0}};

// The matrix with the data that methers that will be trained
double weight_in_hid[INPUT_NODES][HIDDEN_NODES];
double weight_hid_out[HIDDEN_NODES][OUTPUT_NODES];
double bias_hid_node[HIDDEN_NODES];
double bias_out_node[OUTPUT_NODES];

// The activation function and its corresponding derivative
double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
double sigmoid_derivative(double x) { return x * (1.0 - x); }

// The trainig function
void train(double input[INPUT_NODES], double target[OUTPUT_NODES]) {
    double hidden[HIDDEN_NODES]; // local values for hidden nodes
    double output_layer[OUTPUT_NODES]; // local values for output
    double learning_rate = 0.5; // the small step

    // 1. Feedforward
    
    // Feed the Hidden Nodes values
    for (int i = 0; i < HIDDEN_NODES; i++) {
        double sum = bias_hid_node[i]; // The local variable sum is equal to the bias of the corresponding node
        for (int j = 0; j < INPUT_NODES; j++) sum += input[j] * weight_in_hid[j][i]; // make the calculation of (x*weight+bias) 
        hidden[i] = sigmoid(sum); // all outputs of hidden layer have the values of the calculated inputs from previous layer 
    }
    // Feed the Output Nodes values
    for (int i = 0; i < OUTPUT_NODES; i++) {
        double sum = bias_out_node[i]; // The local variable sum is equal to the bias of the corresponding node
        for (int j = 0; j < HIDDEN_NODES; j++) sum += hidden[j] * weight_hid_out[j][i]; // make the calculation of (x*weight+bias) 
        output_layer[i] = sigmoid(sum); // all outputs of output layer have the values of the calculated inputs of previous layer 
    }

    // 2. Backpropagation
    double output_error[OUTPUT_NODES];  // store  the output errors
    double output_delta[OUTPUT_NODES];   //  store the output delta
    for (int i = 0; i < OUTPUT_NODES; i++) {
        output_error[i] = target[i] - output_layer[i];  //  get the derivative of the squared error loss function for the output
        // It is usefull to get target subtracted from output to obtain the negative value for the gradient and save a subtraction calculation
        output_delta[i] = output_error[i] * sigmoid_derivative(output_layer[i]);
    }

    double hidden_delta[HIDDEN_NODES];
    for (int i = 0; i < HIDDEN_NODES; i++) {
        double error = 0;
        for (int j = 0; j < OUTPUT_NODES; j++) error += output_delta[j] * weight_hid_out[i][j];
        hidden_delta[i] = error * sigmoid_derivative(hidden[i]);
    }

    // 3. Update Weights
    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < OUTPUT_NODES; j++) weight_hid_out[i][j] += learning_rate * output_delta[j] * hidden[i];
        bias_hid_node[i] += learning_rate * hidden_delta[i];
    }
    for (int i = 0; i < INPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) weight_in_hid[i][j] += learning_rate * hidden_delta[j] * input[i];
    }
    for (int i = 0; i < OUTPUT_NODES; i++) bias_out_node[i] += learning_rate * output_delta[i];
}

int main() {
    // Initialization of bias and weights, bias with 0 weights with values from -1 to 1
    for (int i = 0; i < INPUT_NODES; i++) 
        for (int j = 0; j < HIDDEN_NODES; j++) weight_in_hid[i][j] = ((double)rand()/RAND_MAX) * 2.0 - 1.0;//Random numbers from -1 to 1;
    for (int i = 0; i < HIDDEN_NODES; i++) {
        bias_hid_node[i] = 0; //Iniciate bias with zero is the best practive
        weight_hid_out[i][0] = ((double)rand()/RAND_MAX) * 2.0 - 1.0; //Random numbers from -1 to 1
    }
    bias_out_node[0] = 0; //Iniciate bias with zero is the best practive

    // Train for 10,000 times_train
    for (int times_train = 0; times_train < 1000000; times_train++) {
        for (int i = 0; i < 4; i++) train(train_inputs[i], train_outputs[i]);
    }

    // Test
    printf("Results after training:\n");
    for (int i = 0; i < 4; i++) {
        // Simple forward pass to print result
        double h[HIDDEN_NODES], out;
        for(int j=0; j<HIDDEN_NODES; j++) {
            double s = bias_hid_node[j];
            for(int k=0; k<INPUT_NODES; k++) s += train_inputs[i][k] * weight_in_hid[k][j];
            h[j] = sigmoid(s);
        }
        double s = bias_out_node[0];
        for(int j=0; j<HIDDEN_NODES; j++) s += h[j] * weight_hid_out[j][0];
        out = sigmoid(s);
        printf("Input: %0.f %0.f | Target: %0.f | Predicted: %.4f\n", 
                train_inputs[i][0], train_inputs[i][1], train_outputs[i][0], out);
    }
    return 0;
}
