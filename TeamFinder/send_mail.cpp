#include "send_mail.h"
#include "ui_send_mail.h"
#include "mainscreen.h"
#include "databaseQuery.h"
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/NetException.h>


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
    QString content = this->ui->message->toPlainText();
    QString email = this->ui->email->text();
    QString subject= this->ui->subject->text();

    bool isEmpty = (password.isEmpty() || content.isEmpty() || email.isEmpty() || subject.isEmpty());
    if(!isEmpty){
        qDebug() << "First Part Complete";
        try{
            Poco::Net::MailMessage message;
            message.setSender(email.toStdString());
            message.setSubject(subject.toStdString());
            message.setContent(content.toStdString());
            message.setContentType("text/plain;charset=\"UTF-8\"");
            for(int i=0;i<usercount;i++){
                 message.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT,user_lobby[i].email.toStdString()));
            }
            Poco::Net::SMTPClientSession session("sandbox.smtp.mailtrap.io",587);
            session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN,"[SET __MAIL__TRAP__INFO]","__SET MAILTRAP __PASSWORD"); // using a  test smtp server
            session.sendMessage(message);

        }catch(Poco::Net::NetException &e){
            qDebug() << "Error :" << e.displayText();
        }
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
