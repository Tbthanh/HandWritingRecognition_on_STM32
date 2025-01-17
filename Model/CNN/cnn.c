/**
  ******************************************************************************
  * @file    cnn.c
  * @author  Tran Ba Thanh
  * @author  Dinh Quoc An, Pham Anh Ho
  * @brief   Convolution neural network (CNN) feedforward function implementations.
  *
  ******************************************************************************
  * @attention
  * Ensure that the input data and weights are pre-initialized correctly before 
  * calling these functions. To be update.
  ******************************************************************************
  * @changelog
  * 2024-12-21 - Created by Tran Ba Thanh
  * 2024-12-22 - Added conv<x>_params.h by T.B.Thanh: following trainned weight by D.Q.An
  * 2024-12-28 - Updated by Tran Ba Thanh: Optimized memory usage, added 
  * 			 doxygen type comments, but too layzeee
  * 
  ******************************************************************************
  @verbatim
  Usage:
  	1. To be update
  @endverbatim
  ******************************************************************************
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
#include "conv3_params.h"
#include "conv4_params.h"
#include "lin1_params.h"
#include "lin2_params.h"

/**
  ******************************************************************************
  * @brief   Performs a 2D convolution operation.
  * @param   in_mat         Pointer to the input matrix/array (1D array of floats).
  * @param   out_mat        Pointer to the output matrix/array (1D array of floats).
  * @param   filter_weight  Pointer to the filter weights, stored as a 1D array 
  *                         of size [input channels * output channels * filter size * filter size].
  * @param   filter_bias    Pointer to the filter biases, stored as a 1D array of size [output channels].
  * @param   in_dim         Dimension (height/width) of the input matrix.
  * @param   in_ch          Number of input channels.
  * @param   out_ch         Number of output channels (or filters).
  * @retval  None
  * @details This function performs the following operations for each output element:
  *          1. Convolves the input matrix with the specified filter weights for each filter.
  *          2. Adds the corresponding bias value to the result.
  *          3. Stores the result in the output matrix.
  *
  *          The output matrix should be pre-allocated by the caller, with the appropriate
  *          dimensions determined by the input size, filter size, and stride settings which
  * 		 is defined and can be redefined in "constants.h".
  ******************************************************************************
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


/*	
	Function: relu
	Input:
	Output:
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


/**
  ******************************************************************************
  * @brief   Implements the softmax function in a neural network.
  * @param   in_mat 		Pointer to the input matrix (1D array of floats).
  * @param   out_mat 		Pointer to the output matrix (1D array of floats).
  * @param   mat_size 		Size of the in/output matrix (number of elements).
  * @retval  None
  * @details This function performs the following operations for each element 
  *          in the output matrix:
  *          1. Computes the total of e^{input matrix value} of the input 
  * 			matrix.
  *          2. For each output matrix element coresponding to input matrix 
  * 			element, calculate the devided value of e^{input} with total 
  * 			in the previous step.
  *          The result is stored in the output matrix.
  ******************************************************************************
  */
void softmax(float *in_mat, float *out_mat, int mat_size)
{
	float total_exp = 0.0;
	// calculate sum of e**input_mat[i]
	for (int i = 0; i < mat_size; i++)
	{
		total_exp += exp(in_mat[i]);
	}
	// calculate softmax result
	for (int i = 0; i < mat_size; i++)
	{
		out_mat[i] = exp(in_mat[i]) / total_exp;
	}
}


/**
  ******************************************************************************
  * @brief   Implements the fully connected layer in a neural network.
  * @param   in_mat			Pointer to the input matrix (1D array of floats).
  * @param   out_mat		Pointer to the output matrix (1D array of floats).
  * @param   weight			Pointer to the weight matrix (1D array of floats).
  * @param   bias			Pointer to the bias array (1D array of floats).
  * @param   in_mat_size	Size of the input matrix (number of elements).
  * @param   out_mat_size	Size of the output matrix (number of elements).
  * @retval  None
  * @details This function performs the following operations for each element 
  *          in the output matrix:
  *          1. Computes the dot product of the input matrix and corresponding
  *             row in the weight matrix.
  *          2. Adds the bias for the corresponding output element.
  *          The result is stored in the output matrix.
  ******************************************************************************
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
	Function:
	Input:
	Output:
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
						// int input_idx = row_idx * in_mat_size + col_idx;
						int input_idx = i_ch * in_mat_size * in_mat_size + row_idx * in_mat_size + col_idx;;

						// Update the maximum value
						if (in_mat[input_idx] > max_value) {
							max_value = in_mat[input_idx];
						}
					}
				}
				// Assign the maximum value to the output matrix
				int output_idx = i_ch * out_mat_size * out_mat_size + i * out_mat_size + j;
				out_mat[output_idx] = max_value;
			}
		}
	}
}


// #define AFTER_KERNEL(N) (N - FILTER_SIZE + 1)	// P = 0; S = 1
int afterKernel(int n)
{
	return (n - FILTER_SIZE + 1);
}

void givePredict(float *mat, uint8_t *predicted_num, float *predicted_num_confidence)
{
	float max_confidence = mat[0];
	int max_idx = 0;
	for (int i = 1; i < OUTPUT_SIZE; i++)
	{
		if (max_confidence < mat[i])
		{
			max_confidence = mat[i];
			max_idx = i;
		}
	}
	*predicted_num = max_idx;
	*predicted_num_confidence = max_confidence;
}


/********************* Convolution BIGGGGboi functions ********************/
void feedforward(float *in_mat, uint8_t *predicted_num, float *predicted_num_confidence)
{
	/*
	Matrix/Array to store calculated value:
		One array of 9140 float value = 36560 bytes = about 37Kbytes
		STM32F401CDU6 DocID025644 Rev 3: Memory maping page 51/135
					96Kb of memory heckyeah
	*/
	float wtf_mat[WTF_NUM];
	memset(wtf_mat, 0, SIZEOF_WTF);

	// void conv2d(float *in_mat, float *out_mat, float *filter_weight, float *filter_bias, int in_dim, int in_ch, int out_ch)
	// void relu(float *mat, int mat_size, int num_ch) 
	// void maxpooling2x2(float *in_mat, float *out_mat, uint8_t in_mat_size, uint8_t num_ch)


	// layer1 ================================================
	conv2d(in_mat, wtf_mat, (float *)conv1_filter_weight, (float *)conv1_filter_bias, INPUT_SIZE, NUM_01CH, CONV1_K_NUM);
	
	relu(wtf_mat, AFTER_CONV1_DIM, CONV1_K_NUM);

	// layer 2 ================================================
	conv2d(wtf_mat, &wtf_mat[ARRAY_SEPARATOR01], (float *)conv2_filter_weight, (float *)conv2_filter_bias, AFTER_CONV1_DIM, CONV1_K_NUM, CONV2_K_NUM);
	
	relu(&wtf_mat[ARRAY_SEPARATOR01], AFTER_CONV2_DIM, CONV2_K_NUM);
	
	maxpooling2x2(&wtf_mat[ARRAY_SEPARATOR01], wtf_mat, AFTER_CONV2_DIM, CONV2_K_NUM);

	// layer 3 ================================================
	conv2d(wtf_mat, &wtf_mat[ARRAY_SEPARATOR02], (float *)conv3_filter_weight, (float *)conv3_filter_bias, AFTER_MAXP1_DIM, NUM_10CH, CONV3_K_NUM);
	relu(&wtf_mat[ARRAY_SEPARATOR02], AFTER_CONV3_DIM, CONV3_K_NUM);	

	// layer 4 ================================================
	conv2d(&wtf_mat[ARRAY_SEPARATOR02], &wtf_mat[ARRAY_SEPARATOR03], (float *)conv4_filter_weight, (float *)conv4_filter_bias, AFTER_CONV3_DIM, NUM_12CH, NUM_15CH);
	relu(&wtf_mat[ARRAY_SEPARATOR03], AFTER_CONV4_DIM, NUM_15CH);
	maxpooling2x2(&wtf_mat[ARRAY_SEPARATOR03], &wtf_mat[ARRAY_SEPARATOR04], AFTER_CONV4_DIM, CONV4_K_NUM);
	// wtf_mat[ARRAY_SEPARATOR04] is already pentan -> no need flatten

	// Fullyconnected 1 =======================================
	fullyconnected(&wtf_mat[ARRAY_SEPARATOR04], &wtf_mat[ARRAY_SEPARATOR05], (float *)lin1_weight, (float *)lin1_bias, FC01NODENUM, FC02NODENUM);	

	// Fullyconnected 2 =======================================
	fullyconnected(&wtf_mat[ARRAY_SEPARATOR05], &wtf_mat[ARRAY_SEPARATOR06], (float *)lin2_weight, (float *)lin2_bias, FC02NODENUM, OUTPUT_SIZE);	

	// Soft_expensive ================================================
	softmax(&wtf_mat[ARRAY_SEPARATOR06], &wtf_mat[ARRAY_SEPARATOR07], OUTPUT_SIZE);

	// Forgot the give predict function
	givePredict(&wtf_mat[ARRAY_SEPARATOR07], predicted_num, predicted_num_confidence);
}


/*************************** Ultility functions ***************************/
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
	float max_predict = 0;
	uint8_t max_idx = 0;
	givePredict(mat, &max_idx, &max_predict);
	printf("Predict %d with chance of %f\n", max_idx, max_predict);
}


// void matmul_a_b()
// void matmul_a_bt()
// void matmul_at_b()
/*
	Reference:
		https://github.com/usamahz/cnn.git
		https://youtu.be/jDe5BAsT2-Y?si=i9AY3u8cukuy75CI
		
*/