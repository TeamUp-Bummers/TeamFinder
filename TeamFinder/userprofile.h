#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QMainWindow>
#include <QMessageBox>
#include"changepassword.h"
namespace Ui {
class UserProfile;
}

class UserProfile : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserProfile(QWidget *parent = nullptr);
    ~UserProfile();

protected:

    void showEvent(QShowEvent *event) override;


private slots:
    void on_pushButton_clicked();


    void on_GameID_currentTextChanged(const QString &arg1);

    void on_ProfileSave_clicked();

    void on_CancelOut_clicked();

private:
    Ui::UserProfile *ui;
};

#endif // USERPROFILE_H
