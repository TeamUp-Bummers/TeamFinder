#include "mainwindow.h"
#include "register.h"
#include "ui_register.h"


Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Cancel","Are You Sure,You Want to stop registration ?",QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
            this->close();
        MainWindow* mainwindow = new MainWindow();
            mainwindow->show();
    }


}

