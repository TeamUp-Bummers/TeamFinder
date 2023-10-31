#include "viewhistory.h"
#include "ui_viewhistory.h"
#include "viewprofile.h"
#include "history.h"
#include <QMap>
#include <QVector>
#include <QTime>
#include <QMessageBox>





void ViewHistory::UpdateTableData()
{
    //-------------------------------------------------------------//

    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
       this->ui->tableWidget->setRowCount(0);

    //-------------------------------------------------------------//

    QMap<QString, QVector<PlayerData>> lobbies = RetrieveLobbyHistory();
    qDebug() << lobbies.size();
    if(!(lobbies.empty())){

        if(this->index >=0 && this->index < lobbies.size()){

            // ------------------Check Button Condition -------------------------//
            if(this->index == 0){
                this->ui->pushButton_2->setDisabled(true);

                (lobbies.size() != 1 ) ? this->ui->pushButton->setEnabled(true) : this->ui->pushButton->setEnabled(false);
            }else if(this->index == (lobbies.size()-1)){
                this->ui->pushButton_2->setEnabled(true);
                this->ui->pushButton->setDisabled(true);
            }else{
                this->ui->pushButton_2->setEnabled(true);
                this->ui->pushButton->setEnabled(true);
            }


            auto iterator = lobbies.begin() + this->index;
            auto timestamp = iterator.key();
            QString FormattedTime= (QDateTime::fromString(timestamp, "yyyyMMddHHmmss")).toString("(yyyy/MM/dd)(hh::mm::ss)");
            this->ui->timestamp->setText(FormattedTime);
            QVector<PlayerData>lobby = iterator.value();
            for (const PlayerData &player : lobby) {
                QTableWidgetItem *item = new QTableWidgetItem(player.username);
                QTableWidgetItem *item_two = new QTableWidgetItem(player.email);
                int row = this->ui->tableWidget->rowCount();
                this->ui->tableWidget->insertRow(row);
                this->ui->tableWidget->setItem(row,0,item);
                this->ui->tableWidget->setItem(row,1,item_two);

            }


        }

    }else if(lobbies.empty()){
        this->ui->pushButton->setDisabled(true);
        this->ui->pushButton_2->setDisabled(true);
    }

}

ViewHistory::ViewHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewHistory)
{
    ui->setupUi(this);
}

ViewHistory::~ViewHistory()
{
    delete ui;
}

void ViewHistory::showEvent(QShowEvent *event)
{

   this->UpdateTableData();
   QDialog::showEvent(event);
}

void ViewHistory::on_pushButton_2_clicked()
{

   this->index-=1;
   this->UpdateTableData();



}


void ViewHistory::on_pushButton_clicked()
{
   this->index+=1;

   this->UpdateTableData();

}




void ViewHistory::on_tableWidget_cellDoubleClicked()
{
   int selectedRow = this->ui->tableWidget->selectedItems().first()->row();
   QTableWidgetItem* username = this->ui->tableWidget->item(selectedRow,0);
   ViewProfile* viewprofile = new ViewProfile(username->text());
   viewprofile->show();
   this->ui->tableWidget->selectionModel()->clear();


}


void ViewHistory::on_pushButton_3_clicked()
{


   QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this,"Question","You Want To Clear Lobby History ?",QMessageBox::Yes|QMessageBox::No);
   if(reply == QMessageBox::Yes){
        DeleteHistory();
        this->index = 0;
        this->UpdateTableData();
   }


}

