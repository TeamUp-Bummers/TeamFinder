#include "mainwindow.h"
#include <QApplication>
#include "datahandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/rsc/game.ico"));
    MainWindow w;
    w.show();

    connectDatabase();
    return a.exec();
}
