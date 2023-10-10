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




void changePassword::on_pushButton_2_clicked()
{
    this->close();
}


void changePassword::on_pushButton_clicked()
{
    this->close();
}









