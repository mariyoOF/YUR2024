#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QWidget>
#include "model/product.h"

namespace Ui {
class AddProduct;
}

class AddProduct : public QWidget
{
  Q_OBJECT

public:
  explicit AddProduct(QWidget *parent = nullptr);
  ~AddProduct();

signals:
  void product(Product product);
public slots:
  void on_add();

private:
  Ui::AddProduct *ui;
};

#endif // ADDPRODUCT_H
