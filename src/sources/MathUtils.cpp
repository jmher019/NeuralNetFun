/**
 *  @file    MathUtils.cpp
 *  @author  Jonathan Hernandez (jmher019)
 *  @date    8/12/2017
 *  @version 0.0
 *
 *  @brief static class that contains similar functionality to numpy
 *
 *  @section DESCRIPTION
 *
 *  This static class will be used as a substitute for some of the
 *  numpy functionality
 *
 */

#include "MathUtils.h"

/**
 *  @brief Used to generate a matrix filled with random numbers form a normal distribution
 *
 *  @param rows the number of rows in the matrix
 *  @param cols the number of cols in the matrix
 *  @return a double pointer to the array of data
 */
double* MathUtils::randn(const uint32_t rows, const uint32_t cols) {
	double* mat = new double[rows * cols];
	
	// construct a trivial random generator engine from a time-based seed:
	// TODO: perhaps use parallelism for such a trivial task here
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::normal_distribution<double> distribution(0.0, 1.0);

	const uint32_t length = rows * cols;
	for (uint32_t index = 0; index < length; index++) {
		mat[index] = distribution(generator);
	}

	return mat;
}

/**
 *  @brief Used to calculate the dot product between 2 vectors
 *
 *  @param vec1 pointer to the array for the first vector
 *  @param vec2 pointer to the array for the second vector
 *  @param length the length of both vectors
 *  @return the value of the dot product of both vectors
 */
double MathUtils::dot(const double* vec1, const double* vec2, const uint32_t length) {
	// TODO: perhaps use parallelism for such a trivial task here
	double sum;
	for (uint32_t index = 0; index < length; index++) {
		sum += vec1[index] * vec2[index];
	}

	return sum;
}

/**
 *  @brief Used to generate a matrix filled with 0's
 *
 *  @param rows number of rows in the matrix
 *  @param cols number of cols in the matrix
 *  @return a matrix of size rows x cols filled with 0's
 */
double* MathUtils::zeroes(const uint32_t rows, const uint32_t cols) {
	double* mat = new double[rows * cols];

	const uint32_t length = rows * cols;
	for (uint32_t index = 0; index < length; index++) {
		mat[index] = 0;
	}

	return mat;
}

/**
 *  @brief Used to find the max value in an array
 *
 *  @param vec the array containing elements
 *  @param length the size of the array
 *  @return the max value of the array
 */
double MathUtils::argmax(const double* vec, const uint32_t length) {
	double max = vec[0];
	for (uint32_t index = 1; index < length; index++) {
		max = max < vec[index] ? vec[index] : max;
	}
	return max;
}

/**
 *  @brief computes the exponential of each element in an array
 *
 *  @param vec the array containing elements
 *  @param length the size of the array
 *  @return the input array with the elements replaced with their exponential value
 */
double* MathUtils::exp(double* vec, const uint32_t length) {
	for (uint32_t index = 0; index < length; index++) {
		vec[index] = std::exp(vec[index]);
	}
	return vec;
}