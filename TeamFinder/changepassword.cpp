#include "changepassword.h"
#include "ui_changepassword.h"
#include "databaseQuery.h"

changePassword::changePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changePassword)
{
    ui->setupUi(this);
}

changePassword::~changePassword()
{
    delete ui;
}




void changePassword::on_pushButton_clicked()
{
    QString entered_password = this->ui->lineEdit->text();
    QString newPassword = this->ui->lineEdit_2->text();
    QString confirmPassword = this->ui->lineEdit_3->text();

    if(!(entered_password.isEmpty()||newPassword.isEmpty()||confirmPassword.isEmpty())){
        if(passwordMatch(CurrentUser,entered_password)){
            if(passwordMatches(newPassword,confirmPassword)){
                if(isValidPassword(newPassword)){
                    updatePassword(newPassword);
                    QMessageBox::information(this,"Status","Password Has Been Updated !");
                    this->close();
                }else{
                    QMessageBox::information(this,"Information","Use A Strong Password");
                }

            } else{
                QMessageBox::information(this,"Information","New Passwords Dont Match !");
            }

        }else{
            QMessageBox::information(this,"Information","Current Password Doesn't Match !");
        }

    }else{
        QMessageBox::information(this,"Information","Dont Leave Any Field Empty");
    }


  //  this->close();
}


void changePassword::on_pushButton_2_clicked()
{
    this->close();
}









