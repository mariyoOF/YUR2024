#include "catalogmanager.h"
#include "ui_catalogmanager.h"
#include "model/productdb.h"
#include <set>

CatalogManager::CatalogManager(User::Role role, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CatalogManager) {
  ui->setupUi(this);

  bool superEnabled = role == User::Role::CompanyManager;

  ui->users_control->setEnabled(superEnabled);
  ui->report->setEnabled(superEnabled);

  connect(ui->add, SIGNAL(clicked()), SLOT(on_product_add()));
  connect(ui->remove, SIGNAL(clicked()), SLOT(on_product_remove()));
  connect(ui->users_control, SIGNAL(clicked()), SLOT(on_user_management()));
  connect(ui->report, SIGNAL(clicked()), SLOT(on_report()));
  connect(ui->orders, SIGNAL(clicked()), SLOT(on_order_management()));

  users = new Users(nullptr);
  users->hide();

  add_product = new AddProduct(nullptr);
  add_product->hide();

  order_management = new OrderManagement(nullptr);
  order_management->hide();

  report = new SalesReport(nullptr);
  report->hide();

  connect(add_product, SIGNAL(product(Product)), SLOT(on_product_added(Product)));
  connect(&PRODUCT_DB, SIGNAL(updated()), SLOT(on_updated()));

  on_updated();
}

CatalogManager::~CatalogManager() {
  delete ui;
}

void CatalogManager::on_user_management() {
  users->show();
}

void CatalogManager::on_report() {
  report->show();
}

void CatalogManager::on_product_remove() {
  QList<QTableWidgetItem*> selectedItems = ui->table->selectedItems();
  set<int> selected_rows;
  set<QString> removed_articles;

  for (auto item : selectedItems) {
    selected_rows.insert(item->row());
  }

  for (auto row : selected_rows) {
    auto article = ui->table->item(row, 1)->text();
    removed_articles.insert(article);
  }

  for (auto article : removed_articles) {
    PRODUCT_DB.remove_product(article.toStdString());
  }
}

void CatalogManager::on_product_add() {
  add_product->show();
}

void CatalogManager::on_order_management() {
  order_management->show();
}

void CatalogManager::on_product_added(Product product) {
  Product other;
  if (false == PRODUCT_DB.product_by_article(product.article, other))
    PRODUCT_DB.add_product(product);
}

void CatalogManager::on_updated() {
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
