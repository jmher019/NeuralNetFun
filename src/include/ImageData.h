/**
 *  @file    ImageData.h
 *  @author  Jonathan Hernandez (jmher019)
 *  @date    7/23/2017
 *  @version 0.0
 *
 *  @brief a container to hold raw image data
 *
 *  @section DESCRIPTION
 *
 *  This container will hold the raw image data and be used
 *  to get basic information from the image such as width,
 *  height, size, and label.
 *
 */

#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

// cpp
#include <memory>

using namespace std;

/**
 *  @brief Class that acts as a container for image and label data
 */
class ImageData {
private:
	uint8_t* data = 0; // the raw image data
	uint16_t size = 0; // the size of the array
	uint16_t width = 0; // the width of the image in pixels
	uint8_t label = 0; // the label for the image which are the ints 0 - 9 (inclusive)

public:
	// Empty constructor (Note: only useful for initializing a vector container)
	ImageData(void);

	// Contructor (Note: use this one)
	ImageData(uint8_t* data, uint16_t width, uint16_t size);

	// Destructor
	~ImageData(void);

	// returns the pixel value at that index
	uint8_t getPixel(uint16_t i) const;

	// returns the pixel value located at x and y
	uint8_t getPixel(uint16_t x, uint16_t y) const;

	// returns the label
	uint8_t getLabel() const;

	// returns the width
	uint16_t getWidth() const;

	// returns the height
	uint16_t getHeight() const;

	// sets the label
	void setLabel(uint8_t label);
};

#endif // !IMAGE_DATA_H
