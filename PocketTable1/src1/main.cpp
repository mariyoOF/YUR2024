#include "catalogbuyer.h"
#include "catalogmanager.h"
#include "users.h"
#include <QApplication>

#include "model/productdb.h"

#define Q_DECLARE_METATYPE(Product);

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  qRegisterMetaType<Product>();

  PRODUCT_DB.createTables();
  CURRENT_USER = "";

  CatalogBuyer w;
  w.show();

  Users u;
  u.show();

  return a.exec();
}
