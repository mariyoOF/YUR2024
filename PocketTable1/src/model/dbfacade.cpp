#include "dbfacade.h"

DBFacade::DBFacade(QString databasename, QObject *parent) : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE", databasename);
    m_db.setDatabaseName(databasename);

    if (false == m_db.open())
        throw OpenDBException(databasename.toLatin1());

    m_query = new QSqlQuery(m_db);
}

DBFacade::~DBFacade() {
    delete m_query;
}

QString DBFacade::qs(QString str) {
    return "'" + str + "'";
}

QString DBFacade::qs(std::string str) {
    return qs(QString::fromStdString(str));
}

void DBFacade::exec(QString str) {
    if (false == m_query->exec(str))
        throw ExecException(str.toLatin1());
}
