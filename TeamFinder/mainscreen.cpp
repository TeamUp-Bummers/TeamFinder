#include "mainscreen.h"
#include "mainwindow.h"
#include "ui_mainscreen.h"
#include "databaseQuery.h"

Mainscreen::Mainscreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainscreen)
{
    ui->setupUi(this);
}

Mainscreen::~Mainscreen()
{
    delete ui;
}


void Mainscreen::on_pushButton_clicked()
{
    UserProfile* userprofile = new UserProfile();
    this->close();
    userprofile->show();
}


void Mainscreen::on_pushButton_2_clicked()
{
    CurrentUser = "";
    this->close();
    MainWindow* mainwindow = new MainWindow();
    mainwindow->show();

}

