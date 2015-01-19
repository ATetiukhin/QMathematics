/**
* @file   database_helper.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  @ref DatabaseHelper is class for working with database.
*
* @ref DatabaseHelper is implemented with the use of the singleton pattern.
* @ref DatabaseHelperDestroyer is helper class for destruction @ref DatabaseHelper.
*/

#ifndef DATABASE_HELPER_HPP_INCLUDE
#define DATABASE_HELPER_HPP_INCLUDE

QT_BEGIN_NAMESPACE
class QSqlDatabase;
class DatabaseHelper;
QT_END_NAMESPACE

class DatabaseHelperDestroyer
{
public:
    ~DatabaseHelperDestroyer();

    void initialize(DatabaseHelper * p);

private:
    DatabaseHelper *pInstance_;
};


class DatabaseHelper
{
public:
    static DatabaseHelper &getInstance();

    void connection(const QString &driver, const QString &dbName,
                    const QString &host, const QString &user,
                    const QString &passwd, int port = -1);

    bool isOpen();

    QStringList getTasks();

    QStringList getMethods(int type_task);

    int getExpressionId(QString const & equation);

    bool getAnswer(QVector <double> const & parametersValues, double & result, int idMethod, int idExpression);

    QString getPathToPlugin(int idTypeTask, int idMethod);

    void setAnswer(QVector<double> const & parametersValues, QString const & expression, int idMethod, double result);

    QStringList getNameSample();

    void sample(QVector<double> & sample, int idMethod, int left, int right);

private:
    static QSqlDatabase db_;
    static DatabaseHelper * pInstance_;
    static DatabaseHelperDestroyer destroyer_;

    DatabaseHelper();

    DatabaseHelper(const DatabaseHelper &other);

    DatabaseHelper &operator=(DatabaseHelper &other);

    ~DatabaseHelper();

    friend class DatabaseHelperDestroyer;
};

#endif

/* End of 'database_helper.hpp' file */