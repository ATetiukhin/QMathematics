/**
* @file   probability_widget.cpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Widget task probability.
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

void ProbabilityWidget::getEquationParameters(int &idSample, int &left, int &right, double &r) const
{
    idSample = nameSample->currentIndex();

    QString rText = inputLineEdit->text();
    if (rText.isEmpty()) {
        throw std::runtime_error("Error: r is empty");
    }
    r = rText.toDouble();

    QString yLeftText = LeftBox->text();
    QString yRightText = RightBox->text();
    left = yLeftText.toInt();
    right = yRightText.toInt();
    if (left > right) {
        throw std::runtime_error("Error: left < right");
    }
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