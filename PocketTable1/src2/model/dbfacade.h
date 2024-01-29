#ifndef DBFACADE_H
#define DBFACADE_H

#include <QObject>
#include <QtSql/QtSql> //подключаем библеотекеу QtSQL
#include <exception>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>

//class QSqlTableModel;

class DBFacade : public QObject { //класс Фасад для работы с интерфейсом+БД
    Q_OBJECT
public:
    explicit DBFacade(QString databasename,
                      QObject *parent = 0);
    ~DBFacade();
signals:
    void updated();
protected:
    void exec(QString);
    QString qs(QString);
    QString qs(std::string);
                //!< quote string

    QSqlDatabase m_db; //генератор БД
    QSqlQuery *m_query; //запросник данных БД
    //QSqlTableModel m_model;
};

class OpenDBException: public std::exception {
public:
    OpenDBException(const char* dbName) : m_dbname(dbName) {}
private:
    virtual const char* what() const throw() {
        return m_dbname;
    }
    const char* m_dbname;
};

class ExecException: public std::exception {
public:
    ExecException(const char* request) : m_request(request) {}
private:
    virtual const char* what() const throw() {
        return m_request;
    }
    const char* m_request;
};

#endif // DBFACADE_H
