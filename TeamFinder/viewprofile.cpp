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

void ViewProfile::showEvent(QShowEvent *event)
{
    this->setWindowTitle("User :"+this->username);
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

