#ifndef CONV1_PARAMS_H
#define CONV1_PARAMS_H

#include "constants.h"

// input 28x28x1, ch_num = 5
// Total 50 param, 45 from weights, 5 from biases

const float conv1_filter_weight[CONV1_K_NUM * NUM_01CH * FILTER_SIZE * FILTER_SIZE] = {
	0, 0, 0,
	0, 1, 0,
	0, 0, 0,
	
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	
	0, 0, 0,
	1, 1, 1,
	0, 0, 0,
	
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,

	1, 0, 1,
	0, 1, 0,
	1, 0, 1,
};

const float conv1_filter_bias[CONV1_K_NUM] = {
	1.0, 0.8, 0.7, -0.6, 0.5,
};

#endif // CONV1_PARAMS_H