#include "safteyinspector.h"
#include "databaseQuery.h"
#include <regex>
#include <iomanip>
#include <openssl/sha.h>
#include <sstream>
#include <random>


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
                QString password_salt = GenerateSalt();
                CreateEntry(username,HashFunction(password+password_salt),password_salt);
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



};


QString HashFunction(const QString& password){

    std::string password_test = password.toStdString();
    SHA256_CTX sha256_context;
    SHA256_Init(&sha256_context);
    SHA256_Update(&sha256_context,password_test.c_str(),password_test.length());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash,&sha256_context);

    std::ostringstream hash_stream;
    for(int i=0;i<SHA256_DIGEST_LENGTH;i++){
        hash_stream<<std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    QString hashed_text = QString::fromStdString(hash_stream.str());

    qDebug() << hashed_text;
    return hashed_text;

};


QString GenerateSalt(){

    const int SALT_SIZE = 32;
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+[]{}|;:,.<>?/";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0,86);
    QString Salt;
    for(int i=0;i<SALT_SIZE;i++){
        Salt += charset[distrib(gen)];
    }
    return Salt;
};
