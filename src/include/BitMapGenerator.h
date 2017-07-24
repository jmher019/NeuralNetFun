/**
 *  @file    BitMapGenerator.h
 *  @author  Jonathan Hernandez (jmher019)
 *  @date    7/23/2017
 *  @version 0.0
 *
 *  @brief used to write ImageData objects into bmp formatted files
 *
 *  @section DESCRIPTION
 *
 *  This static class contains one useful function for writing
 *  a ImageData object to a bmp file.
 *
 */

#ifndef BIT_MAP_GENERATOR_H
#define BIT_MAP_GENERATOR_H

// cpp
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

#include "ImageData.h"

using namespace std;

/**
 *  @brief Class that handles writing ImageData objects as bmp files
 */
class BitMapGenerator {
public:
	// static method for generating a bmp file
	static void generate(ImageData*& img, string filename);

private:
	// static helper method used to write n number of bytes to out
	static void write(ofstream& out, uint8_t n, uint32_t val);
	
	// BMP FILE HEADER constants
	static const uint8_t BFTYPE = 2;
	static const uint8_t BFSIZE = 4;
	static const uint8_t BFRESERVED1 = 2;
	static const uint8_t BFRESERVED2 = 2;
	static const uint8_t BFOFFBITS = 4;

	// BMP INFO HEADER constants
	static const uint8_t BISIZE = 4;
	static const uint8_t BIWIDTH = 4;
	static const uint8_t BIHEIGHT = 4;
	static const uint8_t BIPLANES = 2;
	static const uint8_t BIBITCOUNT = 2;
	static const uint8_t BICOMPRESSION = 4;
	static const uint8_t BISIZEIMAGE = 4;
	static const uint8_t BIXPELSPERMETER = 4;
	static const uint8_t BIYPELSPERMETER = 4;
	static const uint8_t BICLRUSED = 4;
	static const uint8_t BICLRIMPORTANT = 4;

	// BMP PIXEL CONSTANTS
	static const uint8_t RGBBLUE = 1;
	static const uint8_t RGBGREEN = 1;
	static const uint8_t RGBRED = 1;
	static const uint8_t RGBRESERVED = 1;
	static const uint8_t HEADERSIZE = 54;
};

#endif // !BIT_MAP_GENERATOR_H
