#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QMainWindow>

namespace Ui {
class UserProfile;
}

class UserProfile : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserProfile(QWidget *parent = nullptr);
    ~UserProfile();

private:
    Ui::UserProfile *ui;
};

#endif // USERPROFILE_H
