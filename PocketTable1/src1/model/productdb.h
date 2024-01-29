#ifndef PRODUCTDB_H
#define PRODUCTDB_H

#include "dbfacade.h"
#include "singleton.h"

#include <QObject>
#include <QList>

#include "order.h"
#include "product.h"
#include "soltproduct.h"
#include "user.h"
#include <set> //

class ProductDB : public DBFacade { //класс для работы со всей БД (интерфейс)
    Q_OBJECT
public:
    explicit ProductDB(QString dbFIlename = "products.sqlite",
                     QObject *parent = 0);

    bool is_login_busy(QString login); //переменная для логина
    void add_user(User user); //функция добавления пользователя
    vector<User> users(); //
    void remove_user(string login); //функция обновления БД пользователей
    User get_user(QString login); // класс для пользователям

    vector<Product> products(); //
    void add_product(Product product); //функция добавления товара
    bool product_by_article(string article, Product &product); //функция для с артиклем товара
    bool product_by_id(int id, Product &product); //функция для id товара
    void remove_product(string article); //функция обновления наличия товаров

    void add_order(string date, vector<Product> products); //функция добавления заказа
    vector<Order> orders(); //
    void remove_order(string date); //функция обновления информации о заказе
    void sell_order(string date); //функция отмены заказа

    int count(QString from, QString to); //функция для кол-ва
    int sum(QString from, QString to); //функция для суммы заказа

    void createTables(); //функция для генерирования таблиц
public slots:
};

#define PRODUCT_DB Singleton<ProductDB>::instance() //

#endif // PRODUCTDB_H
