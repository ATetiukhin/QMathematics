/**
* @file   equation.cpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  General class @ref EquationTask for the task type equation.
*/

#include "equation.hpp"

EquationTask::EquationTask(QWidget *parent)
{
    EquationWidget * ui = new EquationWidget(parent);

    task_ = new TypeTaskEquation(ui);
    ui->connectWidget(task_);
    ui_ = ui;
}

EquationTask::~EquationTask()
{
}

/* End of 'equation.cpp' file */