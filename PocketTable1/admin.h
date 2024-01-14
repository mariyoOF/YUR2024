#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
//#include "table.h"

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

/*private slots:
    void on_pushButton_clicked();//переход в Table*/

private:
    Ui::admin *ui;
    //Table *uTable;
};
#endif // ADMIN_H
