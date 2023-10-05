#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

#include <QtDebug>
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QMessageBox>




enum Login_Status{
    NO_ACCOUNT,
    ACCESS_GRANTED,
    ACCESS_DENIED
};

void connectDatabase();
bool userNameExists(const QString&);
bool passwordMatch(const QString& username,const QString& password);
Login_Status Login(const QString&,const QString&);
void CreateEntry(const QString&,const QString&);


#endif // DATABASEQUERY_H
