#ifndef VIEWPROFILE_H
#define VIEWPROFILE_H

#include <QDialog>

namespace Ui {
class ViewProfile;
}

class ViewProfile : public QDialog
{
    Q_OBJECT

public:
    explicit ViewProfile(const QString& username,QWidget *parent = nullptr);

    ~ViewProfile();
protected:

    void showEvent(QShowEvent *event) override;
private:
    QString username;
    Ui::ViewProfile *ui;
};

#endif // VIEWPROFILE_H
