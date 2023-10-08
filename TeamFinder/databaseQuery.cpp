#include "databaseQuery.h"
#include "safteyinspector.h"

void connectDatabase(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("XueHue123");
    db.setDatabaseName("teamfinder");

    if(db.open()){
        qDebug() << "Database is Connected";
    }else{
        qDebug() << "Database isnt Connected";
    }

}

bool userNameExists(const QString& username){
    QSqlQuery query;
    QString result;
    query.prepare("SELECT username FROM teamfinder.users WHERE username=(:username)");
    query.bindValue(":username",username);
    query.exec();
    if(query.next()){
        result = query.value(0).toString();
        if(result == username) return true;
    }else{
        return false;
    }


}

bool passwordMatch(const QString& username,const QString& password){

    QSqlQuery query;
    QString hash_password;
    QString password_salt;

    query.prepare("SELECT password,salt FROM teamfinder.users WHERE username=(:username)");
    query.bindValue(":username",username);
    query.exec();
    if(query.next()){
        hash_password = query.value(0).toString();
        password_salt = query.value(1).toString();
        if(hash_password == HashFunction(password+password_salt)) return true;
        return false;
    }
}




Login_Status Login(const QString& username, const QString& password){
    Login_Status status;
    if(!userNameExists(username)) return NO_ACCOUNT;
    if(!passwordMatch(username,password)) return ACCESS_DENIED;
    return ACCESS_GRANTED;

}




void CreateEntry(const QString & username, const QString & password,const QString& salt)
{
    QSqlQuery query;
    query.prepare("INSERT INTO teamfinder.users(username,password,salt) VALUES(:username,:password,:salt)");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":salt",salt);
    query.exec();
}
