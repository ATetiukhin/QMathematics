/**
 * @file   plugin_interface.hpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#ifndef PLUGIN_INTERFACE_HPP_INCLUDE
#define PLUGIN_INTERFACE_HPP_INCLUDE

#include <QtPlugin>
#include <functional>

class PluginInterface
{
public:
    virtual ~PluginInterface()
    {}

    virtual void calculate(const std::function<double (double)> & f,
                           QVector<double> const & parametersValues, QVector<double> & ans) const = 0;
};

Q_DECLARE_INTERFACE(PluginInterface, "PluginInterface")

#endif /* End of 'plugin_interface.hpp' file */