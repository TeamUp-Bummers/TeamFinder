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
/*
    Slot function for handling the button click event in the forgot_password class
    Retrieve entered values for username, unique key, and new password
    Check if none of the fields is empty
    If not empty, check if the entered new password and confirm password fields match
    If matching, check if the new password is valid (uppercase, lowercase, and numbers)
    If valid, check if the entered username exists
    If the username exists, check if the entered unique key matches the one stored in the database
    If the unique key matches, update the password for the user, display a success message, and close the window
    If the unique key does not match or the username does not exist, display appropriate error messages
    If any field is left empty, display a message to fill in all fields
*/

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

/*
    Slot function for handling the visibility toggle button click event in the changePassword class
    Toggle between password visibility and hidden modes for the current password line edit
*/

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


/*
    Slot function for handling the visibility toggle button click event in the changePassword class
    Toggle between password visibility and hidden modes for the current password line edit
*/

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

