/**
* @file   equation.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  General class @ref EquationTask for the task type equation.
*/

#ifndef EQUATION_HPP_INCLUDE
#define EQUATION_HPP_INCLUDE

#include "task.hpp"
#include "equation_widget.hpp"
#include "type_task_equation.hpp"

class EquationWidget;

class EquationTask
    : public Task
{
    Q_OBJECT
public:
    explicit EquationTask(QWidget *parent = nullptr);
    virtual ~EquationTask();
};

#endif /* End of 'equation.hpp' file */