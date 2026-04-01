#include <stdio.h>

int main() {
    // 1. Data: We want the model to learn that y = 2x
    float x[] = {1, 2, 3, 4};
    float y[] = {2, 4, 6, 8};
    int n = 4;

    // 2. Hyperparameters (The values YOU set)
    float weight = 0.0;       // Initial guess
    float learning_rate = 0.01; 
    int times_train = 500;         // How many times to train

    printf("Starting training with weight: %f\n", weight);

    // 3. The Training Loop
    for (int i = 0; i < times_train; i++) {
        float total_error = 0;

        for (int j = 0; j < n; j++) {
            // Forward Pass: Prediction = x * weight
            float prediction = x[j] * weight;

            // Calculate Error (Actual - Prediction)
            float error = y[j] - prediction;

            // Update Rule: Weight = Weight + (Input * Error * Learning Rate)
            // This is a simplified version of Gradient Descent
            weight += x[j] * error * learning_rate;
            
            total_error += error * error; 
        }

        if (i % 100 == 0) {
            printf("times_train %d: Weight = %.4f, Error = %.4f\n", i, weight, total_error);
        }
    }

    printf("\nFinished! Final trained weight: %.2f\n", weight);
    printf("Prediction for x=10: %.2f (Expected 20.00)\n", 10 * weight);

    return 0;
}
