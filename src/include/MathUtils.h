/**
 *  @file    MathUtils.h
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

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// cpp
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;

/**
 *  @brief Class that handles some numpy math functions
 */
class MathUtils {
public:
	// static method for generating random data from a normal distribution with a mean
	// of 0 and a variance of 1
	static double* randn(const uint32_t rows, const uint32_t cols);
	
	// static method that computes the dot product of 2 matrices
	static double dot(const double* vec1, const double* vec2, const uint32_t length);

	// static method that returns a matrix of zeroes
	static double* zeroes(const uint32_t rows, const uint32_t cols);

	// static method that finds the max value in the array
	static double argmax(const double* vec, const uint32_t length);

	// static method that returns an array with the exponential for each element
	static double* exp(double* vec, const uint32_t length);
};

#endif // !MATH_UTILS_H
