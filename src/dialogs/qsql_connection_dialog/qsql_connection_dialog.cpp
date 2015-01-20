/**
* @file   qsql_connection_dialog.cpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Dialog box to connect to the database.
*/

#include <QSqlDatabase>
#include <QMessagebox>

#include "qsql_connection_dialog.hpp"

QSqlConnectionDialog::QSqlConnectionDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

	QStringList drivers = QSqlDatabase::drivers();
    /* remove compat names */
	drivers.removeAll("QMYSQL3");
    drivers.removeAll("QOCI8");
    drivers.removeAll("QODBC3");
    drivers.removeAll("QPSQL7");
    drivers.removeAll("QTDS7");

    comboDriver->addItems(drivers);
}

QSqlConnectionDialog::~QSqlConnectionDialog()
{
}

QString QSqlConnectionDialog::driverName() const
{
    return comboDriver->currentText();
}

QString QSqlConnectionDialog::databaseName() const
{
    return editDatabase->text();
}

QString QSqlConnectionDialog::userName() const
{
    return editUsername->text();
}

QString QSqlConnectionDialog::password() const
{
    return editPassword->text();
}

QString QSqlConnectionDialog::hostName() const
{
    return editHostname->text();
}

int QSqlConnectionDialog::port() const
{
    return portSpinBox->value();
}

void QSqlConnectionDialog::okButtonClicked()
{
    if (comboDriver->currentText().isEmpty()) {
        QMessageBox::information(this, tr("No database driver selected"), tr("Please select a database driver"));
        comboDriver->setFocus();
    } else {
        accept();
    }
}

void QSqlConnectionDialog::cancelButtonClicked()
{
    reject();
}

/* End of 'qsql_connaction_dialog.cpp' file */