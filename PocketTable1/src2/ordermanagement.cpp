#include "ordermanagement.h"
#include "ui_ordermanagement.h"
#include "model/productdb.h"
#include <sstream>

OrderManagement::OrderManagement(QWidget *parent) : //класс заказ.менеджер
  QWidget(parent),
  ui(new Ui::OrderManagement)
{
  ui->setupUi(this);

  connect(ui->back, SIGNAL(clicked()), this, SLOT(hide()));
  connect(ui->sell, SIGNAL(clicked()), this, SLOT(on_sell()));
  connect(ui->remove, SIGNAL(clicked()), this, SLOT(on_remove()));

  on_load();
}

OrderManagement::~OrderManagement() //стандарт конструктор
{
  delete ui;
}

void OrderManagement::on_load() { //
  vector<Order> orders = PRODUCT_DB.orders();

  ui->table->setRowCount(0);
  for (auto order : orders) {
    int index = ui->table->rowCount();
    ui->table->insertRow(index);

    ui->table->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(order.date))); //выцепляем дату заказа

    stringstream sstr; //работаем в id заказа
    for (auto id : order.product_ids) {
      sstr << id << "  ";
    }
    string ids_str;
    getline(sstr, ids_str);

    ui->table->setItem(index, 1, new QTableWidgetItem(QString::fromStdString(ids_str)));
  }
}

vector<Order> OrderManagement::selected_orders() { //функция для обращений к БД
  QList<QTableWidgetItem*> selectedItems = ui->table->selectedItems();
  set<int> selected_rows; //выбираем строку
  vector<Order> orders;   //с нужным заказом

  for (auto item : selectedItems) {
    selected_rows.insert(item->row());
  }

  for (auto row : selected_rows) {
    auto date = ui->table->item(row, 0)->text().toStdString();

    auto it_order = find_if(orders.begin(), orders.end(), [=](Order order){ //при выполнении оформления и проверки заказа
        return order.date == date; //возвращаем его дату
    });

    if (it_order == orders.end()) { //завершаем оформление заказа
      Order order;
      order.date = date;
      orders.push_back(order);
    }
  }
  return orders;
}

void OrderManagement::on_remove() { //удаляем заказ из основной БД
  vector<Order> orders = selected_orders();

  for (auto order : orders) {
    PRODUCT_DB.remove_order(order.date);
  }
  on_load();
}

void OrderManagement::on_sell() { //добавляем в "совершенные" заказы
  vector<Order> orders = selected_orders();

  for (auto order : orders) {
    PRODUCT_DB.sell_order(order.date);
  }
  on_load();
}
