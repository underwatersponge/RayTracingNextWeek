#pragma once

#include <limits>
#include <cmath>
//#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>

// constons
const float infinity = std::numeric_limits<float>::infinity();
const float pi{ 3.14159265 };

// utility funcion

inline float degreeToRadians(const float degree) {
	return degree * pi / 180.0;
}

// c =============
//inline float randFloat() {
//	return std::rand() / (RAND_MAX + 1.0);
//}
//
//inline float randFloat(float min, float max) {
//	return min + (max - min) * randFloat();
//}

// cpp =============
inline float randFloat() {
	std::random_device rd;
	std::mt19937 gen{rd()};
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	
	return dist(gen);
}

inline float randFloat(float min, float max) {
	return min + (max - min) * randFloat();
}

inline int randInt(int min, int max) {
	return int(randFloat(min, max + 1));
}