#include "forgot_password.h"
#include "ui_forgot_password.h"
#include "safteyinspector.h"
#include "datahandler.h"
#include <QLineEdit>
forgot_password::forgot_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgot_password)
{
    ui->setupUi(this);
    this->ui->passwordView->setCheckable(true);
    this->ui->passwordView_2->setCheckable(true);
}

forgot_password::~forgot_password()
{
    delete ui;
}

void forgot_password::on_pushButton_clicked()
{
    QString username = this->ui->username->text();
    QString unique_key = this->ui->Unique_Key->text();
    QString password = this->ui->pwrod->text();
    if(!(username.isEmpty()) && !(unique_key.isEmpty()) && !(password.isEmpty()) && !(ui->password->text().isEmpty())){
        if(passwordMatches(ui->pwrod->text(),ui->password->text())){
            if(isValidPassword(password)){
                if(UserNameMatches(username)){
                    if(UniqueKeyMatch(username,HashFunction(unique_key))){
                        updatePassword(password,username);
                        QMessageBox::information(this,"Alert","Password Changed !");
                        this->close();
                    }else{
                        QMessageBox::information(this,"Alert","Unique Key Doesnt Match");
                    }
                } else{
                    QMessageBox::information(this,"Alert","No Such User Found");
                }
            }else {
                QMessageBox::information(this,"Alert","Bad Password ! (Use uppercase, lowercase and numbers)");
            }
    }

}
}

void forgot_password::on_passwordView_clicked()
{
    switch(this->ui->pwrod->echoMode()){
    case (QLineEdit::Password):
            this->ui->pwrod->setEchoMode(QLineEdit::Normal);
            break;
    default:
            this->ui->pwrod->setEchoMode(QLineEdit::Password);
    }
}




void forgot_password::on_passwordView_2_clicked()
{
    switch(this->ui->password->echoMode()){
    case (QLineEdit::Password):
            this->ui->password->setEchoMode(QLineEdit::Normal);
            break;
    default:
            this->ui->password->setEchoMode(QLineEdit::Password);
    }
}

