/**
 * @file   cdbinrnk.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#include <QVector>
#include <cmath>
#include "cdbinrnk.hpp"

Cdbinrnk::Cdbinrnk()
{
}

Cdbinrnk::~Cdbinrnk()
{
}

/**
 * @param  nums  an array
 * @return void 
 */
void Cdbinrnk::getFrequencies(QMap<double, double> &freqs, QVector<double> &sample) const
{
    for (int x : sample) {
        freqs[x] += 1;
        //if (freqs.containsKey(x)) {
        //    freqs.put(x, freqs.get(x) + 1);
        //} else {
        //    freqs.put(x, 1);
        //}
    }
}

/**
 * Calculates the chi-square value for N positive integers less than r
 * @param  randomNums  a uniformly-randomly-generated array of integers
 * @param  r           upper bound for the random range
 * @return             whether it is likely to be uniformly randomly generated
 */
bool Cdbinrnk::isRandom(QVector<double> &sample, double r) const
{
    /// According to Sedgewick: "This is valid if N is greater than about 10r"
    if (sample.size() <= 10 * r)
        return false;

    /// PART A: Get frequency of randoms
    QMap<double, double> ht;
    getFrequencies(ht, sample);

    /// PART B: Calculate chi-square - this approach is in Sedgewick
    double n_r = sample.size() / r;
    double chiSquare = 0;

    for (int v : ht.values())
    {
        double f = v - n_r;
        chiSquare += f * f;
    }
    chiSquare /= n_r;

    /// PART C: According to Swdgewick: "The statistic should be within 2(r)^1/2 of r
    /// This is valid if N is greater than about 10r"
    return fabs(chiSquare - r) <= 2 * sqrt(r);
}

Q_EXPORT_PLUGIN2(cdbinrnk, Cdbinrnk)

/* End of 'bisection.cpp' file */