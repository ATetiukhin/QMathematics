/**
 * @file   probability.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
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