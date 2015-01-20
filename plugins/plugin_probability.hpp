/**
* @file   plugin_probability.hpp
* @Author ATetiukhin
* @date   December, 2014
* @brief  Brief description of file.
*/

#ifndef PLUGIN_PROBABILITY_HPP_INCLUDE
#define PLUGIN_PROBABILITY_HPP_INCLUDE

#include <QtPlugin>

class PluginProbability
{
public:
    virtual ~PluginProbability()
    {}

    virtual bool isRandom(QVector<double> &sample, double &r) const = 0;
};

Q_DECLARE_INTERFACE(PluginProbability, "PluginInterface")

#endif /* End of 'plugin_probability.hpp' file */