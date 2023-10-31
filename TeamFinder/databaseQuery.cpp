#define YAML_CPP_DLL
#include "databaseQuery.h"
#include <fstream>
#include <string>
#include <yaml-cpp/yaml.h>

YAML::Node config = YAML::LoadFile("config.yml");
struct DatabaseInformation{
    QString hostname;
    QString username;
    QString password;
    QString database_name;
    int port_no;
};

void connectDatabase(){
    try{

        DatabaseInformation* login_info = new DatabaseInformation();

        login_info->database_name =QString::fromStdString(config["database"]["name"].as<std::string>());
        login_info->hostname = QString::fromStdString(config["database"]["hostname"].as<std::string>());
        login_info->username = QString::fromStdString(config["database"]["username"].as<std::string>());
        login_info->password = QString::fromStdString(config["database"]["password"].as<std::string>());
        login_info->port_no = config["database"]["port"].as<int>();

        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(login_info->hostname);
        db.setUserName(login_info->username);
        db.setPassword(login_info->password);
        db.setDatabaseName(login_info->database_name);
        db.setPort(login_info->port_no);
        if(db.open()){
            qDebug() << "Database is Connected";
        }else{
            qDebug() << "Database isnt Connected";
        }
        delete login_info;
    }catch(const std::exception& e){
        qDebug()<< "Error : " << e.what();
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

void UpdateProfile(const QString& game, const QString& rank, const QString& profile_description,int playtime,const QString& discord_tag,const QString& email){

    QSqlQuery query;
    query.prepare("INSERT INTO teamfinder.profile_data (username,profile_description,game_name,game_rank,playtime,discord_tag,email)"
                  " VALUES(:username,:profile_description,:game_name,:game_rank,:playtime,:discord_tag,:email)"
                  "ON DUPLICATE KEY UPDATE "
                  " game_name=(:game_name),game_rank=(:game_rank),profile_description=(:profile_description),playtime=(:playtime),discord_tag=(:discord_tag),email=(:email)"
                  );
    qDebug() << CurrentUser << profile_description << game << rank << playtime;
    query.bindValue(":username",CurrentUser);
    query.bindValue(":profile_description",profile_description);
    query.bindValue(":game_name",game);
    query.bindValue(":game_rank",rank);
    query.bindValue(":playtime",playtime);
    query.bindValue(":discord_tag",discord_tag);
    query.bindValue(":email",email);
    query.exec();

};

ProfileData* RetrieveData(const QString& username){

    QSqlQuery query;
    query.prepare("SELECT game_name,game_rank,profile_description,playtime,discord_tag,email FROM teamfinder.profile_data WHERE username=(:username)");
    query.bindValue(":username",username);
    query.exec();
    ProfileData* current_user = new ProfileData();
    if(query.next()){
        current_user->game_name = query.value(0).toString();
        current_user->game_rank = query.value(1).toString();
        current_user->profile_description = query.value(2).toString();
        current_user->playtime = query.value(3).toString();
        current_user->discord_tag = query.value(4).toString();
        current_user->email = query.value(5).toString();

    }
    return current_user;
};


QSqlQueryModel* RetrieveInformation()
{
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();
    query.prepare("SELECT username,game_name,game_rank,playtime FROM teamfinder.profile_data WHERE"
                  " NOT (game_name is NULL OR game_rank is NULL or playtime is NULL or profile_description is NULL OR playtime is NULL or email is NULL)"
                  " AND username<>(:username) ORDER BY RAND()");
    query.bindValue(":username",CurrentUser);
    query.exec();
    if(query.next()){
        model->setQuery(query);
        return model;
    }else{
        return nullptr;
    }

}

QSqlQueryModel* Filter(const QString& game,const QString& rank){
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();

    QString query_select="SELECT username,game_name,game_rank,playtime FROM teamfinder.profile_data";
    QString query_isValidCondition= " WHERE NOT (game_name is NULL OR game_rank is NULL or playtime is NULL or profile_description is NULL OR playtime is NULL or email is NULL) AND username<>(:username) ";
    QString query_gamefilter= " AND game_name=(:game)";
    QString query_rankfilter =" AND game_rank=(:rank)";
    QString query_limit = " ORDER BY RAND()";
    if(rank.isEmpty()){
        query.prepare(query_select+query_isValidCondition+query_gamefilter+query_limit);
    }else{
        query.prepare(query_select+query_isValidCondition+query_gamefilter+query_rankfilter+query_limit);
        query.bindValue(":rank",rank);
    }
    query.bindValue(":username",CurrentUser);
   query.bindValue(":game",game);
    query.exec();
   qDebug() << query.lastError();
    model->setQuery(query);
    return model;
}

QString  getParticularData(const QString &string,const QString& username)
{
    QString select_statement = "SELECT " + string +" FROM teamfinder.profile_data";
    QString condition = " WHERE username=(:username)";
    QSqlQuery query;
    query.prepare(select_statement+condition);
    query.bindValue(":username",username);
    query.exec();
    if(query.next()){
      return  query.value(0).toString();
    }


}


