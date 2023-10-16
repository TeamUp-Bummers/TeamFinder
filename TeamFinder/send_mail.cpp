#include "send_mail.h"
#include "ui_send_mail.h"
#include "mainscreen.h"
#include "databaseQuery.h"

extern int usercount;
extern std::vector<LobbyData> user_lobby;


send_mail::send_mail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::send_mail)
{
    ui->setupUi(this);

}

send_mail::~send_mail()
{
    delete ui;
}

void send_mail::on_sendInvite_clicked()
{
    QString password = this->ui->email_password->text();
    QString message = this->ui->message->toPlainText();
    QString email = this->ui->email->text();
    QString subject= this->ui->subject->text();

    bool isEmpty = (password.isEmpty() || message.isEmpty() || email.isEmpty() || subject.isEmpty());
    if(!isEmpty){
        qDebug() << "First Part Complete";
    }else{
        QMessageBox::information(this,"Information","Fill Up Every Box Before Sending Mail");
    }

}



void send_mail::showEvent(QShowEvent *event)
{

    for(int i=0;i<usercount;i++){
        this->ui->listWidget->addItem(user_lobby[i].email);
    }
    this->ui->email->setText(getParticularData("email",CurrentUser));


    QDialog::showEvent(event);
}
