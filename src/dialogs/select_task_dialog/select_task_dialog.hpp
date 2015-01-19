/**
* @file   qsql_connection_dialog.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Dialog box for selecting the type of tasks.
*/

#ifndef SELECT_TASK_DIALOG_HPP_INCLUDE
#define SELECT_TASK_DIALOG_HPP_INCLUDE

#include <QDialog>
#include "ui_select_task_dialog.h"

class SelectTaskDialog
    : public QDialog
    , private Ui::SelectTaskDialogUI
{
    Q_OBJECT
public:
    explicit SelectTaskDialog(QWidget * parent = 0);

    virtual ~SelectTaskDialog();

    int getNumberTask() const;

private slots:
    void handleSelectionChanged(int index);

    void okButtonClicked();

private:
    int numberTask_;
};

#endif /* End of 'select_task_dialog.hpp' file */