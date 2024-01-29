#include "productdb.h"
#include <QMap>

ProductDB::ProductDB(QString dbFIlename, QObject *parent)
    : DBFacade(dbFIlename, parent) {
}

void ProductDB::createTables() {
    if (false == m_db.tables().contains("users")) {
      exec("CREATE TABLE users"
           "("
              "login TEXT PRIMARY KEY, "
              "password TEXT NOT NULL, "
              "role TEXT"
           ");"
      );
    }

    if (false == m_db.tables().contains("products")) {
      exec("CREATE TABLE products"
           "("
              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
              "name TEXT NUT NULL, "
              "article TEXT NUT NULL, "
              "cost INTEGER NUT NULL, "
              "kind INTEGER NUT NULL, "
              "expiry_date TEXT NOT NULL, "
              "receipt_date TEXT NOT NULL "
          ");"
      );
    }

    if (false == m_db.tables().contains("solt_products")) {
      exec("CREATE TABLE solt_products"
           "("
              "id INTEGER PRIMARY KEY, "
              "name TEXT NUT NULL, "
              "article TEXT NUT NULL, "
              "cost INTEGER NUT NULL, "
              "kind INTEGER NUT NULL, "
              "expiry_date TEXT NOT NULL, "
              "receipt_date TEXT NOT NULL, "
              "realization_date TEXT NOT NULL"
          ");"
      );
    }

    if (false == m_db.tables().contains("products_order")) {
      exec("CREATE TABLE products_order"
           "("
              "id_product INTEGER NOT NULL,"
              "date TEXT NOT NULL"
          ");"
      );
    }
}

bool ProductDB::is_login_busy(QString login) {
  QString query = tr("SELECT login FROM users WHERE login = ") + qs(login);
  exec(query);

  return m_query->first();
}

void ProductDB::add_user(User user) {
  QString query = tr("INSERT INTO users(login, password, role) VALUES (")
                        + qs(QString::fromStdString(user.login)) + ","
                        + qs(QString::fromStdString(user.password)) + ","
                        + qs(QString::fromStdString(user.role_to_string(user.role))) + ")";
  exec(query);
  emit updated();
}

vector<User> ProductDB::users() {
  vector<User> users;

  QString query = tr("SELECT login, password, role FROM users ");
  exec(query);

  while (true == m_query->next()) {
    QString login = m_query->value(0).toString();
    QString password = m_query->value(1).toString();
    QString role = m_query->value(2).toString();

    users.push_back(User(login.toStdString(),
                         password.toStdString(),
                         User::string_to_role(role.toStdString())));
  }
  return users;
}

User ProductDB::get_user(QString login) {
  QString query = tr("SELECT password, role FROM users WHERE login = ") + qs(login);
  exec(query);

  if (false == m_query->next()) {
    throw string("wrong login");
  }

  QString password = m_query->value(0).toString();
  QString role = m_query->value(1).toString();

  return User(login.toStdString(), password.toStdString(), User::string_to_role(role.toStdString()));
}

void ProductDB::remove_user(string login) {
  QString query = tr("DELETE FROM users WHERE login = ") + qs(login);
  exec(query);
  emit updated();
}

void ProductDB::add_product(Product product) {
  QString query = tr("INSERT INTO products(name, article, cost, kind, expiry_date, receipt_date) VALUES (")
                        + qs(product.name) + ","
                        + qs(product.article) + ","
                        + QString::number(product.cost) + ","
                        + QString::number(product.kind) + ","
                        + qs(product.expiry_date) + ","
                        + qs(product.receipt_date) + ")";
  exec(query);
  emit updated();
}

vector<Product> ProductDB::products() {
  vector<Product> products;

  QString query = tr("SELECT id, name, article, cost, kind, expiry_date, receipt_date FROM products ");
  exec(query);

  while (true == m_query->next()) {
    Product data;
    data.id = m_query->value(0).toInt();
    data.name = m_query->value(1).toString().toStdString();
    data.article = m_query->value(2).toString().toStdString();
    data.cost = m_query->value(3).toInt();
    data.kind = m_query->value(4).toInt();
    data.expiry_date = m_query->value(5).toString().toStdString();
    data.receipt_date = m_query->value(6).toString().toStdString();

    products.push_back(data);
  }
  return products;
}

bool ProductDB::product_by_article(string article, Product& product) {
  QString query = tr("SELECT name, article, cost, kind, expiry_date, receipt_date, id "
                     "FROM products WHERE article = ") + qs(article);
  exec(query);

  if (false == m_query->next()) {
    return false;
  }

  product.name = m_query->value(0).toString().toStdString();
  product.article = m_query->value(1).toString().toStdString();
  product.cost = m_query->value(2).toInt();
  product.kind = m_query->value(3).toInt();
  product.expiry_date = m_query->value(4).toString().toStdString();
  product.receipt_date = m_query->value(5).toString().toStdString();
  product.id = m_query->value(6).toInt();

  return true;
}

bool ProductDB::product_by_id(int id, Product& product) {
  QString query = tr("SELECT name, article, cost, kind, expiry_date, receipt_date, id "
                     "FROM products WHERE id = ") + QString::number(id);
  exec(query);

  if (false == m_query->next()) {
    return false;
  }

  product.name = m_query->value(0).toString().toStdString();
  product.article = m_query->value(1).toString().toStdString();
  product.cost = m_query->value(2).toInt();
  product.kind = m_query->value(3).toInt();
  product.expiry_date = m_query->value(4).toString().toStdString();
  product.receipt_date = m_query->value(5).toString().toStdString();
  product.id = m_query->value(6).toInt();

  return true;
}

void ProductDB::remove_product(string article) {
  QString query = tr("DELETE FROM products WHERE article = ") + qs(article);
  exec(query);
  emit updated();
}

void ProductDB::add_order(string date, vector<Product> products) {
  for (auto product : products) {
    QString query = tr("INSERT INTO products_order(date, id_product) VALUES (")
                          + qs(date) + ","
                          + QString::number(product.id) + ")";
    exec(query);
  }
}

vector<Order> ProductDB::orders() {
  vector<Order> orders;

  QString query = tr("SELECT date, id_product FROM products_order ");
  exec(query);

  while (true == m_query->next()) {
    string date = m_query->value(0).toString().toStdString();
    int id = m_query->value(1).toInt();

    auto it_order = find_if(orders.begin(), orders.end(), [=](Order order){
        return order.date == date;
    });

    if (it_order != orders.end()) {
      (*it_order).product_ids.push_back(id);
    }
    else {
      Order order;
      order.date = date;
      order.product_ids.push_back(id);
      orders.push_back(order);
    }

  }
  return orders;
}

void ProductDB::remove_order(string date) {
  QString query = tr("DELETE FROM products_order WHERE ") +
                     " date = " + qs(date);
  exec(query);
  emit updated();
}

void ProductDB::sell_order(string date) {
  QString date_string = QDate::currentDate().toString(Qt::ISODate);
  date_string.truncate(10);
  date_string.replace("-", ".");

  QString query = tr("SELECT id_product FROM products_order WHERE ") +
                     " date = " + qs(date);
  exec(query);

  vector<int> sold_ids;

  while (true == m_query->next()) {
    int id = m_query->value(0).toInt();
    sold_ids.push_back(id);
  }

  for (auto id : sold_ids) {
    Product product;
    product_by_id(id, product);

    query = tr("INSERT INTO solt_products")
         + tr(" (id, name, article, cost, kind, expiry_date, receipt_date, realization_date)")
         + tr(" VALUES (")
         + QString::number(product.id) + ","
         + qs(product.name) + ","
         + qs(product.article) + ","
         + QString::number(product.cost) + ","
         + QString::number(product.kind) + ","
         + qs(product.expiry_date) + ","
         + qs(product.receipt_date) + ","
         + qs(date_string) + ")";
    exec(query);

    QString query = tr("DELETE FROM products WHERE id = ") + QString::number(id);
    exec(query);
  }

  remove_order(date);
  emit updated();
}

int ProductDB::count(QString from, QString to) {
    exec(
          tr("SELECT COUNT(*) FROM solt_products WHERE ") +
          tr("realization_date >= ") + qs(from) +
          tr(" AND realization_date <= ") + qs(to)
    );
    m_query->next();

    return m_query->value(0).toInt();
}

int ProductDB::sum(QString from, QString to) {
    exec(
          tr("SELECT SUM(cost) FROM solt_products WHERE ") +
          tr("realization_date >= ") + qs(from) +
          tr(" AND realization_date <= ") + qs(to)
    );
    m_query->next();

    return m_query->value(0).toInt();
}
