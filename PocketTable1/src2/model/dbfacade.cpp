#include "dbfacade.h"

DBFacade::DBFacade(QString databasename, QObject *parent) : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE", databasename); //активизируем драйвер для типа БД
    m_db.setDatabaseName(databasename); //устанавливаем имя БД без пароля

    //пароль (QSqlDatabase::setPassword). Подключение к базе данных осуществляется вызовом метода QSqlDatabase::open.
    //После подключения, с базой возможно взаимодействовать посредством запросов. Передача запроса базе осуществляется методом exec класса QSqlQuery,

    if (false == m_db.open())
        throw OpenDBException(databasename.toLatin1());

    m_query = new QSqlQuery(m_db); //переменная для запросов данных из БД
    //m_model = new QSqlTableModel(m_db);
}

DBFacade::~DBFacade() { //конструктор зачистки запросов
    delete m_query;
}

QString DBFacade::qs(QString str) { //
    return "'" + str + "'";
}

QString DBFacade::qs(std::string str) { //
    return qs(QString::fromStdString(str));
}

void DBFacade::exec(QString str) { //
    if (false == m_query->exec(str))
        throw ExecException(str.toLatin1());
}
