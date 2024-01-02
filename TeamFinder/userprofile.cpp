#include "userprofile.h"
#include "ui_userprofile.h"
#include "datahandler.h"
#include "mainscreen.h"
#include <QString>
#include <fstream>
#include <vector>
#include <QMessageBox>
#include <QCloseEvent>


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
/*
    Function to display user profile information when the UserProfile window is shown
    - Set the window title to include the current username
    - Set the displayed username
    - Populate the game and rank combo boxes
    - Retrieve and display the user's profile data
*/
void UserProfile::showEvent(QShowEvent *event){
// ReadGames From a File
    this->setWindowTitle("Teamfinder : " + CurrentUser);
    this->ui->username->setText(CurrentUser);
    //---------------Hard Coded For Now--------------
    this->ui->GameID->addItem("Counter Strike");
    this->ui->GameID->addItem("Valorant");
    // -------------------------------------
    ProfileData* current_user = RetrieveData(CurrentUser);

    this->ui->GameID->setCurrentText(current_user->game_name);
    this->ui->RankID->setCurrentText(current_user->game_rank);
    this->ui->ProfileDescription->setText(current_user->profile_description);
    this->ui->playtime->setText(current_user->playtime);
    this->ui->discord_tag->setText(current_user->discord_tag);
    this->ui->contact_link->setText(current_user->email);
    delete current_user;

    QMainWindow::showEvent(event);
}




/*
    Function to handle the "Change Password" button click in the UserProfile window
    - Create an instance of the changePassword window
    - Execute the changePassword window
*/

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





/*
    Function to handle the "Save" button click in the UserProfile window
    - Retrieve and validate the user profile data from the input fields
    - Check if the current user is trying to change their username and handle accordingly
    - Update the username if changed and set the new username as the current user
    - Close the current UserProfile window and open the Mainscreen window
    - Update the user's profile data in the database
*/
void UserProfile::on_ProfileSave_clicked()
{

    QString current_user = this->ui->username->text();
    QString current_game = this->ui->GameID->currentText();
    QString rank_id = this->ui->RankID->currentText();
    QString profile_description = this->ui->ProfileDescription->toPlainText();
    QString playtime = this->ui->playtime->text();
    QString user_email = this->ui->contact_link->text();
    QString discord_tag = this->ui->discord_tag->text();

    bool canExit = true;

    bool isUnfilled = (current_game.isEmpty() || rank_id.isEmpty() || profile_description.isEmpty() || playtime.isEmpty()|| user_email.isEmpty());


    if(isUnfilled){
        QMessageBox::information(this,"Information","You Wont Be Listed To Other Users, Until You Fill up Your Profile");

    }else   {
        if(!(current_user == CurrentUser)){
            if(UserNameMatches(current_user)){
                QMessageBox::information(this,"Information","This Username Already Exists! Try Another Name");
                canExit = false;
            }else{
                UpdateUserName(current_user);
                CurrentUser = current_user;

            }

        }

    }
    if(canExit){
        Mainscreen* mainscreen = new Mainscreen();
        this->close();
        mainscreen->show();
        UpdateProfile(current_game,rank_id,profile_description,playtime.toInt(),discord_tag,user_email);

    }
}






void UserProfile::on_cancel_clicked()
{
    this->close();
    Mainscreen* mainscreen =new Mainscreen();
    mainscreen->show();
}

