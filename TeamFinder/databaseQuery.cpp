#include "databaseQuery.h"


void setDatabaseInformation(){

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

QString checkCredentials(const QString& username, const QString& password){

    QSqlQuery query;

    query.prepare("SELECT username FROM teamfinder.users WHERE username=(:username_id)");
    query.bindValue(":username_id",username);
    query.exec();
    if(query.next()){
        QString result= query.value(0).toString();
        query.prepare("SELECT password FROM teamfinder.users WHERE username=(:username)");
        query.bindValue(":username",username);
        query.exec();
        if(query.next()){
            result = query.value(0).toString();
            return result;
        }

    }else{

        return "NULL";
    }



}



