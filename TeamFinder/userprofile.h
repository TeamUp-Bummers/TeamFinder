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

private:
    Ui::UserProfile *ui;
};

#endif // USERPROFILE_H
