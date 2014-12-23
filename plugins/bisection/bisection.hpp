/**
 * @file   bisection.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#ifndef DICHOTOMY_HPP_INCLUDE
#define DICHOTOMY_HPP_INCLUDE

#include <QObject>
#include "plugin_interface.hpp"

class Bisection
    : public QObject
    , public PluginInterface
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "PluginInterface")
    Q_INTERFACES(PluginInterface)
public:
    Bisection();
    virtual ~Bisection();

    virtual void calculate(const std::function<double (double)> & f,
                           QVector<double> const & parametersValues, QVector<double> & ans) const;
};

#endif /* End of 'dichotomy.hpp' file */