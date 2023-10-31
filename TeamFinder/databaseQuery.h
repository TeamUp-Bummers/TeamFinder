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

ProfileData* RetrieveData(const QString& username);
QSqlQueryModel* RetrieveInformation();
QSqlQueryModel* Filter(const QString& game,const QString& rank="");
QString getParticularData(const QString& string,const QString& username);
Login_Status Login(const QString&,const QString&);
QString retrieveUserName(const QString& username);
QStringList RetrieveRanks(const QString& game);

bool passwordMatch(const QString& username,const QString& password);


void connectDatabase();
void CreateEntry(const QString&,const QString&,const QString&);
void updatePassword(const QString& password);
void  UpdateUserName(const QString& username);
void UpdateProfile(const QString& game, const QString& rank, const QString& profile_description,int playtime,const QString& discord_tag,const QString& email);


#endif // DATABASEQUERY_H
