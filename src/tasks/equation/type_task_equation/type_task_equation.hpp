/**
* @file   type_task_equation.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Implementation tasks equation.
*/

#ifndef TYPE_TASK_EQUATION_HPP_INCLUDE
#define TYPE_TASK_EQUATION_HPP_INCLUDE

#include "type_task.hpp"
#include <functional>
#include <QVector>

class DatabaseHelper;
class EquationWidget;

class TypeTaskEquation
    : public TypeTask
{
    Q_OBJECT
public:
    explicit TypeTaskEquation(EquationWidget * ui);
    virtual ~TypeTaskEquation();

public slots:
    void solveButtonClicked();

    void plotButtonClicked();

private:
    DatabaseHelper & dataBase_;
    EquationWidget & ui_;
    int idMethod_;
    QString equation_;
    QVector<double> parametersValues_;
    QVector<double> ans_;
};

#endif /* End of 'type_task_equation.hpp' file */