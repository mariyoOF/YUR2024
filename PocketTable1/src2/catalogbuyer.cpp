#include "catalogbuyer.h"
#include "ui_catalogbuyer.h"
#include "authwidget.h"
#include "catalogmanager.h"
#include "model/productdb.h"

CatalogBuyer::CatalogBuyer(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::CatalogBuyer) {
  ui->setupUi(this);

  connect(ui->login, SIGNAL(clicked()), this, SLOT(on_login()));
  connect(ui->buy, SIGNAL(clicked()), this, SLOT(on_order()));
  connect(ui->add, SIGNAL(clicked()), this, SLOT(on_add()));

  on_updated();

  connect(&PRODUCT_DB, SIGNAL(updated()), SLOT(on_updated()));

  order_buyer = new OrderBuyer(nullptr);
  order_buyer->hide();
}

CatalogBuyer::~CatalogBuyer() {
  delete ui;
}

void CatalogBuyer::on_login() { //кнопка "Войти"
  AuthWidget* auth = new AuthWidget(nullptr);
  connect(auth, SIGNAL(auth_ok(User::Role)), SLOT(on_auth_ok(User::Role)));

  auth->show();
}

void CatalogBuyer::on_auth_ok(User::Role role) { //функция проверки на "Администратора"
  this->hide();
  CatalogManager *catalog = new CatalogManager(role, nullptr);
  catalog->show();
}

void CatalogBuyer::on_updated() { //функция для работы с товарам в таблице
  vector<Product> products = PRODUCT_DB.products();

  ui->table->setRowCount(0);
  for (auto product : products) {
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

void CatalogBuyer::on_add() {
  QList<QTableWidgetItem*> selectedItems = ui->table->selectedItems();
  set<int> selected_rows;

  auto product_articles = order_buyer->current_order();

  for (auto item : selectedItems) {
    selected_rows.insert(item->row());
  }

  for (auto row : selected_rows) {
    auto article = ui->table->item(row, 1)->text().toStdString();
    product_articles.insert(article);
  }

  order_buyer->load(product_articles);
}

void CatalogBuyer::on_order() {
  order_buyer->show();
}
