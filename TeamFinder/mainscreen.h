#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>

namespace Ui {
class Mainscreen;
}

class Mainscreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainscreen(QWidget *parent = nullptr);
    ~Mainscreen();


private:
    Ui::Mainscreen *ui;
};

#endif // MAINSCREEN_H