#include "mainscreen.h"
#include "mainwindow.h"
#include "ui_mainscreen.h"
#include "databaseQuery.h"
#include "viewprofile.h"
#include "viewhistory.h"
#include "send_mail.h"

int usercount = 0;

std::vector<LobbyData> user_lobby;

QSortFilterProxyModel* getSortedModel(QSqlQueryModel* model){
    QSortFilterProxyModel *sorted_model = new QSortFilterProxyModel();
    sorted_model->setDynamicSortFilter(true);
    sorted_model->setSourceModel(model);
    return sorted_model;
}
bool isAlreadyAdded(const QString& username){
    for(int i=0;i<usercount;i++){
        if(user_lobby[i].username == username){
            return true;
        }
    }
    return false;

};

void RemovePlayer(const QString& username){
    for(int i=0;i<usercount;i++){
        if(user_lobby[i].username == username){
          user_lobby.erase(user_lobby.begin()+i);
          break;
        }
    }

}

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
    if(usercount == 0){
        this->ui->deleteUser->setDisabled(true);
        this->ui->sendInvite->setDisabled(true);
    };

    if(!user_lobby.empty()){

        for(int i=0;i<usercount;i++){
                int rowCount = this->ui->tableWidget->rowCount();
                this->ui->tableWidget->insertRow(rowCount);
                QTableWidgetItem *item = new QTableWidgetItem(user_lobby[i].username);
                QTableWidgetItem *item_two = new QTableWidgetItem(user_lobby[i].email);
                this->ui->tableWidget->setItem(rowCount,0,item);
                this->ui->tableWidget->setItem(rowCount,1,item_two);
        }


    }

    this->ui->tableView->verticalHeader()->hide();
    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);



    this->ui->game->addItem("Counter Strike");
    this->ui->game->addItem("Valorant");


    QSqlQueryModel* model = RetrieveInformation();
    if(model == nullptr){
         this->ui->addToParty->setEnabled(false);
    }else{

         QSortFilterProxyModel* sortedModel = getSortedModel(model);
         this->ui->tableView->setModel(sortedModel);
         this->ui->tableView->setSortingEnabled(true);



    }
    this->working_model = model;
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
    user_lobby.clear();
    usercount = 0;
    this->close();

    MainWindow* mainwindow = new MainWindow();
    mainwindow->show();

}


void Mainscreen::on_pushButton_3_clicked()
{
    this->ui->lineEdit->clear();
    this->ui->game->setCurrentIndex(-1);
    this->ui->rank->setCurrentIndex(-1);
    QSqlQueryModel* model = RetrieveInformation();
    QSortFilterProxyModel* sortedModel = getSortedModel(model);
    this->ui->tableView->setModel(sortedModel);
    this->ui->tableView->setSortingEnabled(true);
    this->working_model = model;



}



void Mainscreen::on_game_currentTextChanged(const QString &arg1)
{
    QStringList ranks = RetrieveRanks(arg1);
    this->ui->rank->clear();
    this->ui->rank->addItems(ranks);
    QSqlQueryModel* model = Filter(arg1);
    QSortFilterProxyModel* sortedModel = getSortedModel(model);
    this->ui->tableView->setModel(sortedModel);
    this->ui->tableView->setSortingEnabled(true);


    this->working_model = model;



}


void Mainscreen::on_rank_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel* model = Filter(this->ui->game->currentText(),arg1);
    QSortFilterProxyModel* sortedModel = getSortedModel(model);

    this->ui->tableView->setModel(sortedModel);
    this->ui->tableView->setSortingEnabled(true);

    this->working_model = model;
}


void Mainscreen::on_tableView_doubleClicked()
{
    QModelIndex selectedRow = this->ui->tableView->selectionModel()->currentIndex();

    QAbstractItemModel* model = this->ui->tableView->model();
    QModelIndex firstColumnIndex = model->index(selectedRow.row(),0);
    QString username = this->ui->tableView->model()->data(firstColumnIndex).toString();

    ViewProfile* viewprofile = new ViewProfile(username);
    viewprofile->show();
}


void Mainscreen::on_addToParty_clicked()
{
    if(usercount<4){
         QModelIndex selectedRow = this->ui->tableView->selectionModel()->currentIndex();
         if(selectedRow.isValid()){

                QAbstractItemModel* model = this->ui->tableView->model();
                QModelIndex usernameIndex = model->index(selectedRow.row(),0);
                QString username = this->ui->tableView->model()->data(usernameIndex).toString();
                QString email = getParticularData("email",username);
                if(!isAlreadyAdded(username)){
                    int rowCount = this->ui->tableWidget->rowCount();
                    this->ui->tableWidget->insertRow(rowCount);
                    QTableWidgetItem *item = new QTableWidgetItem(username);
                    QTableWidgetItem *item_two = new QTableWidgetItem(email);
                    this->ui->tableWidget->setItem(rowCount,0,item);
                    this->ui->tableWidget->setItem(rowCount,1,item_two);


                    usercount +=1;
                    user_lobby.push_back({username,email});
                    this->ui->deleteUser->setEnabled(true);
                    this->ui->sendInvite->setEnabled(true);

                }else{
                    QMessageBox::information(this,"Information","This User Has Already Been Added");
                }

         }else{
                QMessageBox::information(this,"Information","Consider Selecting a User first !");
         }
        this->ui->tableView->selectionModel()->clear();

    }else{
         QMessageBox::information(this,"Information","Cant Add More than 4 Users to a Lobby");
    }

}


void Mainscreen::on_tableWidget_doubleClicked()
{

    int selectedRow = this->ui->tableWidget->selectedItems().first()->row();
    QTableWidgetItem* username = this->ui->tableWidget->item(selectedRow,0);
    ViewProfile* viewprofile = new ViewProfile(username->text());
    viewprofile->show();
    this->ui->tableWidget->selectionModel()->clear();
    qDebug() << usercount;
}


void Mainscreen::on_deleteUser_clicked()
{

    int selectedRow = this->ui->tableWidget->currentRow();
    if(selectedRow>=0){
        QString username = this->ui->tableWidget->item(selectedRow,0)->text();
        RemovePlayer(username);
        this->ui->tableWidget->removeRow(selectedRow);
        usercount-=1;
        if(usercount==0){
                 this->ui->deleteUser->setEnabled(false);
                 this->ui->sendInvite->setEnabled(false);
        }
        this->ui->tableWidget->selectionModel()->clear();
    }else{
        QMessageBox::information(this,"Information","Select a User First !");
    }

};








void Mainscreen::on_sendInvite_clicked()
{
    send_mail* sendinvitation = new send_mail();
    sendinvitation->exec();
}



void Mainscreen::on_lineEdit_textChanged(const QString &arg1)
{


    if(arg1.isEmpty()){
        this->ui->tableView->setModel(this->working_model);
    }else{
        QSortFilterProxyModel* model = FilterByName(this->working_model,arg1);
        model->setParent(this);
        this->ui->tableView->setModel(model);

    }

}


void Mainscreen::on_viewHistory_clicked()
{
    ViewHistory* viewhistory = new ViewHistory();
    viewhistory->show();
}

