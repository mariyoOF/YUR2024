#ifndef USERS_H
#define USERS_H

#include <QWidget>

namespace Ui {
  class Users;
}

class Users : public QWidget {
  Q_OBJECT

public:
  explicit Users(QWidget *parent = nullptr);
  ~Users();

public slots:
  void on_remove();
  void on_add();
  void on_updated();

private:
  Ui::Users *ui;
};

#endif // USERS_H
