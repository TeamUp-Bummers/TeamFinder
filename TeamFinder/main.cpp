#include "mainwindow.h"
#include <QApplication>
#include "datahandler.h"



/*
    Main function to run the application
    Create a QApplication instance with the given arguments
    Set the application window icon
    Create a MainWindow instance
    Show the MainWindow
    Connect to the database using the connectDatabase function
    Execute the application event loop
*/



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/rsc/game.ico"));
    MainWindow w;
    w.show();

    connectDatabase();
    return a.exec();
}
