#include "Interval.h"

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

Interval::Interval(const Interval& interval1, const Interval& interval2)
{
	min = interval1.min <= interval2.min ? interval1.min : interval2.min;
	max = interval1.max >= interval2.max ? interval1.max : interval2.max;

}

Interval operator+(const Interval ival, const float displament)
{
	return Interval{ ival.min + displament, ival.max + displament };
}

Interval operator+(const float displament, const Interval ival)
{
	return ival + displament;
}
