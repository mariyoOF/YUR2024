#ifndef SALESREPORT_H
#define SALESREPORT_H

#include <QWidget>

namespace Ui {
class SalesReport; //класс для работы с отчетом
}

class SalesReport : public QWidget
{
  Q_OBJECT

public:
  explicit SalesReport(QWidget *parent = nullptr);
  ~SalesReport();

public slots:
  void on_calc();

private:
  Ui::SalesReport *ui;
};

#endif // SALESREPORT_H
