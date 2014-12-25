/**
 * @file   probability_widget.hpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#ifndef EQUATION_PROBABILITY_HPP_INCLUDE
#define EQUATION_PROBABILITY_HPP_INCLUDE

#include <QWidget>

#include "probability.hpp"
#include "type_task_probability.hpp"
#include "ui_probability_widget.h"

class ProbabilityWidget
    : public QWidget
    , private Ui::ProbabilityWidgetUI
{
    Q_OBJECT
public:
    ProbabilityWidget(QWidget *parent);

    ~ProbabilityWidget();

    void connectWidget(TypeTask * task);

    void updateComboBox(QStringList const & namesMethods);

    void getEquationParameters(int & idMethod) const;

    void updateResult(QString const & namesMethods);
};

#endif

/* End of 'probability_widget.hpp' file */