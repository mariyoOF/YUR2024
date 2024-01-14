#include "admin.h"
#include "ui_admin.h"
#include <QMessageBox>   //библиотека для окон оповещения

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
}

admin::~admin()
{
    delete ui;
}

/*void admin::on_pushButton_clicked() //кнопка ВОЙТИ
{
    QString login = ui->login->text(); //создание агрументов для логина и пароля с типом данных текст
    QString password = ui->pass->text();

    if(login == "Admin" && password == "769") { //проверка логина и пароля -> следующее окно
        uTable = new Table(this);
        uTable->show();

    } else {
        QMessageBox::warning(this, "Вход", "Ошибка авторизации"); //окно ошибки входа
    }
}*/
