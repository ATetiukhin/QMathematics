/**
* @file   equation_widget.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Widget task equation.
*/


#ifndef EQUATION_WIDGET_HPP_INCLUDE
#define EQUATION_WIDGET_HPP_INCLUDE

#include <QString>
#include <QWidget>
#include "equation.hpp"
#include "type_task_equation.hpp"
#include "ui_equation_widget.h"

class EquationWidget
    : public QWidget
    , private Ui::EquationWidgetUI
{
    Q_OBJECT
public:
    EquationWidget(QWidget *parent);

    ~EquationWidget();

    void connectWidget(TypeTask * task);

    void updateComboBox(QStringList const & namesMethods);

    void getEquationParameters(QString & equation) const;

    void getEquationParameters(QString & equation, QVector<double> & parametersValues, int & idMethod) const;

    void updateResult(QString const & namesMethods);

private slots:
    void clearButtonClicked();
};

#endif

/* End of 'equation_widget.hpp' file */