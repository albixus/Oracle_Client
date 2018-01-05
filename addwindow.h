#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>

namespace Ui {
class addWindow;
}

class addWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addWindow(QWidget *parent = 0);
    ~addWindow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::addWindow *ui;
};

#endif // ADDWINDOW_H
