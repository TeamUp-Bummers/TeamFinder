#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

#include <QtDebug>
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QMessageBox>
#include "safteyinspector.h"
extern QString CurrentUser;


struct ProfileData{
    QString game_name;
    QString game_rank;
    QString profile_description;
    QString playtime;
    QString discord_tag;
    QString email;
};


struct ProfileData_Short{
    QString username;
    QString game_name;
    QString game_rank;
    QString playtime;

};

void connectDatabase();
bool passwordMatch(const QString& username,const QString& password);
Login_Status Login(const QString&,const QString&);
void CreateEntry(const QString&,const QString&,const QString&);
QString retrieveUserName(const QString& username);
void updatePassword(const QString& password);
QStringList RetrieveRanks(const QString& game);
void  UpdateUserName(const QString& username);
void UpdateProfile(const QString& game, const QString& rank, const QString& profile_description,int playtime,const QString& discord_tag,const QString& email);
ProfileData* RetrieveData();
QSqlQueryModel* RetrieveInformation();
QSqlQueryModel* Filter(const QString& game,const QString& rank="");
#endif // DATABASEQUERY_H
