#include "check.h"

check::check()
{
}

bool check::string_check(QString str)
{
    std::string stdstr = str.toStdString();
    for(unsigned int i =0; i<stdstr.size(); i++)
    {
        if(std::isdigit(stdstr.at(i)))
          return false;
    }
    return true;
}

bool check::is_string_number(QString str)
{
    std::string stdstr = str.toStdString();
    for(unsigned int i =0; i<stdstr.size(); i++)
    {
        if(std::isdigit(stdstr.at(i)))
          continue;
        return false;
    }
    return true;
}

void check::get_id_from_table(QModelIndex index, QString &id_string, QWidget *parent)
{
    if(index.column()==0)
        id_string = index.data().toString();
    else
        QMessageBox::about(parent,"Błąd","Zaznacz ID!");
}


