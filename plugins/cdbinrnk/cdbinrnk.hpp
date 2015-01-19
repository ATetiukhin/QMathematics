/**
* @file   cdbinrnk.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Method cdbinrnk.
*/

#ifndef DICHOTOMY_HPP_INCLUDE
#define DICHOTOMY_HPP_INCLUDE

#include <QObject>
#include "plugin_probability.hpp"

class Cdbinrnk
    : public QObject
    , public PluginProbability
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "PluginInterface")
    Q_INTERFACES(PluginProbability)
public:
    Cdbinrnk();
    virtual ~Cdbinrnk();

    void getFrequencies(QMap<double, double> &freqs, QVector<double> &sample) const;

    bool isRandom(QVector<double> &sample, double r) const;
};

#endif /* End of 'cdbinrnk.hpp' file */