/**
 * @file   probability.hpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
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