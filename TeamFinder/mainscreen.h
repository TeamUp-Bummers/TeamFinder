#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include "userprofile.h"

namespace Ui {
class Mainscreen;
}

class Mainscreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainscreen(QWidget *parent = nullptr);
    ~Mainscreen();
protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Mainscreen *ui;
};

#endif // MAINSCREEN_H
