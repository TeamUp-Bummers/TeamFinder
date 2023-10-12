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

void Mainscreen::Mainscreen::showEvent(QShowEvent *event)
{
    this->ui->game->addItem("Counter Strike");
    this->ui->game->addItem("Valorant");


    QMessageBox::information(this,"Information","Loaded Screen");
    QSqlQueryModel* model = RetrieveInformation();
    this->ui->tableView->setModel(model);
    QMainWindow::showEvent(event);

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


void Mainscreen::on_pushButton_3_clicked()
{
    this->ui->game->setCurrentIndex(-1);
    this->ui->rank->setCurrentIndex(-1);
    this->ui->tableView->setModel(RetrieveInformation());


}



void Mainscreen::on_game_currentTextChanged(const QString &arg1)
{
    QStringList ranks = RetrieveRanks(arg1);
    this->ui->rank->clear();
    this->ui->rank->addItems(ranks);
    QSqlQueryModel* model = Filter(arg1);
    this->ui->tableView->setModel(model);


}


void Mainscreen::on_rank_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel* model = Filter(this->ui->game->currentText(),arg1);
    this->ui->tableView->setModel(model);
}

