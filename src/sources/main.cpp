/**
 *  @file    main.cpp
 *  @author  Jonathan Hernandez (jmher019)
 *  @date    7/23/2017
 *  @version 0.0
 *
 *  @brief used to run test functions
 *
 *  @section DESCRIPTION
 *
 *  We can use this file to run test programs
 *
 */

#include "MNISTParser.h"
#include "BitMapGenerator.h"
#include "MathUtils.h"

#include <cstdlib>
#include <ctime>

/**
 *  @brief this function will clean up vectors containing pointers of type ImageData
 *
 *  @param images the vector object reference
 *  @return void
 */
void cleanup(vector<ImageData*>& images) {
	for (size_t i = images.size() - 1; i > -1; i--) {
		delete images[i];
		images[i] = nullptr;
	}

	images.clear();
}

/**
 *  @brief this function tests the capability to parse image and label files
 *         from the MNIST Database
 *
 *  @return void
 */
void testMnistParser() {
	// First parse the image file
	cout << "Parsing training images" << endl;
	vector<ImageData*> images = MNISTParser::parseImageFile(
		string("D:\\Dev\\Test\\NeuralNetFun\\testData\\train-images.idx3-ubyte")
	);
	cout << "Parsed training images" << endl;

	// if the vector is empty then the parsing was a success
	if (!images.empty()) {
		// parse the label file
		cout << "Parsing label file" << endl;
		MNISTParser::parseLabelFile(
			images, string("D:\\Dev\\Test\\NeuralNetFun\\testData\\train-labels.idx1-ubyte")
		);
		cout << "Paresed label file" << endl;

		// initialize the random seed
		// if you don't initialize the random seed with something new
		// you will get the exact same index every time
		srand(static_cast<uint32_t>(time(0)));
		int randomIndex = rand() % images.size();

		// now write the randomly selected image as a bmp file
		cout << "Picking an image at random and generating a bmp" << endl;
		BitMapGenerator::generate(
			images[randomIndex], string("D:\\Dev\\Test\\NeuralNetFun\\testData\\test-image.bmp")
		);
		cout << "Image generated" << endl;
	}
	else {
		cout << "Parse failed" << endl;
	}

	cout << "Cleaning Up" << endl;
	cleanup(images);
}

void testMathUtils() {
	cout << "Testing randn..." << endl;
	const uint32_t rows = 100000;
	const uint32_t cols = 1;
	const uint32_t length = rows * cols;
	double* mat = MathUtils::randn(rows, cols);

	ofstream out("D:\\Dev\\Test\\NeuralNetFun\\testData\\test-randn.csv", std::ofstream::out);

	for (uint32_t index = 0; index < length; index++) {
		out << mat[index] << endl;
	}

	delete mat;
	mat = nullptr;

	// TODO: add more tests
}

int main() {
	testMnistParser();
	testMathUtils();
	system("pause");
	return 0;
}