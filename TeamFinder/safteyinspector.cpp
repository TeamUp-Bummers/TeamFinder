#include "safteyinspector.h"
#include "datahandler.h"
#include <regex>
#include <iomanip>
#include <openssl/sha.h>
#include <sstream>
#include <random>


// Check if Username Exists in The Database
bool UserNameMatches(const QString& username){

    QString query_username = RetrieveUserNameIfExists(username);
    return (query_username == username)? true : false;
};
// Make Login
Login_Status Login(const QString& username, const QString& password){
    if(!UserNameMatches(username)) return NO_ACCOUNT;
    if(!passwordMatch(username,password)) return ACCESS_DENIED;
    return ACCESS_GRANTED;

}

//Check Password Pattern
bool isValidPassword(const QString &password){
    std::regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=\\S+$).{8,}");
    if(std::regex_match(password.toStdString(),pattern)) return true;
    return false;
};

// Check if 2 Password Matches
bool passwordMatches(const QString &password, const QString& confirm_password)
{
    if(password == confirm_password) return true;
    return false;
}

/*
    Function for user registration
    - Check if the provided username already exists
    - Check if the provided passwords match and meet the strength criteria
    - Generate a salt for password hashing
    - Call the CreateEntry function to insert the new user into the database
    - Return the appropriate registration status
*/
Registration_Status MakeRegistration(const QString &username, const QString &password, const QString& confirmPassword , const QString& UniqueKey)
{

    if(!(UserNameMatches(username))){
        if(passwordMatches(password,confirmPassword)){
            if(isValidPassword(password)){
                QString password_salt = GenerateSalt();
                CreateEntry(username,HashFunction(password+password_salt),password_salt,HashFunction(UniqueKey));
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



/* Password Security Functions*/

// Generate Salt For Password
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

/*
    Function to compute the SHA-256 hash of a given password
    - Convert the QString password to a std::string
    - Initialize an SHA256_CTX context
    - Update the context with the password data
    - Finalize the hash and store it in the hash array
    - Convert the hash to a hexadecimal string and store it in a stringstream
    - Convert the stringstream to a QString and return the hashed text
*/
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
    return hashed_text;

};
// Check if User profile is filled or not
bool IsDataFilled(){
    ProfileData* profileData =  RetrieveData(CurrentUser);
    bool isValid = !(profileData->discord_tag.isEmpty() || profileData->email.isEmpty() || profileData->game_name.isEmpty() || profileData->game_rank.isEmpty() || profileData->playtime.isEmpty() || profileData->profile_description.isEmpty());
    if(isValid) return true;
    return false;
}

