/**
* @file   probability.cpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  General class @ref ProbabilityTask for the task type probability.
*/

#include "probability.hpp"

ProbabilityTask::ProbabilityTask(QWidget *parent)
{
    ProbabilityWidget * ui = new ProbabilityWidget(parent);

    task_ = new TypeTaskProbability(ui);
    ui->connectWidget(task_);
    ui_ = ui;
}

ProbabilityTask::~ProbabilityTask()
{
}

/* End of 'probability.cpp' file */