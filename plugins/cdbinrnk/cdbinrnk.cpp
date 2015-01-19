/**
* @file   cdbinrnk.cpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Method cdbinrnk.
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

bool Cdbinrnk::isRandom(QVector<double> &sample, double r) const
{
    if (sample.size() <= 10 * r)
        return false;

    QMap<double, double> ht;
    getFrequencies(ht, sample);

    double n_r = sample.size() / r;
    double chiSquare = 0;

    for (int v : ht.values())
    {
        double f = v - n_r;
        chiSquare += f * f;
    }
    chiSquare /= n_r;

    return fabs(chiSquare - r) <= 2 * sqrt(r);
}

Q_EXPORT_PLUGIN2(cdbinrnk, Cdbinrnk)

/* End of 'cdbinrnk.cpp' file */