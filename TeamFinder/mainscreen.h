#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include "userprofile.h"

struct LobbyData{
    QString username;
    QString email;

};

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

    void on_pushButton_3_clicked();

    void on_game_currentTextChanged(const QString &arg1);

    void on_rank_currentTextChanged(const QString &arg1);

    void on_tableView_doubleClicked();

    void on_addToParty_clicked();

    void on_tableWidget_doubleClicked();

    void on_deleteUser_clicked();





private:
    Ui::Mainscreen *ui;
};

#endif // MAINSCREEN_H
