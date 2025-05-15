#pragma once

#include <cstdlib>
#include <iostream>
#include"../../third/stb_image.h"
//const char* a = stbi_failure_reason();
//int channels_in_file();

class RTWImage {
public:
	RTWImage() {};

	RTWImage(const char* imageFileName) {
		// getenv("under water sponge");// no for that 
		// not right now @fix latter under water sponge
		auto filename = std::string(imageFileName);
		if (load(filename)) {
			std::cout << "zero!!!!!!!!!!" << '\n';
			return;
		}
		if (load("../" + filename)) {
			std::cout << "one1111111111" << "\n";
			return;
		}

		std::cerr << "ERROR: Could not load image file" << imageFileName << ".\n";
	}

	~RTWImage() {
		delete[] bdata;
		stbi_image_free(fdata);
		//STBI_FREE(fdata);
	}

	bool load(const std::string filename) {
		auto n = bytesPerPixel;
		//std::cout << typeid(n).name() << typeid(n).raw_name() << std::endl;// uws want to look this
		fdata = stbi_loadf(filename.c_str(), &imageWidth, &imageHeight, &n, bytesPerPixel);
		if (fdata == nullptr) return false;

		bytesPerScanline = imageWidth * bytesPerPixel;
		convertToBytes();
		return true;
	};


	int width() const { return(fdata == nullptr) ? 0 : imageWidth; }
	int height()const { return(fdata == nullptr) ? 0 : imageHeight; }

	const unsigned char* pixelData(int x, int y) const {
		static unsigned char magenta[] = { 255, 0, 255 };
		if (bdata == nullptr) return magenta;

		x = clamp(x, 0, imageWidth);
		y = clamp(y, 0, imageHeight);

		return bdata + y * bytesPerScanline + x * bytesPerPixel;
	}

private:
	const int bytesPerPixel = 3;
	float* fdata = nullptr; // linear floatingg point pixel data
	unsigned char* bdata = nullptr; // linear 8-bit pixel data
	int imageWidth = 0; // load image width
	int imageHeight = 0; // load iage height
	int bytesPerScanline = 0; // bytes of horizontal line 

private:
	static int clamp(int x, int low, int high) {
		if (x < low) return low;
		if (x < high) return x;
		return high - 1;
	}
	
	static unsigned char floatToByte(float value) {
		if (value <= 0.0) {
			return 0;
		}if (1.0 <= value) {
			return 255;
		}
		return static_cast<unsigned char>(256.0 * value);
	}

	void convertToBytes() {
		// convert linear floating point pixel data to bytes, storing the resulting byt
		// data to "bdata" <class member> : type is unsigned char*
		int totalBytes = imageWidth * imageHeight * bytesPerPixel;
		bdata = new unsigned char[totalBytes];

		// interate through all pixel components, converting from[0.0, 1.0] float value to unsigned [0, 255] byte value
		auto* bptr = bdata;
		auto* fptr = fdata;
		for (auto i = 0; i < totalBytes; i++, fptr++, bptr++) {
			*bptr = floatToByte(*fptr);
		}
	}
};
