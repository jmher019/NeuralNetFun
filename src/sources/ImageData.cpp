/**
 *  @file    ImageData.cpp
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

#include "ImageData.h"

 /**
  *  @brief empty constructor
  */
ImageData::ImageData(void):
	data(0),
	size(0),
	width(0),
	label(0) {}

/**
 *  @brief constructor
 *
 *  @param data pointer to array containing image pixels
 *  @param width the width of the image in pixels
 *  @param size the total number of pixels
 */
ImageData::ImageData(uint8_t* data, uint16_t width, uint16_t size):
	data(data),
	width(width),
	size(size) {
}

/**
 *  @brief destructor
 */
ImageData::~ImageData(void) {
	if (data) {
		delete data;
		data = 0;
	}
}

/**
 *  @brief returns the pixel stored at that index
 *
 *  @param i the index of the pixel of interest
 *  @return the pixel
 */
uint8_t ImageData::getPixel(uint16_t i) const {
	return data[i];
}

/**
 *  @brief returns the pixel stored at x and y
 *
 *  @param x the horizontal position of the pixel
 *  @param y the vertical position of the pixel
 *  @return the pixel
 */
uint8_t ImageData::getPixel(uint16_t x, uint16_t y) const {
	return data[x + y * width];
}

/**
 *  @brief returns the label
 *
 *  @return the label
 */
uint8_t ImageData::getLabel() const {
	return label;
}

/**
 *  @brief returns the width
 *
 *  @return the width
 */
uint16_t ImageData::getWidth() const {
	return width;
}

/**
 *  @brief returns the height
 *
 *  @return the height
 */
uint16_t ImageData::getHeight() const {
	return size / width;
}

/**
 *  @brief sets the label
 *
 *  @return void
 */
void ImageData::setLabel(uint8_t label) {
	this->label = label;
}