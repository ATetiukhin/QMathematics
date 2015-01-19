/**
 * @file   type_task_equation.cpp
 * @Author ATetiukhin
 * @date   January, 2015
 * @brief  Implementation tasks equation.
 */

#include "type_task_equation.hpp" // you cannot change the position
#include "database_helper.hpp"
#include "equation_widget.hpp"

#include <QtScript/QScriptEngine>

#include <QPluginLoader>
#include "plugin_interface.hpp"

#include "plot_dialog.hpp"

TypeTaskEquation::TypeTaskEquation(EquationWidget * ui)
    : dataBase_(DatabaseHelper::getInstance())
    , ui_(*ui)
    , idMethod_(-1)
    , parametersValues_(3)
{
    QStringList namesMethods(dataBase_.getMethods(0));
    if (!namesMethods.isEmpty()) {
        ui_.updateComboBox(namesMethods);
    }
}

TypeTaskEquation::~TypeTaskEquation()
{
}

void TypeTaskEquation::solveButtonClicked()
{
    try {
        ui_.getEquationParameters(equation_, parametersValues_, idMethod_);
        QScriptEngine engine;
        QScriptValue scriptFun;

        engine.evaluate(tr("function fun(x) { return ") + equation_ + "; }");
        scriptFun = engine.globalObject().property("fun");

        if (engine.hasUncaughtException()) {
            throw std::runtime_error("Error: parsing error");
        }

        int idExpression = dataBase_.getExpressionId(equation_);
        double result = 0;
        bool isSuccesses = false;

        if (idExpression != -1) {
            isSuccesses = dataBase_.getAnswer(parametersValues_, result, idMethod_,  idExpression);
        }

        if (!isSuccesses) {
            PluginInterface * plugin = nullptr;
            ans_.clear();

            QPluginLoader loader(dataBase_.getPathToPlugin(0, idMethod_));
            QObject * pluginObject = loader.instance();

            if (pluginObject) {
                plugin = qobject_cast<PluginInterface *>(pluginObject);
            } else {
                throw std::runtime_error(loader.errorString().toUtf8().constData());
            }

            auto getEvaluateFunction = [&engine, &scriptFun](double x)->double {
                return scriptFun.call(QScriptValue(), QScriptValueList() << x).toNumber();
            };

            plugin->calculate(getEvaluateFunction, parametersValues_, ans_);
            result = ans_[0];
            dataBase_.setAnswer(parametersValues_, equation_, idMethod_, result);
        }

        ui_.updateResult(QString::number(result));

    } catch (std::exception const & e) {
        ui_.updateResult(e.what());
    }
}

void TypeTaskEquation::plotButtonClicked()
{
    try {
        ui_.getEquationParameters(equation_);

        PlotDialog dialog(equation_, &ui_);
        dialog.exec();

    } catch (std::exception const & e) {
        ui_.updateResult(e.what());
    }

}

/* End of 'type_task_equation.cpp' file */