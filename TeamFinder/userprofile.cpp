#include "userprofile.h"
#include "ui_userprofile.h"
#include "databaseQuery.h"
#include <QString>
UserProfile::UserProfile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserProfile)
{
    ui->setupUi(this);
}

UserProfile::~UserProfile()
{
    delete ui;
}
void UserProfile::showEvent(QShowEvent *event){
// ReadGames From a File

    this->ui->username->setText(CurrentUser);

    QMainWindow::showEvent(event);
}






void UserProfile::on_pushButton_clicked()
{
    changePassword* password_screen = new changePassword();
    password_screen->exec();
}

