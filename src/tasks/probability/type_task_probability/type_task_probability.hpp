/**
 * @file   type_task_probability.hpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#ifndef TYPE_TASK_PROBABILITY_HPP_INCLUDE
#define TYPE_TASK_PROBABILITY_HPP_INCLUDE

#include "type_task.hpp"

class DatabaseHelper;
class ProbabilityWidget;

class TypeTaskProbability
    : public TypeTask
{
    Q_OBJECT
public:
    explicit TypeTaskProbability(ProbabilityWidget * ui);
    virtual ~TypeTaskProbability();

public slots:
    void answerButtonClicked();

private:
    DatabaseHelper & dataBase_;
    ProbabilityWidget & ui_;
};

#endif /* End of 'type_task_probability.hpp' file */