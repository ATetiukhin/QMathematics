/**
 * @file   task_factory.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#include "task_factory.hpp"
#include "equation.hpp"

TaskFactory * TaskFactory::pInstance_ = nullptr;
TaskFactoryDestroyer TaskFactory::destroyer_;

TaskFactoryDestroyer::~TaskFactoryDestroyer()
{
    delete pInstance_;
}
void TaskFactoryDestroyer::initialize(TaskFactory * p)
{
    pInstance_= p;
}

TaskFactory::TaskFactory()
{
}

TaskFactory::~TaskFactory()
{
}

TaskFactory & TaskFactory::getInstance()
{
    if (!pInstance_) {
        pInstance_ = new TaskFactory();
        destroyer_.initialize(pInstance_);
    }

    return *pInstance_;
}

Task * TaskFactory::createTask(int id)
{
    Task * newTask = nullptr;

    switch (id) {
    case 0:
        newTask = new EquationTask;
        break;
    default:
        throw std::runtime_error("type task -1");
    }

    return newTask;
}

/* End of 'task_factory.cpp' file */