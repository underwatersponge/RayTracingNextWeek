#pragma once
#include "Utility.hpp"

class Interval {
public:
	Interval() : min(+infinity), max(-infinity) {} // default Interval is empty
	Interval(float min, float max) : min(min), max(max) {}
	Interval(const Interval& interval1, const Interval& interval2);


	float size()const { return max - min; }

	bool contains(float t)const {
		return min <= t && t <= max;
	}
	bool surrounds(float t)const {
		return min < t && t < max;
	}

	float clamp(float x) const  {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	Interval expand(float delta)const {
		auto padding = delta / 2.0;
		return Interval(min - padding, max + padding);
	}


public:
	float min, max;
	static const Interval empty, universe;

};

// do should tranfor by &? i think no need to do : just 2float 
Interval operator+(const Interval ival, const float displament);

Interval operator+(const float displament, const Interval ival);