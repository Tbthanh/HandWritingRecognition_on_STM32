/**
  ******************************************************************************
  * @file    constants.h
  * @author  Tran Ba Thanh
  * @author  Dinh Quoc An, Pham Anh Ho
  * @brief   This file contain all the constants for the convolution neural 
  * 		 network (CNN) feedforward function implementations.
  *
  ******************************************************************************
  * @attention
  * To be update.
  ******************************************************************************
  * @changelog
  * 2024-12-21 - Created by Tran Ba Thanh
  * 2024-12-28 - Updated by Tran Ba Thanh: Optimized memory usage, added 
  * 														oxygen type comments
  * 
  ******************************************************************************
  @verbatim
  Usage:
  	1. To be update
  @endverbatim
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define INPUT_SIZE 		28
#define FILTER_SIZE 	3
#define OUTPUT_SIZE 	2		// Number of output class, in this case 2 (a and b)
#define AFTER_CONV1_DIM	26
#define AFTER_CONV2_DIM	24
#define AFTER_MAXP1_DIM	12
#define AFTER_CONV3_DIM	10
#define AFTER_CONV4_DIM	8
#define AFTER_MAXP2_DIM	4

#define POOLING_SIZE	2

// some tinkering
#define NUM_01CH 		1
#define NUM_02CH    2
#define NUM_05CH 		5
#define NUM_10CH 		10
#define NUM_12CH		12
#define NUM_15CH 		15
#define NUM_20CH 		20

// CNN kernel numbrer
#define CONV1_K_NUM		NUM_05CH
#define CONV2_K_NUM		NUM_10CH
#define CONV3_K_NUM		NUM_12CH
#define CONV4_K_NUM		NUM_15CH

// Classifier node number
#define FC01NODENUM		240
#define FC02NODENUM		40

#define WTF_NUM         AFTER_CONV1_DIM * AFTER_CONV1_DIM * CONV1_K_NUM + AFTER_CONV2_DIM * AFTER_CONV2_DIM * CONV2_K_NUM
#define SIZEOF_WTF			WTF_NUM * 4
#define ARRAY_SEPARATOR01	AFTER_CONV1_DIM * AFTER_CONV1_DIM * CONV1_K_NUM							// 3380: layer1-result | layer2-result
#define ARRAY_SEPARATOR02	AFTER_MAXP1_DIM * AFTER_MAXP1_DIM * CONV2_K_NUM							// 1440: layer2-mxp| trash | layer2-result
#define ARRAY_SEPARATOR03	AFTER_CONV3_DIM * AFTER_CONV3_DIM * CONV3_K_NUM + ARRAY_SEPARATOR02		// 1200 + 1440 = 2640
#define ARRAY_SEPARATOR04	AFTER_CONV4_DIM * AFTER_CONV4_DIM * CONV4_K_NUM + ARRAY_SEPARATOR03		//  960 + 2640 = 3600
#define ARRAY_SEPARATOR05	FC01NODENUM + ARRAY_SEPARATOR04		//  240 + 3600 = 3840 - storing maxpool-layer4 also the fist input of fc1
#define ARRAY_SEPARATOR06	FC02NODENUM + ARRAY_SEPARATOR05		//   40 + 3840 = 3880
#define ARRAY_SEPARATOR07	OUTPUT_SIZE + ARRAY_SEPARATOR06		//   10 + 3880 = 3890 // 2 + 3880
#define ARRAY_SEPARATOR08	OUTPUT_SIZE + ARRAY_SEPARATOR06		//   10 + 3880 = 3890 // 2 + 3880 + 2


enum ExternalArg
{
	printKernelIdx,
	printChannelIdx,
	printMatIdx,
	nonExternalArg,
};

#endif // CONSTANTS_H