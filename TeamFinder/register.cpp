#include "mainwindow.h"
#include "register.h"
#include "ui_register.h"
#include "databaseQuery.h"
#include "safteyinspector.h"


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


void Register::on_pushButton_clicked()
{

    QString username = ui->username->text();
    QString password = ui->password->text();
    QString confirmPassword = ui->confirm_password->text();

    if(!(username.isEmpty()) && !(password.isEmpty()) && !(confirmPassword.isEmpty())){

            Registration_Status status;
            status = MakeRegistration(username,password,confirmPassword);
            if(status == REGISTERED){
                QMessageBox::information(this,"Registration Status","Successfully Registered New User");
                this->close();
                MainWindow* mainwindow = new MainWindow();
                mainwindow->show();
            }else if(status==WEAK_PASSWORD){
                QMessageBox::information(this,"Registration Status","Use A Strong Password !");
            }else if(status==ALREADY_EXISTS){
                QMessageBox::information(this,"Registration Status","User with that name already exists !");
            }else if(status==DIDNT_MATCH){
                QMessageBox::information(this,"Registration Status","Passwords Dont Match");
            }
    }else{

            QMessageBox::information(this,"Registration Status","Fill up all the input fields");

    }

    qDebug() << username << password << confirmPassword;


}

