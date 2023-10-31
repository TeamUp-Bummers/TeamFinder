#ifndef SAFTEYINSPECTOR_H
#define SAFTEYINSPECTOR_H
#include <QString>
#include <string>
#include <QSortFilterProxyModel>


enum Registration_Status{
    ALREADY_EXISTS,
    REGISTERED,
    WEAK_PASSWORD,
    DIDNT_MATCH
};

enum Login_Status{
    NO_ACCOUNT,
    ACCESS_GRANTED,
    ACCESS_DENIED
};




bool isValidPassword(const QString& password);
bool passwordMatches(const QString& password,const QString& confirm_password);
Registration_Status MakeRegistration(const QString&,const QString&,const QString&);
QString HashFunction(const QString& password);
QString GenerateSalt();
bool UserNameMatches(const QString&);


QSortFilterProxyModel* FilterByName(QAbstractItemModel* model,const QString& searchFilter);



#endif // SAFTEYINSPECTOR_H
