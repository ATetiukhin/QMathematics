/**
 * @file   type_task_probability.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#include "type_task_probability.hpp" // you cannot change the position
#include "database_helper.hpp"
#include "probability_widget.hpp"

#include <QPluginLoader>
#include "plugin_interface.hpp"

#include "plot_dialog.hpp"

TypeTaskProbability::TypeTaskProbability(ProbabilityWidget * ui)
    : dataBase_(DatabaseHelper::getInstance())
    , ui_(*ui)
{
    QStringList namesMethods(dataBase_.getMethods(1));
    if (!namesMethods.isEmpty()) {
        ui_.updateComboBox(namesMethods);
    }
}

TypeTaskProbability::~TypeTaskProbability()
{
}

void TypeTaskProbability::answerButtonClicked()
{
    try {
        int idMethod = 0;
        ui_.getEquationParameters(idMethod);

        QPluginLoader loader(dataBase_.getPathToPlugin(1, idMethod));
        QObject * pluginObject = loader.instance();

        PluginInterface * plugin = nullptr;
        if (pluginObject) {
            plugin = qobject_cast<PluginInterface *>(pluginObject);
        } else {
            throw std::runtime_error(loader.errorString().toUtf8().constData());
        }

    } catch (std::exception const & e) {
        ui_.updateResult(e.what());
    }
}


/* End of 'type_task_equation.cpp' file */