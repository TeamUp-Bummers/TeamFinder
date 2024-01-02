#define YAML_CPP_DLL
#include "datahandler.h"
#include <fstream>
#include <string>
#include <yaml-cpp/yaml.h>
/*
  Load YAML configuration file into a YAML::Node object
*/
YAML::Node config = YAML::LoadFile("config.yml");

/*
  Define a structure to hold database information
*/
struct DatabaseInformation{
    QString hostname; // Hostname or IP address of the database server
    QString username;  // Username for authenticating with the database
    QString password;   // Password for authenticating with the database
    QString database_name;// Name of the database to connect to
    int port_no;// Port number to use for the database connection
};

/*
    Function to establish a connection to a MySQL database using provided configuration
    Create an instance of DatabaseInformation to store login details
    Set database connection parameters from the configuration file
    Create a QSqlDatabase instance for MySQL and set connection parameters
    Attempt to open the database connection and print status
    Print a message if the database connection is successful
    Print a message if the database connection fails
    Clean up by deleting the login_info object
    Catch and print any exceptions that occur during the database connection process
*/

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
/*
    Function to retrieve a username from the database if it exists
    Create a QSqlQuery instance for executing SQL queries
    Declare a QString variable to store the query result
    Prepare an SQL query to select the username from the "users" table where the provided username matches
    Bind the provided username to the SQL query
    Execute the SQL query
    Check if the query returned any results
    If results exist, retrieve the first column's value (username) and store it in the 'result' variable
    Return the retrieved username (or an empty string if no match is found)
*/

QString RetrieveUserNameIfExists(const QString& username){
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


/*
    Function to check if the provided username exists and the corresponding password matches the stored hashed password
    Create a QSqlQuery instance for executing SQL queries
    Declare QString variables to store the hashed password and password salt from the database
    Prepare an SQL query to select the password and salt from the "users" table where the provided username matches
    Bind the provided username to the SQL query
    Execute the SQL query
    Check if the query returned any results
    If results exist, retrieve the hashed password and password salt
    Check if the provided password, combined with the salt and hashed, matches the stored hashed password
    Return true if the passwords match, otherwise return false
*/
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


/*
    Function to create a new entry in the "users" table with provided username, password, salt, and unique key
    Create a QSqlQuery instance for executing SQL queries
    Prepare an SQL query to insert values into the "users" table
    Bind the provided username, password, salt, and unique key to the SQL query
    Execute the SQL query to insert the new entry into the database
*/

void CreateEntry(const QString & username, const QString & password,const QString& salt, const QString& unique_key)
{
    QSqlQuery query;
    query.prepare("INSERT INTO teamfinder.users(username,password,salt,Unique_Key) VALUES(:username,:password,:salt,:Unique_Key)");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":salt",salt);
    query.bindValue(":Unique_Key",unique_key);
    query.exec();
}

/*
    Function to update the password and salt for a specific username in the "users" table
    Create a QSqlQuery instance for executing SQL queries
    Generate a new salt using the GenerateSalt() function
    Prepare an SQL query to update the password and salt in the "users" table
    Bind the hashed password (using HashFunction), salt, and username to the SQL query
    Execute the SQL query to update the password and salt for the specified username
*/

void updatePassword(const QString &password , const QString& username)
{

    QSqlQuery query;
    QString salt = GenerateSalt();
    query.prepare("UPDATE teamfinder.users SET password=(:password),salt=(:salt) WHERE username=(:username)");
    query.bindValue(":password",HashFunction(password+salt));
    query.bindValue(":salt",salt);
    query.bindValue(":username",username);
    query.exec();

}
/*
    Function to retrieve ranks for a specific game from the corresponding table in the database
    Create a QSqlQuery instance for executing SQL queries
    Declare a QStringList variable to store the query results
    Check the provided game parameter to determine the appropriate table
    Prepare an SQL query to select all columns from the corresponding ranks table
    Execute the SQL query
    Iterate through the query results and append each rank to the 'result' QStringList
    Return the QStringList containing the retrieved ranks
*/
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
/*
    Function to update the username in the "users" and "profile_data" tables for a specific user
    Create QSqlQuery instances for executing SQL queries for the "users" and "profile_data" tables
    Prepare SQL queries to update the username in the respective tables
    Bind the new username and the current username (CurrentUser) to the SQL queries
    Execute the first query to update the username in the "users" table
    If the first query is successful, execute the second query to update the username in the "profile_data" table
*/

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
/*
    Function to update or insert a user's profile information into the "profile_data" table
    Create a QSqlQuery instance for executing SQL queries
    Prepare an SQL query to insert or update values in the "profile_data" table
    Bind the current username (CurrentUser), profile description, game name, game rank, playtime, discord tag, and email to the SQL query
    Use ON DUPLICATE KEY UPDATE to handle insertion or update based on existing primary key (username)
    Execute the SQL query to update or insert the user's profile information
*/
void UpdateProfile(const QString& game, const QString& rank, const QString& profile_description,int playtime,const QString& discord_tag,const QString& email){

    QSqlQuery query;
    query.prepare("INSERT INTO teamfinder.profile_data (username,profile_description,game_name,game_rank,playtime,discord_tag,email)"
                  " VALUES(:username,:profile_description,:game_name,:game_rank,:playtime,:discord_tag,:email)"
                  "ON DUPLICATE KEY UPDATE "
                  " game_name=(:game_name),game_rank=(:game_rank),profile_description=(:profile_description),playtime=(:playtime),discord_tag=(:discord_tag),email=(:email)"
                  );
    query.bindValue(":username",CurrentUser);
    query.bindValue(":profile_description",profile_description);
    query.bindValue(":game_name",game);
    query.bindValue(":game_rank",rank);
    query.bindValue(":playtime",playtime);
    query.bindValue(":discord_tag",discord_tag);
    query.bindValue(":email",email);
    query.exec();

};
/*
    Function to retrieve user profile data from the "profile_data" table based on the provided username
    Create a QSqlQuery instance for executing SQL queries
    Prepare an SQL query to select specific columns from the "profile_data" table where the username matches
    Bind the provided username to the SQL query
    Execute the SQL query
    Create an instance of the ProfileData struct to store the retrieved data
    Check if the query returned any results
    If results exist, populate the ProfileData instance with values from the query
    Return the ProfileData instance containing the retrieved user profile data
*/
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

/*
    Function to retrieve filtered user information from the "profile_data" table for potential matches
    Create a QSqlQuery instance for executing SQL queries
    Create a QSqlQueryModel instance to store the query results for easy integration with Qt views
    Prepare an SQL query to select specific columns from the "profile_data" table
    Filter results to exclude rows with NULL values in certain columns and the current user's username
    Order the results randomly using ORDER BY RAND()
    Bind the current username (CurrentUser) to the SQL query
    Execute the SQL query
    Check if the query returned any results
    If results exist, set the query results in the QSqlQueryModel and return it
    If no results, return nullptr
*/

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


/*
    Function to filter and retrieve user information based on the provided game and rank criteria
    Create a QSqlQuery instance for executing SQL queries
    Create a QSqlQueryModel instance to store the query results for easy integration with Qt views
    Declare QString variables to construct the SQL query based on provided parameters
    Prepare an SQL query to select specific columns from the "profile_data" table
    Filter results to exclude rows with NULL values in certain columns and the current user's username
    Add additional conditions based on provided game and rank parameters
    Order the results randomly using ORDER BY RAND()
    Bind the current username (CurrentUser), game, and rank (if provided) to the SQL query
    Execute the SQL query
    Set the query results in the QSqlQueryModel and return it
*/

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

    model->setQuery(query);
    return model;
}
/*
    Function to retrieve specific profile data based on the provided column (string) and username
    Construct a SELECT statement to retrieve the specified column from the "profile_data" table
    Construct a WHERE condition to filter results based on the provided username
    Create a QSqlQuery instance for executing SQL queries
    Prepare an SQL query to select the specified column for the provided username
    Bind the provided username to the SQL query
    Execute the SQL query
    Check if the query returned any results
    If results exist, return the value of the specified column as a QString
*/

QString  GetSpecificProfileData(const QString &string,const QString& username)
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
/*
    Function to filter a given QAbstractItemModel by name using a QSortFilterProxyModel
    Create a QSortFilterProxyModel instance to act as a filter for the provided model
    Set the source model to the provided model
    Set filter properties for case insensitivity and key column
    Set the fixed string filter based on the provided searchFilter
    Return the QSortFilterProxyModel
*/

QSortFilterProxyModel *FilterByName(QAbstractItemModel *model, const QString &searchFilter)
{

    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterFixedString(searchFilter);

    return proxyModel;

}



/*
    Function to check if the provided unique key matches the one stored in the "users" table for a given username
    Create a QSqlQuery instance for executing SQL queries
    Prepare an SQL query to select the Unique_Key from the "users" table where the provided username matches
    Bind the provided username to the SQL query
    Execute the SQL query
    Check if the query returned any results
    If results exist, compare the provided unique key with the one retrieved from the query
    Return true if the unique keys match, otherwise return false
*/
bool UniqueKeyMatch(const QString &username, const QString &unique_key)
{
    QSqlQuery query;
    query.prepare("SELECT Unique_Key FROM teamfinder.users WHERE username=(:username)");
    query.bindValue(":username",username);
    query.exec();
    if(query.next()){
      return (unique_key == query.value(0).toString());
    }

}
