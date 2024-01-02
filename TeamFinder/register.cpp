#include "mainwindow.h"
#include "register.h"
#include "ui_register.h"
#include "datahandler.h"
#include "safteyinspector.h"


Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->ui->pushButton->setCursor(Qt::PointingHandCursor);
    this->ui->confirmPasswordView->setCursor(Qt::PointingHandCursor);
    this->ui->passwordView->setCursor(Qt::PointingHandCursor);
    this->ui->confirmPasswordView->setCursor(Qt::PointingHandCursor);
    this->ui->passwordView->setCheckable(true);
    this->ui->confirmPasswordView->setCheckable(true);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_2_clicked()
{
    this->close();
    MainWindow* mainwindow = new MainWindow();
    mainwindow->show();
}
/*
    Slot function for handling the button click event in the Register class
    - Retrieve username, password, confirmPassword, and UniqueKey from UI elements
    - Check if any of the fields is empty
    - Call MakeRegistration function with the provided information
    - Display registration status messages based on the returned status
    - Close the window and open the main window if registration is successful
*/


void Register::on_pushButton_clicked()
{

    QString username = ui->username->text();
    QString password = ui->password->text();
    QString confirmPassword = ui->confirm_password->text();
    QString UniqueKey = ui->unique_key->text();

    if(!(username.isEmpty()) && !(password.isEmpty()) && !(confirmPassword.isEmpty()) && !(UniqueKey.isEmpty())){

            Registration_Status status;
            status = MakeRegistration(username,password,confirmPassword,UniqueKey);
            if(status == REGISTERED){
                QMessageBox::information(this,"Registration Status","Successfully Registered New User");
                this->close();
                MainWindow* mainwindow = new MainWindow();
                mainwindow->show();
            }else if(status==WEAK_PASSWORD){
                QMessageBox::information(this,"Registration Status","Use A Strong Password ! (uppercase,lowercase and numbers)");
            }else if(status==ALREADY_EXISTS){
                QMessageBox::information(this,"Registration Status","User with that name already exists !");
            }else if(status==DIDNT_MATCH){
                QMessageBox::information(this,"Registration Status","Passwords Dont Match");
            }
    }else{

            QMessageBox::information(this,"Registration Status","Fill up all the input fields");

    }



}


void Register::on_passwordView_clicked()
{
    switch(this->ui->password->echoMode()){
    case (QLineEdit::Password):
            this->ui->password->setEchoMode(QLineEdit::Normal);
            break;
    default:
            this->ui->password->setEchoMode(QLineEdit::Password);
    }


}



void Register::on_confirmPasswordView_clicked()
{
    switch(this->ui->confirm_password->echoMode()){
    case (QLineEdit::Password):
            this->ui->confirm_password->setEchoMode(QLineEdit::Normal);
            break;
    default:
            this->ui->confirm_password->setEchoMode(QLineEdit::Password);
    }

}

