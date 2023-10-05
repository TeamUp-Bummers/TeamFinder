#include "mainscreen.h"
#include "mainwindow.h"
#include "ui_mainscreen.h"


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

