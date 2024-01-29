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
#include <set>

class ProductDB : public DBFacade {
    Q_OBJECT
public:
    explicit ProductDB(QString dbFIlename = "products.sqlite",
                     QObject *parent = 0);

    bool is_login_busy(QString login);
    void add_user(User user);
    vector<User> users();
    void remove_user(string login);
    User get_user(QString login);

    vector<Product> products();
    void add_product(Product product);
    bool product_by_article(string article, Product &product);
    bool product_by_id(int id, Product &product);
    void remove_product(string article);

    void add_order(string date, vector<Product> products);
    vector<Order> orders();
    void remove_order(string date);
    void sell_order(string date);

    int count(QString from, QString to);
    int sum(QString from, QString to);

    void createTables();
public slots:
};

#define PRODUCT_DB Singleton<ProductDB>::instance()

#endif // PRODUCTDB_H
