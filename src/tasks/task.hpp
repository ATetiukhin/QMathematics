/**
* @file   task.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  General class @ref Task for different tasks.
*/

#ifndef TASK_HPP_INCLUDE
#define TASK_HPP_INCLUDE

#include <QWidget>
#include "type_task.hpp"

class Task
    : public QObject
{
    Q_OBJECT
public:
    virtual ~Task()
    {}

    QWidget * getWidget()
    {
        return ui_;
    }

protected:
    TypeTask * task_;
    QWidget * ui_;
};

#endif /* End of 'task.hpp' file */