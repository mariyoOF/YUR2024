#include "users.h"
#include "model/productdb.h"
#include "ui_users.h"
#include "model/user.h"
#include <set>
using namespace std;

Users::Users(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Users) {
  ui->setupUi(this);

  on_updated();

  connect(ui->add, SIGNAL(clicked()), SLOT(on_add()));
  connect(ui->remove, SIGNAL(clicked()), SLOT(on_remove()));
  connect(&PRODUCT_DB, SIGNAL(updated()), SLOT(on_updated()));
}

Users::~Users() {
  delete ui;
}

void Users::on_remove() {
  QList<QTableWidgetItem*> selectedItems = ui->table->selectedItems();
  set<int> selected_rows;
  set<QString> removed_users;

  for (auto item : selectedItems) { //обращаемся к сторкам таблицы
    selected_rows.insert(item->row());
  }

  for (auto row : selected_rows) { //удаляем пользователя по логину
    auto login = ui->table->item(row, 0)->text();
    removed_users.insert(login);
  }

  for (auto login : removed_users) {
    User user = PRODUCT_DB.get_user(login);

    if (user.login == CURRENT_USER) {
      continue;
    }

    PRODUCT_DB.remove_user(user.login);
  }
}

void Users::on_add() { //добавляем пользователя и его данные
  QString login = ui->login->text();
  QString password = ui->password->text();

  if (login.isEmpty() || password.isEmpty()) //
    return;

  if (PRODUCT_DB.is_login_busy(login)) //если логин занят
    return;

  bool isSuper = ui->isSuper->isChecked();
  User::Role role;

  if (false == isSuper) {
    role = User::Role::ProductManager;
  }
  else {
    role = User::Role::CompanyManager;
  }

  PRODUCT_DB.add_user(User(login.toStdString(), password.toStdString(), role));
}

void Users::on_updated() { //обновление данных БД пользователей
  vector<User> users = PRODUCT_DB.users();

  ui->table->setRowCount(0);
  for (auto user : users) {
    int index = ui->table->rowCount();
    ui->table->insertRow(index);

    ui->table->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(user.login)));
    ui->table->setItem(index, 1, new QTableWidgetItem(QString::fromStdString(User::role_to_string(user.role))));
  }
}
