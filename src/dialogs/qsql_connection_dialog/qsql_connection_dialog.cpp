/**
 * @file   qsql_connection_dialog.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */

#include <QSqlDatabase> // QSqlDatabase
#include <QMessagebox>
#include "qsql_connection_dialog.hpp"

QSqlConnectionDialog::QSqlConnectionDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(dbCheckBox, SIGNAL(clicked()), this, SLOT(dbCheckBoxClicked()));

    QStringList drivers = QSqlDatabase::drivers();
    /* remove compat names */
    drivers.removeAll("QMYSQL3");
    drivers.removeAll("QOCI8");
    drivers.removeAll("QODBC3");
    drivers.removeAll("QPSQL7");
    drivers.removeAll("QTDS7");

    if (!drivers.contains("QSQLITE")) {
        dbCheckBox->setEnabled(false);
    }

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

bool QSqlConnectionDialog::useInMemoryDatabase() const
{
    return dbCheckBox->isChecked();
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

void QSqlConnectionDialog::dbCheckBoxClicked()
{
    connGroupBox->setEnabled(!dbCheckBox->isChecked());
}

/* End of 'qsql_connaction_dialog.cpp' file */