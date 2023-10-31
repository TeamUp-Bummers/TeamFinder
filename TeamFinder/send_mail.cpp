#include "send_mail.h"
#include "ui_send_mail.h"
#include "mainscreen.h"
#include "databaseQuery.h"
#include "history.h"
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/NetException.h>
#include <yaml-cpp/yaml.h>
#include <string>


extern YAML::Node config;

struct SMTP_Credentials{
    std::string hostname;
    std::string username;
    std::string password;
    int port_no;
};

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
    SMTP_Credentials* credentials = new SMTP_Credentials();

    credentials->hostname = config["smtp"]["hostname"].as<std::string>();
    credentials->username = config["smtp"]["username"].as<std::string>();
    credentials->password = config["smtp"]["password"].as<std::string>();
    credentials->port_no = config["smtp"]["port"].as<int>();

    QString content = this->ui->message->toPlainText();
    QString email = this->ui->email->text();
    QString subject= this->ui->subject->text();

    bool isEmpty = (content.isEmpty() || email.isEmpty() || subject.isEmpty());
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
            Poco::Net::SMTPClientSession session(credentials->hostname,credentials->port_no);
            session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN,credentials->username,credentials->password); // using a  test smtp server
            session.sendMessage(message);

            QMessageBox::information(this,"Invitation","Mail Sent Successfully");
            SaveLobbyData();
            this->close();

        }catch(Poco::Net::NetException &e){
            qDebug() << "Error :" << e.displayText();
        }
    }else{
        QMessageBox::information(this,"Information","Fill Up Every Box Before Sending Mail");
    }


    delete credentials;




}



void send_mail::showEvent(QShowEvent *event)
{

    for(int i=0;i<usercount;i++){
        this->ui->listWidget->addItem(user_lobby[i].email);
    }
    this->ui->email->setText(getParticularData("email",CurrentUser));


    QDialog::showEvent(event);
}
