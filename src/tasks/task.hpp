/**
 * @file   task.hpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
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