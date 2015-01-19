/**
* @file   qsql_connection_dialog.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Dialog box to connect to the database.
*/

#ifndef QSQL_CONNECTION_DIALOG_HPP_INCLUDE
#define QSQL_CONNECTION_DIALOG_HPP_INCLUDE

#include <QDialog>
#include "ui_qsql_connection_dialog.h"

class QSqlConnectionDialog
    : public QDialog
    , private Ui::QSqlConnectionDialogUi
{
    Q_OBJECT
public:
    explicit QSqlConnectionDialog(QWidget *parent = 0);
    virtual ~QSqlConnectionDialog();

    QString driverName  () const;
    QString databaseName() const;
    QString userName    () const;
    QString password    () const;
    QString hostName    () const;
    int     port        () const;

private slots:
    void okButtonClicked     ();
    void cancelButtonClicked ();
};

#endif /* End of 'qsql_connaction_dialog.hpp' file */