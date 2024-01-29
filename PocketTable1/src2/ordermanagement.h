#ifndef ORDERMANAGEMENT_H
#define ORDERMANAGEMENT_H

#include <QWidget>
#include <vector>
#include "model/order.h"

using namespace std;

namespace Ui {
class OrderManagement;
}

class OrderManagement : public QWidget
{
  Q_OBJECT

public:
  explicit OrderManagement(QWidget *parent = nullptr);
  ~OrderManagement();

public slots:
  void on_load();
  void on_remove();
  void on_sell();

  vector<Order> selected_orders();

private:
  Ui::OrderManagement *ui;
};

#endif // ORDERMANAGEMENT_H
