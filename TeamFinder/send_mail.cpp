#include "send_mail.h"
#include "ui_send_mail.h"
#include "mainscreen.h"
#include "datahandler.h"
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
    this->ui->sendInvite->setCursor(Qt::PointingHandCursor);

}

send_mail::~send_mail()
{
    delete ui;
}
/*
    Slot function for handling the button click event in the send_mail class
    - Create an instance of the SMTP_Credentials struct and populate it with SMTP information from the configuration file
    - Retrieve content, email, and subject from UI elements
    - Check if any of the content, email, or subject is empty
    - If not empty, construct a Poco::Net::MailMessage with the provided information
    - Add recipients from the user_lobby vector to the mail message
    - Create an SMTPClientSession and login with the provided credentials
    - Send the mail message
    - Display a success message and close the window
    - Handle any exceptions and display error information if necessary
    - Delete the credentials struct
*/
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
            QString error_message = QString::fromStdString(e.displayText());
            QMessageBox::information(this,"Information",error_message);
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
    this->ui->email->setText(GetSpecificProfileData("email",CurrentUser));


    QDialog::showEvent(event);
}
