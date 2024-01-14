#ifndef DBFACADE_H
#define DBFACADE_H

#include <QObject>
#include <QtSql/QtSql>
#include <exception>

class DBFacade : public QObject {
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

    QSqlDatabase m_db;
    QSqlQuery *m_query;
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
