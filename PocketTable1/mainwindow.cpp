#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Start_clicked()
{
    uAdmin = new admin(this); // allocated space for a new MyDialog
        // while also giving a parent class of
        // this, the MainWindow class
    uAdmin->show(); // call the show method on the object
}

