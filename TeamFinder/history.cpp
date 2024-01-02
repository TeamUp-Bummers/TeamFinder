#include <QFile>
#include <vector>
#include <QDateTime>
#include <QString>
#include <QVector>
#include <QMap>

#include "history.h"
#include "mainscreen.h"

/*
    Declaration of external variables
    - usercount: An integer representing the count of users
    - user_lobby: A vector of LobbyData representing user lobby information
    - CurrentUser: A QString representing the current user
*/
extern int usercount;
extern std::vector<LobbyData> user_lobby;
extern QString CurrentUser;


/*
    Function to save lobby data to a CSV file with a filename based on the current user and timestamp
    Generate a timestamp using the current date and time
    Create a QFile instance with a filename constructed from the current user and timestamp
    Open the file in WriteOnly, Text, and Append mode
    If the file opens successfully, create a QTextStream to write to the file
    Iterate through the user_lobby vector and write timestamp, username, and email to the file
    Close the file after writing data
    If the file cannot be opened, print an error message
*/


void SaveLobbyData()
{
     QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
     QFile file("lobbyHistory_"+CurrentUser+".csv");
     if(file.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Append)){

          QTextStream out(&file);

         for(int i=0;i<usercount;i++){
              out << timestamp <<","<<user_lobby[i].username << "," <<user_lobby[i].email <<"\n";
          }

     }else{
          qDebug() << "Could Not Open History File !";
     }
}

/*
    Function to retrieve lobby history from a CSV file based on the current user
    Create a QFile instance with a filename constructed from the current user
    Create a QVector<PlayerData> to store individual player data
    Create a QMap<QString, QVector<PlayerData>> to store lobby history data with timestamps as keys
    Open the file in ReadOnly and Text mode
    If the file opens successfully, create a QTextStream to read from the file
    Read each line from the file, split it into parts, and create a PlayerData object for each line
    Append each PlayerData object to the playerData vector
    Iterate through the playerData vector and organize the data into the lobbies map using timestamps as keys
    Close the file after reading data
    Return the lobbies map
*/

QMap<QString, QVector<PlayerData>> RetrieveLobbyHistory()
{
     QFile file("lobbyHistory_"+CurrentUser+".csv");
     QVector<PlayerData> playerData;
     QMap<QString, QVector<PlayerData>> lobbies;
     if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
         QTextStream input(&file);



         while(!input.atEnd()){
              QString line = input.readLine();
              QStringList parts = line.split(",");
              PlayerData player;
              player.timestamp = parts[0];
              player.username = parts[1];
              player.email = parts[2];
              playerData.append(player);


         }

         for (const PlayerData &player : playerData) {
              lobbies[player.timestamp].append(player);
         }

     }


     return lobbies;


}
/*
    Function to delete lobby history file for the current user
    Create a QFile instance with a filename constructed from the current user
    Resize the file to 0 to clear its content
*/

void DeleteHistory()
{
 QFile file("lobbyHistory_"+CurrentUser+".csv");
 file.resize(0);
}
