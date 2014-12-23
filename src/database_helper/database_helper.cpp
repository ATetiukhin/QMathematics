/**
 * @file   database_helper.cpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */

#include <stdexcept>
#include <QtSql>

#include "database_helper.hpp"

DatabaseHelper * DatabaseHelper::pInstance_ = nullptr;
DatabaseHelperDestroyer DatabaseHelper::destroyer_;
QSqlDatabase DatabaseHelper::db_;

DatabaseHelperDestroyer::~DatabaseHelperDestroyer()
{
    delete pInstance_;
}

void DatabaseHelperDestroyer::initialize(DatabaseHelper *p)
{
    pInstance_ = p;
}

DatabaseHelper::DatabaseHelper()
{
}

DatabaseHelper::~DatabaseHelper()
{
}

DatabaseHelper &DatabaseHelper::getInstance()
{
    if (!pInstance_) {
        pInstance_ = new DatabaseHelper();
        destroyer_.initialize(pInstance_);
    }

    return *pInstance_;
}

void DatabaseHelper::connection(const QString &driver, const QString &dbName, const QString &host,
                                     const QString &user, const QString &passwd, int port)
{
    static int cCount = 0;

    db_ = QSqlDatabase::addDatabase(driver);
    db_.setDatabaseName(dbName);
    db_.setHostName(host);
    db_.setPort(port);

    QSqlError error;
    if (!db_.open(user, passwd)) {
        error = db_.lastError();
        db_ = QSqlDatabase();
        QSqlDatabase::removeDatabase(dbName);
    }

    if (error.type() != QSqlError::NoError) {
        throw std::runtime_error(error.text().toUtf8().constData());
    }
}

void DatabaseHelper::disconnection()
{
    db_.close();
    db_.removeDatabase(db_.connectionName());
}

bool DatabaseHelper::isOpen()
{
    return db_.isOpen();
}

QStringList DatabaseHelper::getTasks()
{
    QStringList result;
    QSqlQuery q("", db_);
    q.exec("SELECT name_task FROM type_task");
    int field = q.record().indexOf("name_task");

    while (q.next()) {
        result.append(q.value(field).toString());
    }

    return result;
}

QStringList DatabaseHelper::getMethods()
{
    QStringList result;
    QSqlQuery q("", db_);
    q.exec("SELECT method_name FROM methods WHERE type_task = 0");
    int field = q.record().indexOf("method_name");

    while (q.next()) {
        result.append(q.value(field).toString());
    }

    return result;
}

int DatabaseHelper::getExpressionId(QString const & equation)
{
    QSqlQuery q("", db_);
    q.prepare("SELECT id_expression FROM expressions WHERE expression = :s AND type_task = :id");
    q.bindValue(":s", equation);
    q.bindValue(":type_task", 0); //equation in r1
    q.exec();

    if (!q.first()) {
        return -1;
    }

    return q.value(0).toInt();
}

bool DatabaseHelper::getAnswer(QVector <double> const & parametersValues, double & result, int idMethod, int idExpression)
{
    int check = 0;
    QSqlQuery q("", db_);
    q.prepare("SELECT id_session FROM parameters_values WHERE method = :id_1 AND expression = :id_2");
    q.bindValue(":id_1", idMethod);
    q.bindValue(":id_2", idExpression);
    q.exec();
    while (q.next())
    {
        int id_s;
        id_s = q.value(0).toInt();
        QSqlQuery p("", db_);
        for (int i = 0; i < parametersValues.size(); i++)
        {
            p.prepare("SELECT value FROM parameters_values WHERE method = :id_1 AND id_session = :id_2 AND expression = :id_3 AND parameter = :id_4 AND value = :value");
            p.bindValue(":id_1", idMethod);
            p.bindValue(":id_2", id_s);
            p.bindValue(":id_3", idExpression);
            p.bindValue(":id_4", i);
            p.bindValue(":value", parametersValues[i]);
            p.exec();
            if (!p.first())
            {
                check = 1;
                break;
            }
        }
        if (check == 1)
        {
            check = 0;
            continue;
        }
        p.prepare("SELECT answer FROM result WHERE method = :id_1 AND session = :id_2 AND number_component = :id_3");
        p.bindValue(":id_1", idMethod);
        p.bindValue(":id_2", id_s);
        p.bindValue(":id_3", 1);
        p.exec();
        if (p.first()) {
            result = p.value(0).toDouble();
            return true;
        }
    }

    return false;
}

QString DatabaseHelper::getPathToPlugin(int idMethod)
{
    QSqlQuery q("", db_);
    q.prepare("SELECT path_to_method FROM methods WHERE type_task = 0 AND id_method = :id_1");
    q.bindValue(":id_1", idMethod);
    q.exec();
    int field = q.record().indexOf("path_to_method");

    QString path;
    while (q.next()) {
        path.append(q.value(field).toString());
    }

    return path;
}

void DatabaseHelper::setAnswer(QVector<double> const & parametersValues, QString const & expression, int idMethod, double result)
{
    QSqlQuery q("", db_);
    int id_ex, id_s;

    id_ex = getExpressionId(expression);
    if (id_ex == -1)
    {
        q.prepare("INSERT INTO expressions (type_task, expression) VALUES (0, :s)");
        q.bindValue(":s", expression);
        q.exec();
        id_ex = getExpressionId(expression);
    }

    QSqlQuery p("", db_);
    p.prepare("INSERT INTO parameters_values (method, expression, parameter, value) VALUES (:id_1, :id_2, 0, :v)");
    p.bindValue(":id_1", idMethod);
    p.bindValue(":id_2", id_ex);
    p.bindValue(":v", parametersValues[0]);
    p.exec();
    q.prepare("SELECT id_session FROM parameters_values WHERE method = :id_1 AND expression = :id_2 AND parameter = 0 AND value = :v ORDER BY id_session DESC");
    q.bindValue(":id_1", idMethod);
    q.bindValue(":id_2", id_ex);
    q.bindValue(":v", parametersValues[0]);
    q.exec();

    if (q.first())
        id_s = q.value(0).toInt();

    for (int i = 1; i < parametersValues.size(); i++)
    {
        p.prepare("INSERT INTO parameters_values (id_session, method, expression, parameter, value) VALUES (:id_1, :id_2, :id_3, :id_4, :v)");
        p.bindValue(":id_1", id_s);
        p.bindValue(":id_2", idMethod);
        p.bindValue(":id_3", id_ex);
        p.bindValue(":id_4", i);
        p.bindValue(":v", parametersValues[i]);
        p.exec();
    }

    p.prepare("INSERT INTO result (number_component, session, method, answer) VALUES (1, :id_1, :id_2, :id_3)");
    p.bindValue(":id_1", id_s);
    p.bindValue(":id_2", idMethod);
    p.bindValue(":id_3", result);
    p.exec();
}

/* End of 'database_helper.cpp' file */