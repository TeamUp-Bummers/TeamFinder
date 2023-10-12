#include "databaseQuery.h"


void connectDatabase(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("XueHue123");
    db.setDatabaseName("teamfinder");

    if(db.open()){
        qDebug() << "Database is Connected";
    }else{
        qDebug() << "Database isnt Connected";
    }

}


QString retrieveUserName(const QString& username){
    QSqlQuery query;
    QString result;
    query.prepare("Select username From teamfinder.users WHERE username=(:username)");
    query.bindValue(":username",username);
    query.exec();
    if(query.next()){
        result = query.value(0).toString();
        return result;
    }
};


bool passwordMatch(const QString& username,const QString& password){

    QSqlQuery query;
    QString hash_password;
    QString password_salt;

    query.prepare("SELECT password,salt FROM teamfinder.users WHERE username=(:username)");
    query.bindValue(":username",username);
    query.exec();
    if(query.next()){
        hash_password = query.value(0).toString();
        password_salt = query.value(1).toString();
        if(hash_password == HashFunction(password+password_salt)) return true;
        return false;
    }
}




void CreateEntry(const QString & username, const QString & password,const QString& salt)
{
    QSqlQuery query;
    query.prepare("INSERT INTO teamfinder.users(username,password,salt) VALUES(:username,:password,:salt)");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":salt",salt);
    query.exec();
}

void updatePassword(const QString &password)
{

    QSqlQuery query;
    QString salt = GenerateSalt();
    query.prepare("UPDATE teamfinder.users SET password=(:password),salt=(:salt) WHERE username=(:username)");
    query.bindValue(":password",HashFunction(password+salt));
    query.bindValue(":salt",salt);
    query.bindValue(":username",CurrentUser);
    query.exec();

}

QStringList RetrieveRanks(const QString &game){
    QSqlQuery query;
    QStringList result;

    if(game == "Valorant"){
        query.prepare("SELECT * FROM teamfinder.valorantranks");
    }else if(game == "Counter Strike"){
        query.prepare("SELECT * FROM teamfinder.csgoranknames");
    }
    query.exec();
    while(query.next()){
        result << query.value(0).toString();
    }

    return result;
};

void  UpdateUserName(const QString& username){

    QSqlQuery query_first;
    QSqlQuery query_second;
//    query.prepare("UPDATE teamfinder.users SET username=(:username) WHERE username=(:current_username)");
//    query.bindValue(":username",username);
//    query.bindValue(":current_username",CurrentUser);
//    query.exec();
    query_first.prepare("UPDATE teamfinder.users SET username=(:username) WHERE username=(:current_username)");
    query_second.prepare("UPDATE teamfinder.profile_data SET username=(:username) WHERE username=(:current_username)");
    query_first.bindValue(":username",username);
    query_first.bindValue(":current_username",CurrentUser);
    if(query_first.exec()){
        query_second.bindValue(":username",username);
        query_second.bindValue(":current_username",CurrentUser);
        query_second.exec();
    }


}

void UpdateProfile(const QString& game, const QString& rank, const QString& profile_description,int playtime){

    QSqlQuery query;
    query.prepare("INSERT INTO teamfinder.profile_data (username,profile_description,game_name,game_rank,playtime)"
                  " VALUES(:username,:profile_description,:game_name,:game_rank,:playtime)"
                  "ON DUPLICATE KEY UPDATE "
                  " game_name=(:game_name),game_rank=(:game_rank),profile_description=(:profile_description),playtime=(:playtime)"
                  );
    qDebug() << CurrentUser << profile_description << game << rank << playtime;
    query.bindValue(":username",CurrentUser);
    query.bindValue(":profile_description",profile_description);
    query.bindValue(":game_name",game);
    query.bindValue(":game_rank",rank);
    query.bindValue(":playtime",playtime);
    query.exec();

};

ProfileData* RetrieveData(){

    QSqlQuery query;
    query.prepare("SELECT game_name,game_rank,profile_description,playtime FROM teamfinder.profile_data WHERE username=(:username)");
    query.bindValue(":username",CurrentUser);
    query.exec();
    ProfileData* current_user = new ProfileData();
    if(query.next()){
        current_user->game_name = query.value(0).toString();
        current_user->game_rank = query.value(1).toString();
        current_user->profile_description = query.value(2).toString();
        current_user->playtime = query.value(3).toString();
    }
    return current_user;
};
