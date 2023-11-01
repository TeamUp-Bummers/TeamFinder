#include <QFile>
#include <vector>
#include <QDateTime>
#include <QString>
#include <QVector>
#include <QMap>

#include "history.h"
#include "mainscreen.h"


extern int usercount;
extern std::vector<LobbyData> user_lobby;
extern QString CurrentUser;




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

void DeleteHistory()
{
 QFile file("lobbyHistory_"+CurrentUser+".csv");
 file.resize(0);
}
