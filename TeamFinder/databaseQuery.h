#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

#include <QtDebug>
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <string>
#include <QString>
#include <QMessageBox>


void setDatabaseInformation();
QString checkCredentials(const QString&,const QString&);

#endif // DATABASEQUERY_H
