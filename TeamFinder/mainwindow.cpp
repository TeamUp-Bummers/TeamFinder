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


void MainWindow::on_pushButton_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();

    if(username == "abc" && password == "password"){
        QMessageBox::information(this,"Login Informtion","Successful");
        this->hide();
        Mainscreen *mainscreen = new Mainscreen();
        mainscreen->show();


    }else{
        QMessageBox::warning(this,"Login Status","Access Denied");
    }

}


void MainWindow::on_Register_clicked()
{
    this->hide();
    Register *register_screen = new Register();
    register_screen->show();
}

