/**
 *  @file    MNISTParser.cpp
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

#include "MNISTParser.h"

/**
 *   @brief  Class constructor
 *
 *   @param  message a string that contains a descriptive error
 */
MNISTParserException::MNISTParserException(string message) : message(message) {
}

/**
 *   @brief  used to extract the error message from the exception
 *
 *   @return a const char pointer container the error message
 */
const char* MNISTParserException::what() const noexcept {
	return message.c_str();
}

/**
 *   @brief  parses the image file
 *
 *   @param  name the full path to the image file
 *   @return a vector containing pointers of type ImageData for each image
 */
vector<ImageData*> MNISTParser::parseImageFile(string name) {
	ifstream in(name.c_str(), std::ifstream::in | std::ifstream::binary);

	// If the file is not opened or is empty, throw an exception and
	// return an empty vector
	try {
		MNISTParser::validateStream(in, name);
	}
	catch (const exception& e) {
		cout << e.what() << endl;
		return vector<ImageData*>();
	}
	
	// Every image file from the MNIST Database is formated like so:
	// int32 magic number
	// int32 number of images
	// int32 width in pixels
	// int32 height in pixels
	// raw image data
	unique_ptr<char> magicNumber = unique_ptr<char>(new char[4]);
	unique_ptr<char> numberOfItems = unique_ptr<char>(new char[4]);
	unique_ptr<char> widthBytes = unique_ptr<char>(new char[4]);
	unique_ptr<char> heightBytes = unique_ptr<char>(new char[4]);

	in.read(magicNumber.get(), 4);
	in.read(numberOfItems.get(), 4);
	in.read(widthBytes.get(), 4);
	in.read(heightBytes.get(), 4);

	// Now that we read the header info, lets get width, height, size, and
	// number of images
	const uint16_t width = static_cast<uint16_t>(convertToUInt(widthBytes.get()));
	const uint16_t height = static_cast<uint16_t>(convertToUInt(heightBytes.get()));
	const uint16_t size = width * height;
	const uint32_t numImages = convertToUInt(numberOfItems.get());
	vector<ImageData*> images(numImages, nullptr);

	// loop through the raw data and store them inside of ImageData objects
	for (uint32_t i = 0; i < numImages; i++) {
		char* data = new char[size];
		in.read(data, size);
		images[i] = new ImageData((uint8_t*)data, width, size);
	}

	// close the file
	in.close();

	return images;
}

/**
 *   @brief  parses the label file
 *
 *   @param  images the vector containing ImageData pointers for each image
 *   @param  name the full path to the label file
 *   @return void
 */
void MNISTParser::parseLabelFile(vector<ImageData*>& images, string name) {
	ifstream in(name.c_str(), std::ifstream::in | std::ifstream::binary);

	// If the file is not opened or is empty, throw an exception and
	// return
	try {
		MNISTParser::validateStream(in, name);
		if (images.size() == 0) {
			throw MNISTParserException(
				string("There are no image data objects in this vector.")
			);
		}
	}
	catch (const exception& e) {
		cout << e.what() << endl;
		return;
	}

	in.seekg(0, in.end);
	streampos length = in.tellg();
	in.seekg(0, in.beg);

	// The header is only 8 bytes long
	streampos diff = 8;

	// The labels file from the MNIST Database is formated like so:
	// int32 magic number
	// int32 number of labels
	// raw data with values ranging from 0 to 9 (inclusive)
	unique_ptr<char> magicNumber = unique_ptr<char>(new char[4]);
	unique_ptr<char> numberOfItems = unique_ptr<char>(new char[4]);
	unique_ptr<char> labelBytes = unique_ptr<char>(new char[static_cast<uint32_t>(length - diff)]);

	in.read(magicNumber.get(), 4);
	in.read(numberOfItems.get(), 4);
	in.read(labelBytes.get(), length - diff);

	// Let's take the raw data and assign the labels to each ImageData object
	uint32_t numLabels = convertToUInt(numberOfItems.get());
	for (uint32_t i = 0; i < numLabels; i++) {
		images[i]->setLabel(static_cast<uint8_t>(labelBytes.get()[i]));
	}

	// close the file
	in.close();
}

/**
 *   @brief  checks if the ifstream has been opened or is empty
 *
 *   @param  in the ifstream object for the file we are attempting to ingest
 *   @param  name the full path of the file
 *   @return void
 */
void MNISTParser::validateStream(ifstream& in, string name) {
	// Check if the file is open
	if (!in.is_open()) {
		throw MNISTParserException(
			"File: " + name + " failed to open!"
		);
	}

	in.seekg(0, in.end);
	streampos length = in.tellg();

	if (length == static_cast<streampos>(0)) {
		throw MNISTParserException(
			"File: " + name + " is empty!"
		);
	}

	in.seekg(0);
}

 /**
  *   @brief  helper method for converting char array of size 4 to uint32_t
  *
  *   @param  data the char pointer which contains 4 bytes representing an uint32_t
  *   @return the uint32_t value of the 4 bytes
  */
uint32_t MNISTParser::convertToUInt(const char* data) {
	unsigned char c1 = static_cast<unsigned char>(data[0]);
	unsigned char c2 = static_cast<unsigned char>(data[1]);
	unsigned char c3 = static_cast<unsigned char>(data[2]);
	unsigned char c4 = static_cast<unsigned char>(data[3]);

	return (c1 << 24) | (c2 << 16) | (c3 << 8) | c4;
}