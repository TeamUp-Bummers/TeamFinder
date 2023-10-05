#include "safteyinspector.h"
#include "databaseQuery.h"
#include <regex>




bool isValidPassword(const QString &password){
    std::regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=\\S+$).{8,}");
    if(std::regex_match(password.toStdString(),pattern)) return true;
    return false;
};

bool passwordMatches(const QString &password, const QString& confirm_password)
{
    if(password == confirm_password) return true;
    return false;
}

Registration_Status MakeRegistration(const QString &username, const QString &password, const QString& confirmPassword)
{

    if(!(userNameExists(username))){
        if(passwordMatches(password,confirmPassword)){
            if(isValidPassword(password)){
                CreateEntry(username,password);
                return REGISTERED;
            }else{
                return WEAK_PASSWORD;
            }
        }else{
            return DIDNT_MATCH;
        }

    }else{
        return ALREADY_EXISTS;
    }



}

