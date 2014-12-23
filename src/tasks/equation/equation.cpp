/**
 * @file   equation.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#include "equation.hpp"

EquationTask::EquationTask(QWidget *parent)
{
    EquationWidget * ui = new EquationWidget(parent);

    task_ = new TypeTaskEquation(ui);
    ui->connectEquationWidget(task_);
    ui_ = ui;
}

EquationTask::~EquationTask()
{
    delete task_;
    delete ui_;
}

/* End of 'equation.cpp' file */