#ifndef CONV1_PARAMS_H
#define CONV1_PARAMS_H

#include "cnn.h"

// input 28x28x1, ch_num = 5

const conv1_filter_ch00_weights00[FILTER_SIZE][FILTER_SIZE] = {
    { 0.0124,  0.1875,  0.1134},
    { 0.3180, -0.1194,  0.1318},
    { 0.1256,  0.3247, -0.3463}
};

const conv1_filter_ch01_weights00[FILTER_SIZE][FILTER_SIZE] = {
	{-0.1902,  0.2928,  0.2543},
	{ 0.2972,  0.0502,  0.0244},
	{ 0.1715, -0.1924,  0.2963}
};

const conv1_filter_ch02_weights00[FILTER_SIZE][FILTER_SIZE] = {
	{-0.5824, -0.3782, -0.6659},
	{-0.4372, -0.6331, -0.6271},
	{-0.6455, -0.5357, -0.6060}
};

const conv1_filter_ch03_weights00[FILTER_SIZE][FILTER_SIZE] = {
	{ 0.3625, -0.1436,  0.1321},
	{ 0.1683,  0.0952, -0.2777},
	{-0.2249,  0.1154, -0.2253}
};

const conv1_filter_ch04_weights00[FILTER_SIZE][FILTER_SIZE] = {
	{ 0.3358,  0.0061, -0.2654},
	{ 0.1674,  0.3248, -0.2838},
	{ 0.2682,  0.3277, -0.3537}
};

const conv1_filter_bias[NUM_05CH] = {-0.2676, -0.0370,  0.0005,  0.2774,  0.4532}

#endif CONV1_PARAMS_H