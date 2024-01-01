#ifndef FORGOT_PASSWORD_H
#define FORGOT_PASSWORD_H

#include <QDialog>

namespace Ui {
class forgot_password;
}

class forgot_password : public QDialog
{
    Q_OBJECT

public:
    explicit forgot_password(QWidget *parent = nullptr);
    ~forgot_password();

private slots:
    void on_pushButton_clicked();

    void on_passwordView_clicked();

    void on_passwordView_2_clicked();

private:
    Ui::forgot_password *ui;
};

#endif // FORGOT_PASSWORD_H
