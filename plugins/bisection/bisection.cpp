/**
 * @file   bisection.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#include <QVector>
#include <cmath>
#include "bisection.hpp"

Bisection::Bisection()
{
}

Bisection::~Bisection()
{
}

void Bisection::calculate(const std::function<double (double)> & f,
               QVector<double> const & parametersValues, QVector<double> & ans) const
{
#if _DEBUG
    if (parametersValues.size() != 3) {
        std::runtime_error("Debug: wrong parametrs");
    }
#endif
    double const epsilon = parametersValues[2];

    double x1 = parametersValues[0];
    double x2 = parametersValues[1];
    double x3 = 0;
    int count = 0;
    int iter = 1000;
    double answer = 0;

    double f1 = 0;
    double f2 = 0;
    double f3 = 0;

    do {
        if (count == iter) {
            break;
        }
        x3 = (x1 + x2) / 2.0;
        f1 = f(x1);
        f3 = f(x3);

        if (f1 * f3 < 0) {
            x2 = x3;
        } else {
            x1 = x3;
        }
        count++;
        answer = f(x3);
    } while (fabs(answer) >= epsilon);

    ans.push_back(x3);
}

Q_EXPORT_PLUGIN2(bisection, Bisection)

/* End of 'bisection.cpp' file */