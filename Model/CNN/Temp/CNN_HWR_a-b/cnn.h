/**
  ******************************************************************************
  * @file    cnn.h
  * @author  Tran Ba Thanh
  * @author  Dinh Quoc An, Pham Anh Ho
  * @brief   This file contain all function prototype for the convolution neural 
  * 		 network (CNN) feedforward function implementations.
  *
  ******************************************************************************
  * @attention
  * To be update.
  ******************************************************************************
  * @changelog
  * 2024-12-21 - Created by Tran Ba Thanh
  * 2024-12-28 - Updated by Tran Ba Thanh: Optimized memory usage, added 
  * 														doxygen type comments
  * 
  ******************************************************************************
  @verbatim
  Usage:
  	1. To be update
  @endverbatim
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNN_H
#define CNN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "constants.h"

/* Function prototype---------------------------------------------------------*/
/* Convolution sub functions  *************************************************/
void conv2d(float *in_mat, float *out_mat, float *filter_weight, float *filter_bias, int in_dim, int in_ch, int out_ch);
void relu(float *mat, int mat_size, int num_ch);
void softmax(float *in_mat, float *out_mat, int mat_size);
void fullyconnected(float *in_mat, float *out_mat, float *weight, float *bias, int in_mat_size, int out_mat_size);
void maxpooling2x2(float *in_mat, float *out_mat, uint8_t in_mat_size, uint8_t num_ch);
int afterKernel(int n);
void givePredict(float *mat, uint8_t *predicted_num, float *predicted_num_confidence);

/* Convolution BIGGGGboi functions  *******************************************/
void feedforward(float *in_mat, uint8_t *predicted_num, float *predicted_num_confidence);
void DBfeedforward(float *in_mat, uint8_t *predicted_num, float *predicted_num_confidence);


/* Ultility functions  *******************************************/
void printMatrix(float *mat, int num_ch, int mat_size, int external_arg);
void printFilterBias(float *bias_mat, int num_ch);
void printFilterWeight(float *mat, int num_ch_out, int num_ch_in);
void printMat1D(float *mat, int num_ch);
void printPredict(float *mat);

/* Debug functions  *******************************************/
void printMatrixToFile(FILE *file, float *mat, int num_ch, int mat_size, int external_arg);
void printFilterBiasToFile(FILE *file, float *bias_mat, int num_ch);
void printMat1DToFile(FILE *file, float *mat, int num_ch);
void printFilterWeightToFile(FILE *file, float *mat, int num_ch_out, int num_ch_in);


#endif // CNN_H