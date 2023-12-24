#include "mainwindow.h"
#include <QApplication>
#include "datahandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    connectDatabase();
    return a.exec();
}
