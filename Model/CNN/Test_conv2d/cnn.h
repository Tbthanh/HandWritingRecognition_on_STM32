#ifndef CNN_H
#define CNN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "constants.h"
#include "conv1_params.h"
#include "conv2_params.h"

// ----------------Function prototype----------------
// Convolution functions
// void read_input_data(const char *filename, float input[INPUT_SIZE][INPUT_SIZE]);
// float apply_filter(float *input, Filter *filter, int x, int y) ;
// void conv2d_1ch(float *input_mat, float *output_mat, Filter *filter, int input_mat_size);
void conv2d(float *in_mat, float *out_mat, float *filter_weight, float *filter_bias, int in_dim, int in_ch, int out_ch);
void relu(float *mat, int mat_size, int num_ch);
void softmax(float *input_mat, float *output_mat, int mat_size);
void fullyconnected(float *in_mat, float *out_mat, float *weight, float *bias, int in_mat_size, int out_mat_size);
void maxpooling2x2(float *in_mat, float *out_mat, uint8_t in_mat_size, uint8_t num_ch);
int afterKernel(int n);

// Ultility functions
void printMatrix(float *mat, int num_ch, int mat_size, int external_arg);
void printFilterBias(float *bias_mat, int num_ch);
void printFilterWeight(float *mat, int num_ch_out, int num_ch_in);
void printMat1D(float *mat, int num_ch);
void printPredict(float *mat);

#endif // CNN_H