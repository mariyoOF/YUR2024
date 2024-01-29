#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QWidget>
#include "model/user.h"

namespace Ui {
class AuthWidget; //класс для аторизации пользователей
}

class AuthWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AuthWidget(QWidget *parent = nullptr);
    ~AuthWidget();

private slots:
    void enter();

signals:
    void auth_ok(User::Role);

private:
    Ui::AuthWidget *ui;
};

#endif // AUTHWIDGET_H
