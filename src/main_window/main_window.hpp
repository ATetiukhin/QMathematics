/**
 * @file   main_window.hpp
 * @Author ATetiukhin
 * @date   January, 2015
 * @brief  @ref MainWindow is control class.
 */

#ifndef MAIN_WINDOW_HPP_INCLUDE
#define MAIN_WINDOW_HPP_INCLUDE

#include <QMainWindow>

class QAction;
class QMenu;
class DatabaseHelper;
class Task;

class MainWindow
    : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow();

    virtual ~MainWindow();

    bool connection_from_commandline(const QStringList &args);

public slots:
    void exec              ();

    void disconnection     ();

    void select_task_dialog();

    void about             ();

    void pass              ();

private:
    void create_actions        ();

    void create_menus          ();

    void qsql_connection_dialog();

    void enabled_menu          ();

private:
    QVector<QMenu*> main_menu_;
    QVector<QAction*> main_action_;

    DatabaseHelper & data_base_helper_;
    Task * currentTask_;
};

#endif

/* End of 'main_window.hpp' file */