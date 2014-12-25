/**
 * @file   probability_widget.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#include "probability_widget.hpp"
#include "ui_probability_widget.h"

ProbabilityWidget::ProbabilityWidget(QWidget *parent)
    :  QWidget(parent)
{
    setupUi(this);
}

ProbabilityWidget::~ProbabilityWidget()
{
}

void ProbabilityWidget::connectWidget(TypeTask * task)
{
    connect(answerButton, SIGNAL(clicked()), task, SLOT(answerButtonClicked()));
}

void ProbabilityWidget::getEquationParameters(int & idMethod) const
{
    idMethod = nameSample->currentIndex();
}

void ProbabilityWidget::updateComboBox(QStringList const & namesMethods)
{
    nameSample->addItems(namesMethods);
}

void ProbabilityWidget::updateResult(QString const & namesMethods)
{
    resultLineEdit->setText(namesMethods);
}

/* End of 'probability_widget.cpp' file */