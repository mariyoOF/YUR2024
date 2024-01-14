#ifndef ORDERBUYER_H
#define ORDERBUYER_H

#include <QWidget>
#include <set>
#include <string>
using namespace std;

namespace Ui {
class OrderBuyer;
}

class OrderBuyer : public QWidget
{
  Q_OBJECT

public:
  explicit OrderBuyer(QWidget *parent = nullptr);
  ~OrderBuyer();

  void load(set<string> product_articles);
  set<string> current_order();

public slots:
  void create_order();
  void remove_product();

private:
  Ui::OrderBuyer *ui;

  set<string> product_articles;
};

#endif // ORDERBUYER_H
