#ifndef HISTORY_H
#define HISTORY_H
#include <QMap>
#include <QVector>

struct PlayerData {
    QString timestamp;
    QString username;
    QString email;
};


void SaveLobbyData();
QMap<QString, QVector<PlayerData>> RetrieveLobbyHistory();

void DeleteHistory();





#endif // HISTORY_H

