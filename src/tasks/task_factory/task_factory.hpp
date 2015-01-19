/**
* @file   task_factory.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  The Abstract factory pattern.
*/

#ifndef TASK_FACTORY_HPP_INCLUDE
#define TASK_FACTORY_HPP_INCLUDE

#include "task.hpp"

class TaskFactory;

class TaskFactoryDestroyer
{
public:
    ~TaskFactoryDestroyer();
    void initialize(TaskFactory * p);
private:
    TaskFactory * pInstance_;
};

class TaskFactory
{
public:
    static TaskFactory & getInstance ();
    static Task        * createTask  (int id);

private:
    TaskFactory();
    TaskFactory(const TaskFactory &);
    TaskFactory & operator=(TaskFactory &);
    ~TaskFactory();
    friend class TaskFactoryDestroyer;

    static TaskFactory * pInstance_;
    static TaskFactoryDestroyer destroyer_;
};

#endif /* End of 'task_factory.hpp' file */