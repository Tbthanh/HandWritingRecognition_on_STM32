#ifndef CONSTANTS_H
#define CONSTANTS_H

#define INPUT_SIZE 		6
#define FILTER_SIZE 	3
#define OUTPUT_SIZE 	10		// Number of output class, in this case 10 (0 to 9)
#define AFTER_CONV1_DIM	4
#define AFTER_CONV2_DIM	2
// #define AFTER_MAXP1_DIM	12
// #define AFTER_CONV3_DIM	10
// #define AFTER_CONV4_DIM	8
// #define AFTER_MAXP2_DIM	4

#define POOLING_SIZE	2

// some tinkering
#define NUM_01CH 		1
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

enum ExternalArg
{
	// nonExternalArg,
	printKernelIdx,
	printChannelIdx,
	printMatIdx,
};

enum DebugOption
{
	noD_ebug,
	result_mat_only,
	layer1_indept,
	layer2_indept,
	layer3_indept,
	layer4_indept,
	fc1_indept,
	fc2_indept,

};

#endif // CONSTANTS_H