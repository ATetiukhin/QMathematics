/**
* @file   cdbinrnk.cpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Method cdbinrnk.
*/

#include <cmath>
#include "cdbinrnk.hpp"
#include "libdieharder.hpp"

Cdbinrnk::Cdbinrnk()
{
}

Cdbinrnk::~Cdbinrnk()
{
}

bool Cdbinrnk::isRandom(QVector<double> &sample, double &r) const
{
	double result = diehard_rank_6x8(sample);
	r = result;
	return result <= 4 ? true : false;
}

Q_EXPORT_PLUGIN2(cdbinrnk, Cdbinrnk)

/* End of 'cdbinrnk.cpp' file */