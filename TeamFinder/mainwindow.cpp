#include "mainwindow.h"
#include "databaseQuery.h"
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
    Login_Status status = Login(username,password);
    if(username !="" && password !=""){
        if(status == NO_ACCOUNT){
            QMessageBox::information(this,"Login Status","No Account with that username found !");
        }else if(status == ACCESS_DENIED){
            QMessageBox::information(this,"Login Status","Incorrect Password !");
        }else if(status == ACCESS_GRANTED){
            Mainscreen* mainscreen = new Mainscreen();
            this->close();
            mainscreen->show();

        }

    }else{
        QMessageBox::information(this,"Login Status","Fill Up Username and Password Before Logging In !");
    }

}


void MainWindow::on_Register_clicked()
{
    this->hide();
    Register *register_screen = new Register();
    register_screen->show();
}
