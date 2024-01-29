#include "addproduct.h"
#include "ui_addproduct.h"
#include <QIntValidator>

AddProduct::AddProduct(QWidget *parent) : //функция добавления новго товара
  QWidget(parent),
  ui(new Ui::AddProduct) {
  ui->setupUi(this);

  ui->cost->setValidator(new QIntValidator(0, 9999999, this)); //параметры цены
  ui->kind->setValidator(new QIntValidator(0, 10, this)); //параметры сорта

  //QRegExp R_date("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(19[0-9][0-9]|20[0-9][0-9])");
  //QRegExpValidator *dateValidator = new QRegExpValidator(R_date, this);

  //ui->expiry_date->setPlaceholderText("Example : 01/01/2023"); //параметры "годен до"
  //ui->receipt_date->setPlaceholderText("Example : 01/01/2023"); //параметры даты завоза

  connect(ui->add, SIGNAL(clicked()), SLOT(on_add())); //кнопки "добавить"
  connect(ui->back, SIGNAL(clicked()), SLOT(hide())); //и "назад"
}

AddProduct::~AddProduct() { //конструктор отчистки информации всей таблицы
  delete ui;
}

void AddProduct::on_add() {
  auto all_fields = {ui->kind, ui->cost, ui->name, ui->article, ui->name, ui->expiry_date, ui->receipt_date};

  for (auto field : all_fields) {
    if (field->text().isEmpty())
      return;
  }

  Product data; //

  data.cost = ui->cost->text().toInt();
  data.kind = ui->kind->text().toInt();

  data.name = ui->name->text().toStdString();
  data.article = ui->article->text().toStdString();
  data.expiry_date = ui->expiry_date->text().toStdString();
  data.receipt_date = ui->receipt_date->text().toStdString();

  emit product(data);
}
