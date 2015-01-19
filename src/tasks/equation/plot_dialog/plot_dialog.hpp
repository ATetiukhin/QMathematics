/**
* @file   plot_dialog.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Drawing graphs using the library Qwt.
*/

#ifndef PLOT_DIALOG_HPP_INCLUDE
#define PLOT_DIALOG_HPP_INCLUDE

#include <QDialog>

class QwtPlotCurve;
class QPolygonF;

namespace Ui
{
    class PlotDialogUI;
}

class PlotDialog
    : public QDialog
{
    Q_OBJECT

public:
    explicit PlotDialog(QString const & str, QWidget *parent = 0);

    virtual ~PlotDialog();

private Q_SLOTS:
    void plotClicked();

    void changeColorClicked();

private:
    Ui::PlotDialogUI *ui_;
    QString str_;
    QwtPlotCurve *curve_;
    QPolygonF points_;
    double xLeft_;
    double xRight_;
    double epsilont;

    void createPlot();

    void createPlotGrid();

    void createStyleCurve();

    void makeCurve();

    void associatePlot();

    void enableMagnifier();

    void enableMovingOnPlot();

    void enablePicker();

    void wheelEvent(QMouseEvent *mouseEvent);

    void mouseReleaseEvent(QMouseEvent *mouseEvent);
};

#endif

/* End of 'plot_dialog.hpp' file */