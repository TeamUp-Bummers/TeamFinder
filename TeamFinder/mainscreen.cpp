#include "mainscreen.h"
#include "mainwindow.h"
#include "ui_mainscreen.h"
#include "databaseQuery.h"
#include "viewprofile.h"

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
    this->ui->tableView->verticalHeader()->hide();
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->game->addItem("Counter Strike");
    this->ui->game->addItem("Valorant");
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


void Mainscreen::on_tableView_clicked()
{
    QModelIndex selectedRow = this->ui->tableView->selectionModel()->currentIndex();
    QAbstractItemModel* model = this->ui->tableView->model();
    QModelIndex firstColumnIndex = model->index(selectedRow.row(),0);
    QString username = this->ui->tableView->model()->data(firstColumnIndex).toString();

    ViewProfile* viewprofile = new ViewProfile(username);
    viewprofile->show();
}

