#include "userprofile.h"
#include "ui_userprofile.h"
#include "databaseQuery.h"
#include "mainscreen.h"
#include <QString>
#include <fstream>
#include <vector>


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
    //---------------Hard Coded For Now--------------
    this->ui->GameID->addItem("Counter Strike");
    this->ui->GameID->addItem("Valorant");
    // -------------------------------------
    ProfileData* current_user = RetrieveData();

    this->ui->GameID->setCurrentText(current_user->game_name);
    this->ui->RankID->setCurrentText(current_user->game_rank);
    this->ui->ProfileDescription->setText(current_user->profile_description);
    this->ui->playtime->setText(current_user->playtime);
    delete current_user;

    QMainWindow::showEvent(event);
}






void UserProfile::on_pushButton_clicked()
{
    changePassword* password_screen = new changePassword();
    password_screen->exec();
}




void UserProfile::on_GameID_currentTextChanged(const QString &arg1)
{
    QStringList ranks = RetrieveRanks(arg1);
    this->ui->RankID->clear();
    this->ui->RankID->addItems(ranks);
}


void UserProfile::on_ProfileSave_clicked()
{
    Mainscreen* mainscreen = new Mainscreen();
    QString current_user = this->ui->username->text();
    QString current_game = this->ui->GameID->currentText();
    QString rank_id = this->ui->RankID->currentText();
    QString profile_description = this->ui->ProfileDescription->toPlainText();
    QString playtime = this->ui->playtime->text();



    bool isUnfilled = (current_game.isEmpty() || rank_id.isEmpty() || profile_description.isEmpty() || playtime.isEmpty());
    qDebug() << isUnfilled;

    if(isUnfilled){
        QMessageBox::information(this,"Information","You Wont Be Listed To Other Users, Until You Fill up Your Profile");
    }else{
        if(!(current_user == CurrentUser)){
            if(UserNameMatches(current_user)){
                QMessageBox::information(this,"Information","This Username Already Exists! Try Another Name");
            }else{
                UpdateUserName(current_user);
                CurrentUser = current_user;
                this->close();
                delete this;
                mainscreen->show();
            }

        }
    }

    UpdateProfile(current_game,rank_id,profile_description,playtime.toInt());
}



void UserProfile::on_CancelOut_clicked()
{
    Mainscreen* mainscreen = new Mainscreen();
    this->close();
    delete this;
    mainscreen->show();


}

