#ifndef DOMAIN_H__
#define DOMAIN_H__

class Domain
{
private:
	double lower_bound;
	double upper_bound;
public:
	Domain(double lb, double ub)
		:lower_bound(lb), upper_bound(ub)
	{}

	double get_lower_bound() const
	{
		return lower_bound;
	}

	double get_upper_bound() const
	{
		return upper_bound;
	}
};

#endif // DOMAIN_H__