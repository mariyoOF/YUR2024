#ifndef USERS_H
#define USERS_H

#include <QWidget>

namespace Ui {
  class Users; //класс для работы с пользователями
}

class Users : public QWidget {
  Q_OBJECT

public:
  explicit Users(QWidget *parent = nullptr);
  ~Users();

public slots:
  void on_remove(); //удаление пользователя
  void on_add(); //добавление
  void on_updated();//обновление

private:
  Ui::Users *ui;
};

#endif // USERS_H
