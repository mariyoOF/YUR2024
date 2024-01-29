#include "salesreport.h"
#include "ui_salesreport.h"
#include "model/productdb.h"

SalesReport::SalesReport(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SalesReport) {
  ui->setupUi(this);

  connect(ui->calc, SIGNAL(clicked()), SLOT(on_calc()));

  //ui->start->setValidator(dateValidator);
  //ui->end->setValidator(dateValidator);
}

SalesReport::~SalesReport() {
  delete ui;
}

void SalesReport::on_calc() {
  QString from = ui->start->text();
  QString to = ui->end->text();

  int count = PRODUCT_DB.count(from, to);
  int sum = PRODUCT_DB.sum(from, to);

  ui->count->setText(QString::number(count));
  ui->sum->setText(QString::number(sum));
}
