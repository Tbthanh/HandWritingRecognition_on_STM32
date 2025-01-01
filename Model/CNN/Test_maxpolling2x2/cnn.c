/*
	File: cnn.c
	Author: Tran Ba Thanh
	Created: 21/12/2024
	Last update: 21/12/2024
	Purpose: to impliment trained weight from python in C

	Todo:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "cnn.h"
#include "constants.h"
#include "conv1_params.h"
#include "conv2_params.h"
// #include "conv3_params.h"
// #include "conv4_params.h"
// #include "lin1_params.h"
// #include "lin2_params.h"

#define DEBUG 2  // Corresponds to layer1_indep

// Label: 1
const float input_mat_temp[INPUT_SIZE * INPUT_SIZE] = {
	1.0, 0.0, 0.5, 0.0, 0.2, 0.1, 
	1.0, 0.4, 0.5, 0.3, 0.2, 0.0,
	1.0, 0.0, 0.5, 0.0, 0.2, 0.1,
	1.0, 0.0, 0.5, 0.3, 0.2, 0.0,
	1.0, 0.4, 0.5, 0.0, 0.2, 0.1,
	1.0, 0.0, 0.5, 0.3, 0.2, 0.0,
};

// // Label: 3
// const float input_mat_temp[INPUT_SIZE * INPUT_SIZE] = {
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.2, 0.4, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.5, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.6, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.7, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 1.0, 1.0, 0.9, 0.5, 0.5, 0.5, 0.5, 0.7, 1.0, 1.0, 1.0, 1.0, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 0.0, 0.1, 0.9, 1.0, 1.0, 0.7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3, 1.0, 1.0, 1.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3, 0.7, 1.0, 1.0, 1.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.8, 1.0, 1.0, 1.0, 1.0, 0.8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.5, 0.8, 0.8, 0.8, 1.0, 1.0, 1.0, 1.0, 0.9, 0.4, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.5, 0.2, 0.2, 0.2, 0.2, 0.2, 0.6, 1.0, 1.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 1.0, 1.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3, 1.0, 1.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.9, 1.0, 1.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.7, 1.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.1, 0.4, 0.9, 1.0, 1.0, 1.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.8, 1.0, 1.0, 0.6, 0.5, 0.5, 0.5, 0.5, 0.8, 1.0, 1.0, 1.0, 0.7, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.6, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.8, 0.6, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.9, 1.0, 0.7, 0.4, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// 	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
// };

int main()
{
// variable and stuff
	
	// layer 1 stuff - l1~~~
	const int l1_ch = NUM_05CH;
	const int l1_dim = 4;
	float l1_mat[l1_ch * l1_dim * l1_dim];	// mat to store calculated value
	int l1_mat_bytesize = sizeof(float)*l1_ch*l1_dim*l1_dim;
	memset(l1_mat, 0, l1_mat_bytesize);

	const int l1_pool_mat_dim = 2; 		// l2_pool_mat_dim = l2_dim / 2
	float l1_pool_mat[l1_ch * l1_pool_mat_dim * l1_pool_mat_dim];			// mat to store maxpooling calculated value
	int l1_pool_mat_bs = sizeof(float)*l1_ch*l1_pool_mat_dim*l1_pool_mat_dim;
	memset(l1_pool_mat, 0, l1_pool_mat_bs);


// Calculation
	#ifdef DEBUG
	printf("\n======================================================================= INPUT\n");
	printMatrix((float *)input_mat_temp, 1, INPUT_SIZE, 0);
	#endif

	// layer 1
	#if DEBUG == 2
	printf("\n======================================================================= Layer 1, filter weight\n");
	printFilterWeight((float *)conv1_filter_weight, 5, 1);
	printf("\n======================================================================= Layer 1, filter bias\n");
	printFilterBias((float *)conv1_filter_bias, 5);
	#endif
	
	conv2d((float *)input_mat_temp, (float *)l1_mat, (float *)conv1_filter_weight, (float *)conv1_filter_bias, INPUT_SIZE, NUM_01CH, NUM_05CH);
	
	#if DEBUG == 2
	printf("\n======================================================================= Layer 1, l1_mat after conv2d\n");
	printMatrix((float *)l1_mat, CONV1_K_NUM, AFTER_CONV1_DIM, printChannelIdx);
	#endif // DEBUG == layer1_indept

	relu((float *)l1_mat, AFTER_CONV1_DIM, NUM_05CH);

	#if DEBUG == 2
	printf("\n======================================================================= Layer 1, l1_mat after relu\n");
	printMatrix((float *)l1_mat, CONV1_K_NUM, AFTER_CONV1_DIM, printChannelIdx);
	#endif // DEBUG == layer1_indept

	maxpooling2x2((float *)l1_mat, (float *)l1_pool_mat, AFTER_CONV1_DIM, CONV1_K_NUM);

	#if DEBUG == 2
	printf("\n======================================================================= Layer 1, l1_pool_mat\n");
	printMatrix((float *)l1_pool_mat, CONV1_K_NUM, 2, printChannelIdx);
	#endif // DEBUG == layer1_indept

	// layer 2
	// conv2d((float *)l1_mat, (float *)l2_mat, (float *)conv2_filter_weight, (float *)conv2_filter_bias, AFTER_CONV1_DIM, NUM_05CH, NUM_10CH);
	// #if DEBUG == 2
	// printf("\n======================================================================= Layer 2, l2_mat after conv2d\n");
	// printMatrix((float *)l2_mat, CONV1_K_NUM, AFTER_CONV2_DIM, printChannelIdx);
	// #endif // DEBUG == layer1_indept

	// relu((float *)l2_mat, AFTER_CONV2_DIM, CONV2_K_NUM);
	// #if DEBUG == 2
	// printf("\n======================================================================= Layer 1, l1_mat after relu\n");
	// printMatrix((float *)l2_mat, CONV2_K_NUM, AFTER_CONV2_DIM, printChannelIdx);
	// #endif // DEBUG == layer1_indept
	// maxpooling2x2((float *)l2_mat, (float *)l2_pool_mat, AFTER_CONV2_DIM, CONV2_K_NUM);

	// // layer 3
	// conv2d((float *)l2_pool_mat, (float *)l3_mat, (float *)conv3_filter_weight, (float *)conv3_filter_bias, AFTER_MAXP1_DIM, NUM_10CH, CONV3_K_NUM);
	// relu((float *)l3_mat, AFTER_CONV3_DIM, CONV3_K_NUM);	

	// // layer 4
	// conv2d((float *)l3_mat, (float *)l4_mat, (float *)conv4_filter_weight, (float *)conv4_filter_bias, AFTER_CONV3_DIM, NUM_12CH, NUM_15CH);
	// relu((float *)l4_mat, AFTER_CONV4_DIM, NUM_15CH);
	// maxpooling2x2((float *)l4_mat, (float *)l4_pool_mat, AFTER_CONV4_DIM, CONV4_K_NUM);

	// fullyconnected((float *)l4_pool_mat, (float *)fc1_mat, (float *)lin1_weight, (float *)lin1_bias, FC01NODENUM, FC02NODENUM);	

	// fullyconnected((float *)fc1_mat, (float *)fc2_mat, (float *)lin2_weight, (float *)lin2_bias, FC02NODENUM, OUTPUT_SIZE);	

	// softmax((float *)fc2_mat, (float *)softmax_result_mat, OUTPUT_SIZE);

	// #if (DEBUG == 1)
	// printf("\n======================================================================= CONV1 relu result\n");
	// printMatrix((float *)l1_mat, CONV1_K_NUM, AFTER_CONV1_DIM, printChannelIdx);
	// printf("\n======================================================================= CONV2 relu result\n");
	// printMatrix((float *)l2_mat, CONV2_K_NUM, AFTER_CONV2_DIM, printChannelIdx);
	// printf("\n======================================================================= CONV2 maxpooling result\n");
	// printMatrix((float *)l2_pool_mat, CONV2_K_NUM, AFTER_MAXP1_DIM, printChannelIdx);
	// printf("\n======================================================================= CONV3 relu result\n");
	// printMatrix((float *)l3_mat, CONV3_K_NUM, AFTER_CONV3_DIM, printChannelIdx);
	// printf("\n======================================================================= CONV4 relu result\n");
	// printMatrix((float *)l4_mat, CONV4_K_NUM, AFTER_CONV4_DIM, printChannelIdx);
	// printf("\n======================================================================= CONV4 maxpooling result\n");
	// printMatrix((float *)l4_pool_mat, CONV4_K_NUM, AFTER_MAXP2_DIM, printChannelIdx);
	// printf("\n======================================================================= FC1 result\n");
	// printMat1D((float *)fc1_mat, FC01NODENUM);
	// printf("\n======================================================================= FC2 relu result\n");
	// printMat1D((float *)fc2_mat, FC02NODENUM);
	// #endif

	// printf("\n======================================================================= softmax result\n");
	// printMat1D((float *)softmax_result_mat, NUM_10CH);
	// printf("=======================================================================\n");
	// printPredict((float *)softmax_result_mat);

	return 0;
}


/*
	i, j
		m, n
			p, q
	
*/
void conv2d(float *in_mat, float *out_mat, float *filter_weight, float *filter_bias, int in_dim, int in_ch, int out_ch)
{
	int out_dim = afterKernel(in_dim);	// calculate out_mat dimentions

	// Initialize output matrix to zero
    for (int i = 0; i < out_ch * out_dim * out_dim; i++)
    {
        out_mat[i] = 0.0f;
    }

	// Perform convolution (damme bull$h!#)
	for (int i_out_ch = 0; i_out_ch < out_ch; i_out_ch++)	// iterate though output channels
	{
		// START: iterate though out_mat to store value
		for (int m = 0; m < out_dim; m++)	// m for row
		{
			for (int n = 0; n < out_dim; n++)	// n for col
			{
				float sum = 0.0f;
				for (int i_in_ch = 0; i_in_ch < in_ch; i_in_ch++)	// iterate though input channels
				{
					// START: iterate though Kernel
					for (int p = 0; p < FILTER_SIZE; p++)			// for accessing row of filter
					{
						for (int q = 0; q < FILTER_SIZE; q++) 		// for accessing col of filter
						{
							int in_idx = (i_in_ch * in_dim * in_dim) + ((m + p) * in_dim) + (n + q);
							int filter_idx = (i_out_ch * in_ch * FILTER_SIZE * FILTER_SIZE) + 
                                             (i_in_ch * FILTER_SIZE * FILTER_SIZE) + 
                                             (p * FILTER_SIZE) + q;
							// sum += in_mat[i_ch_out][m+p][n+q] * filter_weight[i_out_ch][i_in_ch][p][q]
							sum += in_mat[in_idx] * filter_weight[filter_idx];
						}
					}
					// END: iterate though Kernel
				}
				int out_idx = (i_out_ch * out_dim * out_dim) + (m * out_dim) + n;
				out_mat[out_idx] = sum + filter_bias[i_out_ch];
			}
		}
		// END: iterate though out_mat to store value
	}
}

/*	Function: relu
*/
void relu(float *mat, int mat_size, int num_ch) 
{
	for (int i_ch = 0; i_ch < num_ch; i_ch++)
	{
		for (int i = 0; i < mat_size; i++) 
		{
			for (int j = 0; j < mat_size; j++) 
			{
				float *ptr = (mat + (i_ch * mat_size * mat_size) + (i * mat_size) + j);
				if (*ptr < 0) 
				{
					*ptr = 0;
				}
			}
		}
	}
}


/*	Function: softmax - 
	Input:
	Output:
*/
void softmax(float *input_mat, float *out_mat, int mat_size)
{
	float total_exp = 0.0;
	// calculate sum of e**input_mat[i]
	for (int i = 0; i < mat_size; i++)
	{
		total_exp += exp(input_mat[i]);
	}
	// calculate softmax result
	for (int i = 0; i < mat_size; i++)
	{
		out_mat[i] = exp(input_mat[i]) / total_exp;
	}
}

/*	Function: fullyconnected
	Input:
	Output:
*/
void fullyconnected(float *in_mat, float *out_mat, float *weight, float *bias, int in_mat_size, int out_mat_size)
{
	// need to impliment matmul, but too reiji so ...
	// loop though the output mat to save cal result
	for (int i_out = 0; i_out < out_mat_size; i_out++)			// i_out for out_mat index
	{
		out_mat[i_out] = 0;
		// loop though the input mat to cal
		for (int i_in = 0; i_in < in_mat_size; i_in ++)		// j for input_mat index
		{
			out_mat[i_out] += in_mat[i_in] * weight[i_out * in_mat_size + i_in];
		}
		out_mat[i_out] += bias[i_out]; 						// adding bias
	}
}

/*
*/
void maxpooling2x2(float *in_mat, float *out_mat, uint8_t in_mat_size, uint8_t num_ch)
{
	 // Calculate the size of the output matrix
	uint8_t out_mat_size = (int)(in_mat_size / 2);

	for (int i_ch = 0; i_ch < num_ch; i_ch++)
	{
		// Iterate through the output matrix
		for (int i = 0; i < out_mat_size; i++) 
		{
			for (int j = 0; j < out_mat_size; j++)
			{
				float max_value = -__FLT_MAX__; // Initialize to the smallest float value
				
				// Iterate through the pooling window
				for (int m = 0; m < POOLING_SIZE; m++) 
				{
					for (int n = 0; n < POOLING_SIZE; n++) 
					{
						// Calculate the index of the current input element
						int row_idx = i * POOLING_SIZE + m;
						int col_idx = j * POOLING_SIZE + n;
						int input_idx = row_idx * in_mat_size + col_idx;

						// Update the maximum value
						if (in_mat[input_idx] > max_value) {
							max_value = in_mat[input_idx];
							// max_value = input_mat[i_ch][row_idx][col_idx];
						}
					}
				}
				// Assign the maximum value to the output matrix
				// output_mat[i_ch][i][j] = max_value;
				int output_idx = i_ch * out_mat_size * out_mat_size + i * out_mat_size + j;
				out_mat[output_idx] = max_value;
			}
		}
	}
}


/*
*/
void printMatrix(float *mat, int num_ch, int mat_size, int external_arg)
{
	for (int i_ch = 0; i_ch < num_ch; i_ch++)
	{
		// External argument for printing extra info - mainly for debuging purpose
		if (external_arg == printKernelIdx)
		{
			printf("Kernel %d\n", i_ch);
		}
		else if (external_arg == printChannelIdx)
		{
			printf("Channel %d\n", i_ch);
		}
		else if (external_arg == printMatIdx)
		{
			printf("Matrix %d\n", i_ch);
		}

		// Printing loop
		for (int i = 0; i < mat_size; i++)
		{
			for (int j = 0; j < mat_size; j++)
			{
				printf("%.3f  ", *(mat + (i_ch * mat_size * mat_size) + (i * mat_size) + j));
			}
			printf("\n");
		}
		printf("\n");
	}
}

/*
*/
void printFilterBias(float *bias_mat, int num_ch)
{
	for (int i_ch = 0; i_ch < num_ch; i_ch++)
	{
		printf("%f ", bias_mat[i_ch]);
	}
	printf("\n\n");
}

void printMat1D(float *mat, int num_ch)
{
	printFilterBias((float *)mat, num_ch);
}

/*
*/
void printFilterWeight(float *mat, int num_ch_out, int num_ch_in)
{
	int mat_size = FILTER_SIZE;
	for (int i_ch_out = 0; i_ch_out < num_ch_out; i_ch_out++)
	{
		printf("Kernel %d\n", i_ch_out);
		printMatrix((float *)(mat + i_ch_out * num_ch_in * mat_size * mat_size), num_ch_in, mat_size, printChannelIdx);
	}
}

void printPredict(float *mat)
{
	float max_predict = mat[0];
	int max_idx = 0;
	for (int i = 1; i < OUTPUT_SIZE; i++)
	{
		if (max_predict < mat[i])
		{
			max_predict = mat[i];
			max_idx = i;
		}
	}
	printf("Predict %d with chance of %f\n", max_idx, max_predict);
}

// #define AFTER_KERNEL(N) (N - FILTER_SIZE + 1)	// P = 0; S = 1
int afterKernel(int n)
{
	return (n - FILTER_SIZE + 1);
}

// void matmul_a_b()
// void matmul_a_bt()
// void matmul_at_b()
/*
	Reference:
		https://github.com/usamahz/cnn.git
		https://youtu.be/jDe5BAsT2-Y?si=i9AY3u8cukuy75CI
		
*/