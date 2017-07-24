/**
 *  @file    MNISTParser.h
 *  @author  Jonathan Hernandez (jmher019)
 *  @date    7/23/2017
 *  @version 0.0
 *
 *  @brief used to parse images and labels from MNIST Database
 *
 *  @section DESCRIPTION
 *
 *  This static class contains two useful functions for parsing
 *  the image and label files. It is recommended that the programmer
 *  parse the image file first and then parse the labels file.
 *
 */

#ifndef MNIST_PARSER_H
#define MNIST_PARSER_H

// cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#include "ImageData.h"

using namespace std;

/**
 *  @brief Class that extends exception and used for specific error handling here
 */
class MNISTParserException : std::exception {
private:
	string message; // The error message

public:

	// Constructor
	MNISTParserException(string message);
	
	// Extracts the error message as a const char pointer
	const char* what() const noexcept;
};

/**
*  @brief Class that handles parsing image and label files from the MNIST Database
*/
class MNISTParser {
public:
	// static method that parses a MNIST image file
	static vector<ImageData*> parseImageFile(string name);
	
	// static method that parses a MNIST label file
	static void parseLabelFile(vector<ImageData*>& images, string name);

private:
	// static helper method that converts 4 bytes into a uint32_t
	static uint32_t convertToUInt(const char* data);
	
	// static helper method that checks if the file is opened or empty
	static void validateStream(ifstream& in, string name);
};

#endif // !MNIST_PARSER_H
