#include "addproduct.h"
#include "ui_addproduct.h"
#include <QIntValidator>

AddProduct::AddProduct(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AddProduct) {
  ui->setupUi(this);

  ui->cost->setValidator(new QIntValidator(0, 9999999, this));
  ui->kind->setValidator(new QIntValidator(0, 10, this));

  //ui->expiry_date->setValidator(dateValidator);
  //ui->receipt_date->setValidator(dateValidator);

  connect(ui->add, SIGNAL(clicked()), SLOT(on_add()));
  connect(ui->back, SIGNAL(clicked()), SLOT(hide()));
}

AddProduct::~AddProduct() {
  delete ui;
}

void AddProduct::on_add() {
  auto all_fields = {ui->kind, ui->cost, ui->name, ui->article, ui->name, ui->expiry_date, ui->receipt_date};

  for (auto field : all_fields) {
    if (field->text().isEmpty())
      return;
  }

  Product data;

  data.cost = ui->cost->text().toInt();
  data.kind = ui->kind->text().toInt();

  data.name = ui->name->text().toStdString();
  data.article = ui->article->text().toStdString();
  data.expiry_date = ui->expiry_date->text().toStdString();
  data.receipt_date = ui->receipt_date->text().toStdString();

  emit product(data);
}
