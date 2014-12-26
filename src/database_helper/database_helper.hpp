/**
 * @file   database_helper.hpp
 * @Author https://github.com/ATetiukhin
 * @date   December, 2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */
#ifndef DATABASE_HELPER_HPP_INCLUDE
#define DATABASE_HELPER_HPP_INCLUDE

class QSqlDatabase;
class DatabaseHelper;

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

    static void connection(const QString &driver, const QString &dbName,
                           const QString &host, const QString &user,
                           const QString &passwd, int port = -1);

    static void disconnection();

    static bool isOpen();

    static QStringList getTasks();

    static QStringList getMethods(int type_task);

    static int getExpressionId(QString const & equation);

    static bool getAnswer(QVector <double> const & parametersValues, double & result, int idMethod, int idExpression);

    static QString getPathToPlugin(int idTypeTask, int idMethod);

    static void setAnswer(QVector<double> const & parametersValues, QString const & expression, int idMethod, double result);

    static QStringList getNameSample();

    static void sample(QVector<double> & sample, int idMethod, int left, int right);

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