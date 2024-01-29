#include "authwidget.h"
#include "ui_authwidget.h"
#include "model/productdb.h"
#include "model/user.h"

using namespace std;

AuthWidget::AuthWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthWidget) {
    ui->setupUi(this);

    connect(ui->enter, SIGNAL(clicked()), SLOT(enter()));
    connect(ui->back, SIGNAL(clicked()), SLOT(close()));
}

AuthWidget::~AuthWidget() {
    delete ui;
}

void AuthWidget::enter() {
  string login = ui->login->text().toStdString();
  string password = ui->password->text().toStdString();

  ui->login->text().clear();
  ui->password->text().clear();

  if (PRODUCT_DB.is_login_busy(QString::fromStdString(login)) == false)
    return;

  User user = PRODUCT_DB.get_user(QString::fromStdString(login));
  if (user.password == password) {
    CURRENT_USER = user.login;
    emit auth_ok(user.role);
    this->close();
  }
}
