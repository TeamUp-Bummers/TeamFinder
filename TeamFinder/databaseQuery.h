#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

#include <QtDebug>
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QMessageBox>
#include <safteyinspector.h>
extern QString CurrentUser;

void connectDatabase();
bool passwordMatch(const QString& username,const QString& password);
Login_Status Login(const QString&,const QString&);
void CreateEntry(const QString&,const QString&,const QString&);
QString retrieveUserName(const QString& username);

#endif // DATABASEQUERY_H
