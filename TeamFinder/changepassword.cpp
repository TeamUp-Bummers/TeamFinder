#include "changepassword.h"
#include "ui_changepassword.h"
#include "datahandler.h"

changePassword::changePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changePassword)
{
    ui->setupUi(this);
    this->setWindowTitle("Teamfinder : Change Password");
}

changePassword::~changePassword()
{
    delete ui;
    this->ui->passwordView->setCheckable(true);
    this->ui->passwordView_2->setCheckable(true);
    this->ui->passwordView_3->setCheckable(true);
}


/*
    Slot function for handling the button click event in the changePassword class
    Retrieve entered passwords from line edits
    Check if any of the password fields is empty
    If not empty, check if the entered current password matches the stored password for the current user
    If passwords match, check if the entered new password and confirm password fields match
    If matching, check if the new password is valid (uppercase, lowercase, and numbers)
    If valid, update the password for the current user, display a success message, and close the window
    If the entered passwords do not match or the new password is not valid, display appropriate error messages
    If any field is left empty, display a message to fill in all fields
*/

void changePassword::on_pushButton_clicked()
{
    QString entered_password = this->ui->lineEdit->text();
    QString newPassword = this->ui->lineEdit_2->text();
    QString confirmPassword = this->ui->lineEdit_3->text();

    if(!(entered_password.isEmpty()||newPassword.isEmpty()||confirmPassword.isEmpty())){
        if(passwordMatch(CurrentUser,entered_password)){
            if(passwordMatches(newPassword,confirmPassword)){
                if(isValidPassword(newPassword)){
                    updatePassword(newPassword,CurrentUser);
                    QMessageBox::information(this,"Status","Password Has Been Updated !");
                    this->close();
                }else{
                    QMessageBox::information(this,"Information","Use A Strong Password! (uppercase,lowercase and numbers)");
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







/*
    Slot function for handling the visibility toggle button click event in the changePassword class
    Toggle between password visibility and hidden modes for the current password line edit
*/


void changePassword::on_passwordView_clicked()
{
    switch(this->ui->lineEdit->echoMode()){
    case (QLineEdit::Password):
        this->ui->lineEdit->setEchoMode(QLineEdit::Normal);
        break;
    default:
        this->ui->lineEdit->setEchoMode(QLineEdit::Password);
    }
}

/*
    Slot function for handling the visibility toggle button click event in the changePassword class
    Toggle between password visibility and hidden modes for the current password line edit
*/
void changePassword::on_passwordView_2_clicked()
{
    switch(this->ui->lineEdit_2->echoMode()){
    case (QLineEdit::Password):
        this->ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
        break;
    default:
        this->ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}

/*
    Slot function for handling the visibility toggle button click event in the changePassword class
    Toggle between password visibility and hidden modes for the current password line edit
*/
void changePassword::on_passwordView_3_clicked()
{
    switch(this->ui->lineEdit_3->echoMode()){
    case (QLineEdit::Password):
        this->ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
        break;
    default:
        this->ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    }
}

