#ifndef RAW_POINT_H__
#define RAW_POINT_H__

#include <vector>

using std::vector;

class RawPoint
{
private:
	vector<double> vals;
public:
	RawPoint(vector<double> v)
	{
		vals = v;
	}

	vector<double> get_vals() const
	{
		return vals;
	}
};

#endif // RAW_POINT_H__
