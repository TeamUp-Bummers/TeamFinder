#ifndef VIEWHISTORY_H
#define VIEWHISTORY_H

#include <QDialog>

namespace Ui {
class ViewHistory;
}

class ViewHistory : public QDialog
{
    Q_OBJECT

public:
    void UpdateTableData();
    explicit ViewHistory(QWidget *parent = nullptr);
    ~ViewHistory();
protected:

    void showEvent(QShowEvent *event) override;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tableWidget_cellDoubleClicked();

    void on_pushButton_3_clicked();

private:

    int index = 0;
    Ui::ViewHistory *ui;
};

#endif // VIEWHISTORY_H
