#ifndef SAFTEYINSPECTOR_H
#define SAFTEYINSPECTOR_H

#include <QString>

enum Registration_Status{
    ALREADY_EXISTS,
    REGISTERED,
    WEAK_PASSWORD,
    DIDNT_MATCH
};


bool isValidPassword(const QString& password);
bool passwordMatches(const QString& password,const QString& confirm_password);
Registration_Status MakeRegistration(const QString&,const QString&,const QString&);



#endif // SAFTEYINSPECTOR_H
