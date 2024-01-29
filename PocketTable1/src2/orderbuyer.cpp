#include "orderbuyer.h"
#include "ui_orderbuyer.h"
#include "model/product.h"
#include "model/productdb.h"

OrderBuyer::OrderBuyer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::OrderBuyer)
{
  ui->setupUi(this);

  connect(ui->back, SIGNAL(clicked()), this, SLOT(hide()));
  connect(ui->ok, SIGNAL(clicked()), this, SLOT(create_order()));
  connect(ui->remove, SIGNAL(clicked()), SLOT(remove_product()));
}

OrderBuyer::~OrderBuyer() { //стандарт конструктор
  delete ui;
}

void OrderBuyer::load(set<string> additional_products) { //загрузка новыйх данных в БД проданных товаров
  for (auto product : additional_products) {
    product_articles.insert(product);
  }

  ui->table->setRowCount(0);
  for (auto article : product_articles) {
    Product product;
    PRODUCT_DB.product_by_article(article, product);

    int index = ui->table->rowCount();
    ui->table->insertRow(index);

    ui->table->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(product.name)));
    ui->table->setItem(index, 1, new QTableWidgetItem(QString::fromStdString(product.article)));
    ui->table->setItem(index, 2, new QTableWidgetItem(QString::number(product.cost)));
    ui->table->setItem(index, 3, new QTableWidgetItem(QString::number(product.kind)));
    ui->table->setItem(index, 4, new QTableWidgetItem(QString::fromStdString(product.expiry_date)));
    ui->table->setItem(index, 5, new QTableWidgetItem(QString::fromStdString(product.receipt_date)));
  }
}

set<string> OrderBuyer::current_order() {
  return product_articles;
}

void OrderBuyer::create_order() {

  QString date_string = QDate::currentDate().toString(Qt::ISODate);
  date_string.truncate(10);
  date_string.replace("-", ".");

  vector<Product> products;

  for (auto article : product_articles) {
    Product product;
    PRODUCT_DB.product_by_article(article, product);

    products.push_back(product);
  }


  PRODUCT_DB.add_order(date_string.toStdString(),
                       products);

  hide();
}

void OrderBuyer::remove_product() {
  QList<QTableWidgetItem*> selectedItems = ui->table->selectedItems();
  set<int> selected_rows;

  for (auto item : selectedItems) {
    selected_rows.insert(item->row());
  }

  for (auto row : selected_rows) {
    auto article = ui->table->item(row, 1)->text().toStdString();
    product_articles.erase(article);
  }

  load(product_articles);
}
