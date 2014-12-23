/**
 * @file   plot_dialog.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */

#include <functional>

#include <QColorDialog>

#include <qwt_plot.h>           // ui_
#include <qwt_plot_grid.h>      // QwtPlotGrid

#include <qwt_legend.h>

#include <qwt_plot_curve.h>     // QwtPlotCurve
#include <qwt_symbol.h>         // QwtSymbol

#include <qwt_plot_magnifier.h> // QwtPlotMagnifier

#include <qwt_plot_panner.h>    // QwtPlotPanner

#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>

#include <QtScript/QScriptEngine>

#include "plot_dialog.hpp"
#include "ui_plot_dialog.h"

PlotDialog::PlotDialog(QString const & str, QWidget *parent)
    : QDialog(parent)
    , ui_(new Ui::PlotDialogUI)
    , str_(str)
    , xLeft_(-10)
    , xRight_(10)
{
    ui_->setupUi(this);

    createPlot();
    createPlotGrid();

    createStyleCurve();
    makeCurve();
    associatePlot();

    enableMagnifier();
    enableMovingOnPlot();
    enablePicker();

    connect(ui_->plotClicked, SIGNAL(clicked()), this, SLOT(plotClicked()));
}

PlotDialog::~PlotDialog()
{
    delete ui_;
}

void PlotDialog::createPlot()
{
    QFont font("Sans Serif", 10);

    QwtText title("Plot");
    QwtText xAxis("X Axis");
    QwtText yAxis("Y Axis");

    title.setFont(font);
    xAxis.setFont(font);
    yAxis.setFont(font);

    // Title and background
    ui_->Qwt_Widget->setTitle(title);
    ui_->Qwt_Widget->setCanvasBackground(Qt::white);

    // Axis
    ui_->Qwt_Widget->setAxisTitle(QwtPlot::xBottom, xAxis);
    ui_->Qwt_Widget->setAxisScale(QwtPlot::xBottom, -10, 10, 0);
    ui_->Qwt_Widget->setAxisTitle(QwtPlot::yLeft, yAxis);
    ui_->Qwt_Widget->setAxisScale(QwtPlot::yLeft, -10, 10, 0);

    // Legend
    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode(QwtLegendData::Clickable);
    ui_->Qwt_Widget->insertLegend(legend, QwtPlot::RightLegend);
    connect(legend, SIGNAL(clicked(const QVariant &, int)), SLOT(changeColorClicked()));
}

void PlotDialog::createPlotGrid()
{
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(Qt::gray, 1)); // color and thickness
    grid->attach(ui_->Qwt_Widget);
}

void PlotDialog::createStyleCurve()
{
    curve_ = new QwtPlotCurve();
    curve_->setTitle("Color");
    curve_->setPen(Qt::blue, 2);
}

void PlotDialog::makeCurve()
{
    points_.clear();
    epsilont = (xRight_ - xLeft_) / 1e3;

    QScriptEngine engine;
    QScriptValue scriptFun;

    engine.evaluate(tr("function fun(x) { return ") + str_ + "; }");
    scriptFun = engine.globalObject().property("fun");

    if (engine.hasUncaughtException()) {
        throw std::runtime_error("Error: parsing error");
    }

    auto f = [&engine, &scriptFun](double x)->double {
        return scriptFun.call(QScriptValue(), QScriptValueList() << x).toNumber();
    };

    for (double i = xLeft_, step = epsilont; i <= xRight_; i += step) {
        QPointF point(i, f(i));
        points_ << point;
    }

    curve_->setSamples(points_);     // to associate a set of points with the curve
}

void PlotDialog::associatePlot()
{
    curve_->attach(ui_->Qwt_Widget); // to display the curve on the graph
    ui_->Qwt_Widget->replot();
}

void PlotDialog::enableMagnifier()
{
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(ui_->Qwt_Widget->canvas());
    magnifier->setMouseButton(Qt::MidButton); // key activating the approximation / distance
}

void PlotDialog::enableMovingOnPlot()
{
    QwtPlotPanner *d_panner = new QwtPlotPanner(ui_->Qwt_Widget->canvas());
    d_panner->setMouseButton(Qt::LeftButton); // moving on schedule
}

void PlotDialog::enablePicker()
{
    // function setting
    QwtPlotPicker *d_picker = new QwtPlotPicker(
        QwtPlot::xBottom, QwtPlot::yLeft, // association with the axes
        QwtPlotPicker::CrossRubberBand,   // the style of perpendicular lines
        QwtPicker::AlwaysOn,
        ui_->Qwt_Widget->canvas());       // association with the field

    d_picker->setRubberBandPen(QColor(Qt::red)); // The color of perpendicular lines
    d_picker->setTrackerPen(QColor(Qt::black));  // the color coordinates of the pointer position
    d_picker->setStateMachine(new QwtPickerDragPointMachine());
    d_picker->setMousePattern(QwtEventPattern::MouseSelect1, Qt::RightButton);
}

void PlotDialog::plotClicked()
{
    ui_->plotClicked->setEnabled(false);
    QString yLeftText = ui_->yLeftBox->text().replace(QLocale().decimalPoint(), QLatin1Char('.'));
    QString yRightText = ui_->yRightBox->text().replace(QLocale().decimalPoint(), QLatin1Char('.'));

    double yLeft = yLeftText.toDouble();
    double yRight = yRightText.toDouble();

    ui_->Qwt_Widget->setAxisScale(QwtPlot::yLeft, yLeft , yRight, 0);

    QString xLeftText = ui_->xLeftBox->text().replace(QLocale().decimalPoint(), QLatin1Char('.'));
    QString xRightText = ui_->xRightBox->text().replace(QLocale().decimalPoint(), QLatin1Char('.'));

    xLeft_ = xLeftText.toDouble();
    xRight_ = xRightText.toDouble();
    epsilont = (xRight_ - xLeft_) / 1e3;

    ui_->Qwt_Widget->setAxisScale(QwtPlot::xBottom, xLeft_, xRight_, 0);

    makeCurve();

    ui_->Qwt_Widget->replot();
    ui_->plotClicked->setEnabled(true);
}

void PlotDialog::changeColorClicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    curve_->setPen(color, 2);
    ui_->Qwt_Widget->replot();
}

void PlotDialog::mouseReleaseEvent(QMouseEvent * mouseEvent)
{
    QwtInterval xCoord = ui_->Qwt_Widget->axisInterval(QwtPlot::xBottom);
    xLeft_ = xCoord.minValue();
    xRight_ = xCoord.maxValue();
    makeCurve();
    ui_->Qwt_Widget->replot();
}

void PlotDialog::wheelEvent(QMouseEvent * mouseEvent)
{
    mouseReleaseEvent(mouseEvent);
}

/* End of 'plot_dialog.cpp' file */