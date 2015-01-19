/**
* @file   type_task.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  General class @ref TypeTask for different type tasks.
*/

#ifndef TYPE_TASK_HPP_INCLUDE
#define TYPE_TASK_HPP_INCLUDE

#include <QObject>

class TypeTask
    : public QObject
{
    Q_OBJECT
public:
    virtual ~TypeTask()
    {}
};

#endif