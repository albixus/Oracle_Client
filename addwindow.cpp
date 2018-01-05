#include "addwindow.h"
#include "ui_addwindow.h"

addWindow::addWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWindow)
{
    ui->setupUi(this);
}

addWindow::~addWindow()
{
    delete ui;
}

void addWindow::on_buttonBox_accepted()
{

}

void addWindow::on_buttonBox_rejected()
{

}
