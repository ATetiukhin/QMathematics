/**
* @file   probability.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  General class @ref ProbabilityTask for the task type probability.
*/

#ifndef PROBABILITY_HPP_INCLUDE
#define PROBABILITY_HPP_INCLUDE

#include "task.hpp"
#include "probability_widget.hpp"
#include "type_task_probability.hpp"

class ProbabilityWidget;

class ProbabilityTask
    : public Task
{
    Q_OBJECT
public:
    explicit ProbabilityTask(QWidget *parent = nullptr);
    virtual ~ProbabilityTask();
};

#endif /* End of 'probability.hpp' file */