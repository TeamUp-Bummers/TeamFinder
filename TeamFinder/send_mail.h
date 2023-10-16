#ifndef SEND_MAIL_H
#define SEND_MAIL_H

#include <QDialog>

namespace Ui {
class send_mail;
}

class send_mail : public QDialog
{
    Q_OBJECT

public:
    explicit send_mail(QWidget *parent = nullptr);
    ~send_mail();
protected:
    void showEvent(QShowEvent *event) override;
private slots:


    void on_sendInvite_clicked();

private:
    Ui::send_mail *ui;
};

#endif // SEND_MAIL_H
