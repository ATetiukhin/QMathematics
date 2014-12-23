/**
 * @file   equation.hpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
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