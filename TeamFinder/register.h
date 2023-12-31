#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>



namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_passwordView_clicked();

    void on_confirmPasswordView_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
