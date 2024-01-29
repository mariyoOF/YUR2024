#ifndef CATALOG_H
#define CATALOG_H

#include <QMainWindow>
#include "model/user.h"
#include <set>
#include "orderbuyer.h"

namespace Ui {
class CatalogBuyer; //класс для работы с выбраными товарами в заказе (для покупателя)
}

class CatalogBuyer : public QMainWindow
{
  Q_OBJECT

public:
  explicit CatalogBuyer(QWidget *parent = 0);
  ~CatalogBuyer();

public slots:
  void on_login();
  void on_auth_ok(User::Role);

  void on_updated();
  void on_add();
  void on_order();

  private:
  Ui::CatalogBuyer *ui;

  OrderBuyer* order_buyer;
};

#endif // CATALOG_H
