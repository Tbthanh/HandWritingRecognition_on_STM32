#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

// Function to perform ReLU activation
float relu(float x) {
    return x > 0 ? x : 0;
}

// Function to compute softmax
void softmax(float* input, size_t length) {
    float sum = 0.0;
    for (size_t i = 0; i < length; i++) {
        input[i] = exp(input[i]);
        sum += input[i];
    }
    for (size_t i = 0; i < length; i++) {
        input[i] /= sum;
    }
}

// Function to load weights
void load_weights(const char* filename, float* weights, size_t size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open %s\n", filename);
        exit(1);
    }
    for (size_t i = 0; i < size; i++) {
        fscanf(file, "%f,", &weights[i]);
    }
    fclose(file);
}

// Function to perform inference through a layer
void inference(float* input, float* weights, size_t input_size, size_t output_size, float* output) {
    for (size_t i = 0; i < output_size; i++) {
        output[i] = 0;
        for (size_t j = 0; j < input_size; j++) {
            output[i] += input[j] * weights[i * input_size + j];
        }
        // Apply ReLU for hidden layers (if needed)
        output[i] = relu(output[i]);
    }
    // Apply softmax for the output layer
    softmax(output, output_size);
}

int main() {
    // Define layer sizes
    size_t input_size = 784;        // Input layer (28x28 pixels)
    size_t hidden_1_size = 128;     // First hidden layer
    size_t hidden_2_size = 128;     // Second hidden layer
    size_t hidden_3_size = 128;     // Third hidden layer
    size_t output_size = 10;        // Output layer 

    // Allocate memory for the weights
    float* W1 = malloc(input_size * hidden_1_size * sizeof(float));
    float* W2 = malloc(hidden_1_size * hidden_2_size * sizeof(float));
    float* W3 = malloc(hidden_2_size * hidden_3_size * sizeof(float));
    float* W4 = malloc(hidden_3_size * output_size * sizeof(float));

    // Load weights from text files
    load_weights("mnist_model_W1.txt", W1, input_size * hidden_1_size);
    load_weights("mnist_model_W2.txt", W2, hidden_1_size * hidden_2_size);
    load_weights("mnist_model_W3.txt", W3, hidden_2_size * hidden_3_size);
    load_weights("mnist_model_W4.txt", W4, hidden_3_size * output_size);

    // Example input (784 pixel values)
    float input[784]; // Input (e.g., normalized image data)
    float hidden_1[128]; // First hidden layer activations
    float hidden_2[128]; // Second hidden layer activations
    float hidden_3[128]; // Third hidden layer activations
    float output[10];    // Output layer activations

    // Propagate through the first layer (input -> hidden_1)
    inference(input, W1, input_size, hidden_1_size, hidden_1);

    // Propagate through the second layer (hidden_1 -> hidden_2)
    inference(hidden_1, W2, hidden_1_size, hidden_2_size, hidden_2);

    // Propagate through the third layer (hidden_2 -> hidden_3)
    inference(hidden_2, W3, hidden_2_size, hidden_3_size, hidden_3);

    // Propagate through the output layer (hidden_3 -> output)
    inference(hidden_3, W4, hidden_3_size, output_size, output);

    // Output prediction (choose the class with highest activation)
    size_t prediction = 0;
    for (size_t i = 1; i < output_size; i++) {
        if (output[i] > output[prediction]) {
            prediction = i;
        }
    }

    // Print predicted class (digit)
    printf("Predicted Class: %zu\n", prediction);

    // Free allocated memory
    free(W1);
    free(W2);
    free(W3);
    free(W4);

    return 0;
}
