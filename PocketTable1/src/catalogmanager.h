#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <QWidget>
#include "model/user.h"
#include "users.h"
#include "addproduct.h"
#include "ordermanagement.h"
#include "salesreport.h"

namespace Ui {
class CatalogManager;
}

class CatalogManager : public QWidget {
  Q_OBJECT

public:
  CatalogManager(User::Role role, QWidget *parent = nullptr);
  ~CatalogManager();

public slots:
  void on_user_management();
  void on_report();
  void on_product_remove();
  void on_product_add();
  void on_order_management();

  void on_product_added(Product product);

  void on_updated();

private:
  Ui::CatalogManager *ui;
  Users* users;
  AddProduct* add_product;
  OrderManagement* order_management;
  SalesReport *report;
};

#endif // CATALOGMANAGER_H
