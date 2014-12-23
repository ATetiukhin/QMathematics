/**
 * @file   select_task_dialog.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#include "select_task_dialog.hpp"
#include "database_helper.hpp"

SelectTaskDialog::SelectTaskDialog(QWidget * parent)
    : QDialog(parent)
    , numberTask_(-1)
{
    setupUi(this);

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSelectionChanged(int)));
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));

    DatabaseHelper & dataBase = DatabaseHelper::getInstance();
    comboBox->addItems(dataBase.getTasks());
    label->setText(comboBox->currentText());
}

SelectTaskDialog::~SelectTaskDialog()
{
}

int SelectTaskDialog::getNumberTask() const
{
    return numberTask_;
}

void SelectTaskDialog::okButtonClicked()
{
    accept();
}

void SelectTaskDialog::handleSelectionChanged(int index)
{
    numberTask_ = index;
    label->setText(comboBox->currentText());
};

/* End of 'select_task_dialog.cpp' file */