#ifndef SAFTEYINSPECTOR_H
#define SAFTEYINSPECTOR_H
#include <QString>
#include <string>



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



Login_Status Login(const QString&,const QString&);
bool isValidPassword(const QString& password);
bool passwordMatches(const QString& password,const QString& confirm_password);
Registration_Status MakeRegistration(const QString&,const QString&,const QString&,const QString&);
QString HashFunction(const QString& password);
QString GenerateSalt();
bool IsDataFilled();
bool UserNameMatches(const QString&);
bool IsDataFilled();



#endif // SAFTEYINSPECTOR_H
