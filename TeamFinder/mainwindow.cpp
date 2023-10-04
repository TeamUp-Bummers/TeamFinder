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
    QString password_retrieved;

   password_retrieved= checkCredentials(username,password);



    if(password == password_retrieved && password_retrieved!="NULL"){
        QMessageBox::information(this,"Login Status","Successful");
        this->close();
        Mainscreen *mainscreen = new Mainscreen();
        mainscreen->show();


    }else if(password_retrieved=="NULL" && password!=""){
        QMessageBox::information(this,"Login Status","User Not Found , Consider Registering!");
    }

    else if(username =="" || password == ""){
        QMessageBox::warning(this,"Login Status","Fill Up Both Parameters");
    }

    else{
        QMessageBox::warning(this,"Login Status","Access Denied");
    }

}


void MainWindow::on_Register_clicked()
{
    this->hide();
    Register *register_screen = new Register();
    register_screen->show();
}

