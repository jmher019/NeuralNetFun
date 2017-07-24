/**
*  @file    BitMapGenerator.cpp
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

#include "BitMapGenerator.h"

/**
 *  @brief Takes the Buffer stored in the ImageData and writes a bmp file
 *  
 *  @param img reference to a pointer of type ImageData
 *  @param filename the full path of the bmp that will be generated
 *  @return void
 */
void BitMapGenerator::generate(ImageData*& img, string filename) {
	ofstream out(filename.c_str(), std::ofstream::out | std::ofstream::binary);

	uint16_t width = img->getWidth();
	uint16_t height = img->getHeight();
	uint16_t size = width * height;
	
	// Here is the basic format for bmp files
	// 2 bytes for BFTYPE which is always set to 19778
	// 4 bytes for BFSIZE which is set to the total file size
	// 2 bytes for BFRESERVED1 which is always set to 0
	// 2 bytes for BFRESERVED2 which is always set to 0
	// 4 bytes for BFOFFBITS which is set to the sum of bytes of both headers
	//
	// 4 bytes for BISIZE size of bit map info header which is always set to 40
	// 4 bytes for BIWIDTH which is set to the image width in pixels
	// 4 bytes for BIHEIGHT which is set to the image height in pixels
	// 2 bytes for BIPLANES which is set to the number of color planes being used
	// 2 bytes for BIBITCOUNT which is the number of bits per pixel (24 for RGB)
	// 4 bytes for BICOMPRESSION which is the type of compression (0 for none)
	// 4 bytes for BIXPELSPERMETER which is the horizontal pixels per meter
	// 4 bytes for BIYPELSPERMETER which is the vertical pixels per meter
	// 4 bytes for BICLRUSED which is the number of colors used (if set to 0 then it is calculated from BIBITCOUNT)
	// 4 bytes for BICLRIMPORTANT which is the number of color that are important (if set to 0 then all are important)

	uint16_t remainder = width % 4;
	uint32_t fileSize = size * 3 + remainder * height + HEADERSIZE;

	BitMapGenerator::write(out, BFTYPE, 19778);
	BitMapGenerator::write(out, BFSIZE, fileSize);
	BitMapGenerator::write(out, BFRESERVED1, 0);
	BitMapGenerator::write(out, BFRESERVED2, 0);
	BitMapGenerator::write(out, BFOFFBITS, HEADERSIZE);
	BitMapGenerator::write(out, BISIZE, 40);
	BitMapGenerator::write(out, BIWIDTH, width);
	BitMapGenerator::write(out, BIHEIGHT, height);
	BitMapGenerator::write(out, BIPLANES, 1);
	BitMapGenerator::write(out, BIBITCOUNT, 24);
	BitMapGenerator::write(out, BICOMPRESSION, 0);
	BitMapGenerator::write(out, BISIZEIMAGE, size * 3);
	BitMapGenerator::write(out, BIXPELSPERMETER, 0);
	BitMapGenerator::write(out, BIYPELSPERMETER, 0);
	BitMapGenerator::write(out, BICLRUSED, 0);
	BitMapGenerator::write(out, BICLRIMPORTANT, 0);
	
	// The way to write the pixel data for RGB is to write
	// BGR. Also begin writing from the bottomost row and work
	// your way up. If the number of bytes written per row is not
	// divisible by 4 then pad it with bytes set to 0 until it is
	for (uint16_t y = height - 1; y < height; y--) {
		for (uint16_t x = 0; x < width; x++) {
			uint8_t val = ~img->getPixel(x, y);
			BitMapGenerator::write(out, RGBBLUE, val);
			BitMapGenerator::write(out, RGBGREEN, val);
			BitMapGenerator::write(out, RGBRED, val);
		}

		if (remainder == 1) {
			BitMapGenerator::write(out, RGBRESERVED, 0);
		}
		else if (remainder == 2) {
			BitMapGenerator::write(out, RGBRESERVED, 0);
			BitMapGenerator::write(out, RGBRESERVED, 0);
		}
		else if (remainder == 3) {
			BitMapGenerator::write(out, RGBRESERVED, 0);
			BitMapGenerator::write(out, RGBRESERVED, 0);
			BitMapGenerator::write(out, RGBRESERVED, 0);
		}
	}

	// close the file
	out.close();
};

/**
 *  @brief writes n bytes to out
 *
 *  @param out the ofstream containing the bmp file output
 *  @param n the number of bytes to be written
 *  @param val the 32 bit integer containing the data to be written
 *  @return void
 */
void BitMapGenerator::write(ofstream& out, uint8_t n, uint32_t val) {
	unsigned char c1, c2, c3, c4;
	switch (n) {
		case 1:
			c1 = c1 = (val & 0x000000ff);
			out << c1;
			break;
		case 2:
			c1 = (val & 0x0000ff00) >> 8;
			c2 = (val & 0x000000ff);
			out << c2 << c1;
			break;
		case 4:
			c1 = (val & 0xff000000) >> 24;
			c2 = (val & 0x00ff0000) >> 16;
			c3 = (val & 0x0000ff00) >> 8;
			c4 = (val & 0x000000ff);
			out << c4 << c3 << c2 << c1;
			break;
	}
}