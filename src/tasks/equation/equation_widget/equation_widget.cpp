/**
 * @file   equation_widget.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#include "equation_widget.hpp"
#include "ui_equation_widget.h"

#include "plot_dialog.hpp"

EquationWidget::EquationWidget(QWidget *parent)
    :  QWidget(parent)
{
    setupUi(this);
}

EquationWidget::~EquationWidget()
{
}

void EquationWidget::connectEquationWidget(TypeTask * task)
{
    connect(solve, SIGNAL(clicked()), task, SLOT(solveButtonClicked()));
    connect(plot, SIGNAL(clicked()), task, SLOT(plotButtonClicked()));
    connect(clear, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
}

void EquationWidget::updateComboBox(QStringList const & namesMethods)
{
    methods->addItems(namesMethods);
}

void EquationWidget::getEquationParameters(QString & equation) const
{
    equation = functionLineEdit->text();
    if (equation.isEmpty()) {
        throw std::runtime_error("Error: equation is empty");
    }
}

void EquationWidget::getEquationParameters(QString & equation, QVector<double> & parametersValues, int & idMethod) const
{
    getEquationParameters(equation);

    bool isSuccesses = false;

    parametersValues[0] = startLineEdit->displayText().toDouble(&isSuccesses);
    if (!isSuccesses) {
        throw std::runtime_error("Error: input start point");
    }

    parametersValues[1] = endLineEdit->displayText().toDouble(&isSuccesses);
    if (!isSuccesses) {
        throw std::runtime_error("Error: input end point");
    }

    parametersValues[2] = epsilonLineEdit->displayText().toDouble(&isSuccesses);
    if (!isSuccesses) {
        throw std::runtime_error("Error: input epsilon");
    }

    idMethod = methods->currentIndex();
}

void EquationWidget::updateResult(QString const & namesMethods)
{
    resultLineEdit->setText(namesMethods);
}

void EquationWidget::clearButtonClicked()
{
    functionLineEdit->clear();
    functionLineEdit->setFocus();

    startLineEdit->clear();
    startLineEdit->setFocus();

    endLineEdit->clear();
    endLineEdit->setFocus();

    epsilonLineEdit->clear();
    epsilonLineEdit->setFocus();

    resultLineEdit->clear();
    resultLineEdit->setFocus();
}

/* End of 'equation_widget.cpp' file */