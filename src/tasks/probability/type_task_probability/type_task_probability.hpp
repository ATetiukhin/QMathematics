/**
* @file   type_task_probability.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Implementation tasks probability.
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