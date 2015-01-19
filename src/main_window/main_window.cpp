/**
* @file   main_window.cpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  @ref MainWindow is control class.
*/

#include <stdexcept>

#include <QAction>
#include <QMenuBar>
#include <QUrl>
#include <QMessageBox>

#include "main_window.hpp"
#include "database_helper.hpp"

#include "qsql_connection_dialog.hpp"
#include "select_task_dialog.hpp"

#include "task.hpp"
#include "task_factory.hpp"

MainWindow::MainWindow()
    : data_base_helper_(DatabaseHelper::getInstance())
    , currentTask_(nullptr)
{
    resize(450, 300);
    create_actions();
    create_menus();
}

MainWindow::~MainWindow()
{}

void MainWindow::create_actions()
{
    const int sizeAction = 6;
    main_action_.resize(sizeAction);
    char const * const nameAction[sizeAction] = {"&Connection", "&Disconnect", "&Exit",
        "&New task", "&Table task", "Help"};

    for (int i = 0; i < sizeAction; ++i) {
        main_action_[i] = new QAction(tr(nameAction[i]), this);
    }

    connect(main_action_[0], SIGNAL(triggered()), this, SLOT(exec()));
    connect(main_action_[1], SIGNAL(triggered()), this, SLOT(disconnection()));
    connect(main_action_[2], SIGNAL(triggered()), this, SLOT(close()));
    connect(main_action_[3], SIGNAL(triggered()), this, SLOT(select_task_dialog()));
    connect(main_action_[4], SIGNAL(triggered()), this, SLOT(pass()));
    connect(main_action_[5], SIGNAL(triggered()), this, SLOT(about()));

    main_action_[1]->setEnabled(false);
    main_action_[3]->setEnabled(false);
    main_action_[4]->setEnabled(false);
}

void MainWindow::create_menus()
{
    const int sizeMenu = 3;
    main_menu_.resize(sizeMenu);
    char const * const nameMenu[sizeMenu] = {"&File", "&Task", "Help"};

    for (int i = 0; i < sizeMenu; ++i) {
        main_menu_[i] = menuBar()->addMenu(QObject::tr(nameMenu[i]));
    }

    main_menu_[0]->addAction(main_action_[0]);
    main_menu_[0]->addAction(main_action_[1]);
    main_menu_[0]->addSeparator();
    main_menu_[0]->addAction(main_action_[2]);
    main_menu_[1]->addAction(main_action_[3]);
    main_menu_[1]->addAction(main_action_[4]);
    main_menu_[2]->addAction(main_action_[5]);
}

void MainWindow::exec()
{
    try {
        if (!data_base_helper_.isOpen()) {
            qsql_connection_dialog();
            enabled_menu();
        }
        select_task_dialog();
    } catch (std::exception & e) {
        QMessageBox::warning(this, tr("Error"), tr("Error: ") + e.what());
    }
}

bool MainWindow::connection_from_commandline(const QStringList & args)
{
    int count = args.count();
    for (int i = 1; i < count; ++i) {
        QUrl url(args.at(i), QUrl::TolerantMode);
        if (!url.isValid()) {
            qWarning("Invalid URL: %s", qPrintable(args.at(i)));
            continue;
        }

        data_base_helper_.connection(url.scheme(), url.path().mid(1), url.host(),
                                     url.userName(), url.password(), url.port(-1));
    }

    return count > 1;
}

void MainWindow::qsql_connection_dialog()
{
    QSqlConnectionDialog dialog(this);

    if (dialog.exec() != QDialog::Accepted) {
        throw std::runtime_error("unable to open database");
    }

    data_base_helper_.connection(dialog.driverName(), dialog.databaseName(), dialog.hostName(),
                                 dialog.userName(), dialog.password(), dialog.port());
}

void MainWindow::disconnection()
{
    enabled_menu();
}

void MainWindow::enabled_menu()
{
    for (int i = 0; i < 5; ++i) {
        if (i == 2) {
            continue;
        }
        main_action_[i]->setEnabled(!(main_action_[i]->isEnabled()));
    }
}

void MainWindow::select_task_dialog()
{
    SelectTaskDialog dialog(this);

    if (dialog.exec() != QDialog::Accepted) {
        throw std::runtime_error("no task is selected");
    }

    TaskFactory & newTask_ = TaskFactory::getInstance();
    delete currentTask_;
    currentTask_  = nullptr;

    currentTask_ = newTask_.createTask(dialog.getNumberTask());

    setCentralWidget(currentTask_->getWidget());
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"), tr("The <b>Application</b> Solves equations of one variable"));
}

void MainWindow::pass()
{
}

/* End of 'main_window.cpp' file */