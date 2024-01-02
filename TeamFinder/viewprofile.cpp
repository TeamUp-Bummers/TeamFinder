#include "viewprofile.h"
#include "ui_viewprofile.h"
#include "datahandler.h"



ViewProfile::ViewProfile(const QString& username,QWidget *parent) :
    QDialog(parent),username(username),
    ui(new Ui::ViewProfile)
{
    ui->setupUi(this);
}

ViewProfile::~ViewProfile()
{
    delete ui;
}
/*
    Overridden function to handle the showEvent in the ViewProfile class
    - Set the window title to "Teamfinder : " followed by the username
    - Retrieve profile data using the RetrieveData function
    - Update UI elements with the retrieved profile data (username, profile description, playtime, discord tag, email, game information, rank data)
*/

void ViewProfile::showEvent(QShowEvent *event)
{
    this->setWindowTitle("Teamfinder : "+this->username);
    ProfileData* profile_data = RetrieveData(this->username);


    this->ui->username_box->setText(this->username);
    this->ui->profile_description->setText(profile_data->profile_description);
    this->ui->playtime->setText(profile_data->playtime);
    this->ui->discord_tag->setText(profile_data->discord_tag);
    this->ui->email->setText(profile_data->email);
    this->ui->game_information->setText(profile_data->game_name);
    this->ui->rank_data->setText(profile_data->game_rank);




    QDialog::showEvent(event);
}

