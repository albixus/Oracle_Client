#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new dbMenagement();


    if(db->open())
        QMessageBox::about(this,"OK","Udało się nawiązać połączenie z baza");
    else
        QMessageBox::critical(this,"Błąd","Nie udało się nawiązać połączenia z baza");

    on_selectComboBox_currentIndexChanged(0);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,150);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,150);

    list = new QStringList();
    list->append("DANE O PASAZERACH KTORZY MAJA KUPIONY BILET POSORTOWANE ALFABETYCZNIE");
    list->append("DANE O PASAZERACH KTORZY WYJEZDZAJA ZE STACJI KIELCE");
    list->append("DANE O POLACZENIACH KTORE MAJA WSPOLNE PRZYSTANKI");
    list->append("DANE O PIERWSZYCH KLIENTACH CZYLI TAKICH CO KUPILI NAJWCZESNIEJ BILET");
    list->append("DANE O NAJSTARSZYM POCIAGU");
    list->append("ROCZNE ZESTAWIENIE ZAWIERAJACE ROK ILOSC PODROZY KTORE SIE ODBYLY W DANYM ROKU");
    list->append("ZESTAWIENIE ZAWIERAJACE NAZWE POCIAGU ORAZ LICZBE JEGO PRACOWNIKOW");
    list->append("ZESTAWIENIE ZAWIERAJACE NAJPOPULARNIEJSZE POLACZENIE");
    list->append("NAJLEPIEJ ZARABIAJACY PRACOWNIK PRACUJACY W POCIAGU KTOREGO NAZWA KONCZY SIE NA LITERE A");
    list->append("ZESTAWIENIE POKAZUJACE ILOSC KURSOW W OSTATNIM MIESIACU");

    model = new QStringListModel();

    model->setStringList(*list);
    ui->listView_queries->setModel(model);

    curr_tab = (current_table)ui->selectComboBox->currentIndex();
    delete list;
    //db->drop_all_tables();
    //db->create_tables();
    //db->create_sequences();
    //QMessageBox::about(this,"HURRA","ok");
}

MainWindow::~MainWindow()
{
    delete db;
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    //opening add dialog
    addWindow *add_win = new addWindow(db,this);
    add_win->setModal(false);
    add_win->exec();
    query_string = add_win->get_query_string();

    if(!add_win->is_canceled)
        if(db->query_execute(query_string))
            QMessageBox::about(this,"OK","Udało się dodać pozycję do bazy");
        else
            QMessageBox::critical(this,"Błąd","Nie udało się dodać do bazy");

    refresh_tab_view(curr_tab);

    delete add_win;
}

void MainWindow::on_selectComboBox_currentIndexChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery query;
    switch(index)
    {
    case 0:
        query = db->select_query_execute("SELECT * FROM Pasazer");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 1:
        query = db->select_query_execute("SELECT * FROM Pracownik");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 2:
        query = db->select_query_execute("SELECT * FROM Pociag");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 3:
        query = db->select_query_execute("SELECT * FROM Stacja");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 4:
        query = db->select_query_execute("SELECT * FROM Polaczenie");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 5:
        query = db->select_query_execute("SELECT * FROM Bilet");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;
    }

    curr_tab =(current_table)index;
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{}

void MainWindow::on_updateButton_clicked()
{
    updateWindow *update_win = new updateWindow(db,this);
    update_win->setModal(false);
    update_win->exec();
    query_string = update_win->get_query_string();

    if(!update_win->is_canceled)
        if(db->query_execute(query_string))
            QMessageBox::about(this,"OK","Modyfikacja danych powiodła się!");
        else
            QMessageBox::critical(this,"Błąd!","Modyfikacja danych nie powiodła się!");


    refresh_tab_view(curr_tab);
    delete update_win;
}

void MainWindow::on_deleteButton_clicked()
{
    deleteWindow *del_win = new deleteWindow(db,this);
    del_win -> setModal(false);
    del_win ->exec();

    query_string = del_win->get_query_string();

    if(db->query_execute(query_string))
        QMessageBox::about(this,"OK","Modyfikacja danych powiodła się!");
    else
        QMessageBox::critical(this,"Błąd!","Modyfikacja danych nie powiodła się!");


    refresh_tab_view(curr_tab);
}

void MainWindow::on_listView_queries_clicked(const QModelIndex &index)
{
    int current_index = index.row();
    QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel();

    switch (current_index)
    {
    case 0:
        query_string = "SELECT DISTINCT p.imie,p.nazwisko,p.numer_telefonu \
                FROM Pasazer p, Bilet b \
                WHERE p.ID_Pasazer(+) = b.ID_Pasazer \
                ORDER BY p.nazwisko ASC, p.imie ASC";
        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;
    case 1:
        query_string = "SELECT DISTINCT p.imie,p.nazwisko,p.numer_telefonu, pol.MIEJSCE_WYJAZDU \
                FROM Pasazer p, Bilet b, Polaczenie pol \
                WHERE p.ID_Pasazer (+) = b.ID_Pasazer \
                AND b.ID_Polaczenie = pol.ID_Polaczenie \
                AND pol.MIEJSCE_WYJAZDU LIKE 'Kielce'";

        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;

    case 2:
        query_string = "SELECT DISTINCT pol.MIEJSCE_WYJAZDU, pol.MIEJSCE_DOCELOWE \
                FROM Polaczenie pol, Przystanek prz, Stacja s \
                WHERE pol.ID_Polaczenie = prz.ID_Polaczenie \
                AND s.ID_Stacja = prz.ID_Stacja";

        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;

    case 3:
        query_string = "SELECT p.imie, p.nazwisko, p.numer_telefonu, b.data_wyjazdu \
                FROM PASAZER p, Bilet b \
                WHERE p.ID_Pasazer = b.ID_Pasazer \
                AND b.Data_wyjazdu = (SELECT MIN(data_wyjazdu) FROM Bilet)";

        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;

    case 4:
        query_string = "SELECT * \
                FROM Pociag \
                WHERE DATA_PRODUKCJI = (SELECT MIN(Data_Produkcji) FROM Pociag)" ;

        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;

    case 5:
        query_string = "SELECT EXTRACT(YEAR FROM b.Data_Wyjazdu) AS ROK, COUNT(pol.ID_Polaczenie) AS Ilosc_Podrozy \
                FROM Bilet b, Polaczenie pol \
                WHERE b.ID_Polaczenie = pol.ID_Polaczenie \
                GROUP BY EXTRACT(YEAR FROM b.Data_Wyjazdu)";

        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;

    case 6:
        query_string = "SELECT poc.NAZWA, COUNT(pr_poc.ID_Pracownik) \
                FROM Pociag poc, Pracownik pr, Pracownik_Pociagu pr_poc \
                WHERE poc.ID_Pociag = pr_poc.ID_Pociag \
                AND pr.ID_Pracownik = pr_poc.ID_Pracownik \
                GROUP BY poc.Nazwa";

        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;

    case 7:
        query_string = "SELECT DISTINCT pol.MIEJSCE_DOCELOWE, pol.MIEJSCE_WYJAZDU,bcount AS Ilosc \
                FROM Polaczenie pol, Bilet b, ( \
                    SELECT pol3.ID_POLACZENIE, COUNT(b3.ID_Bilet)bcount \
                    FROM Bilet b3, Polaczenie pol3 \
                    WHERE pol3.ID_Polaczenie = b3.ID_Polaczenie \
                    GROUP BY b3.ID_Polaczenie) my \
                WHERE pol.ID_Polaczenie = b.ID_Polaczenie \
                AND ( \
                    SELECT MAX(COUNT(b2.ID_Bilet)) \
                    FROM Bilet b2, Polaczenie pol2 \
                    WHERE pol2.ID_Polaczenie = b2.ID_Polaczenie \
                    GROUP BY b2.ID_Polaczenie \
                    ) = my.bcount \
                AND my.ID_POLACZENIE = pol.ID_POLACZENIE";

        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;

    case 8:
        query_string = "SELECT pra.imie, pra.NAZWISKO, pra.PENSJA \
                FROM Pracownik pra \
                WHERE pra.PENSJA = (SELECT MAX(PENSJA) \
                    FROM Pracownik,Pracownik_Pociagu pra_poc ,Pociag poc \
                    WHERE Pracownik.ID_Pracownik = pra_poc.ID_Pracownik \
                    AND poc.ID_Pociag = pra_poc.ID_Pociag \
                    AND poc.Nazwa LIKE '%a')";

        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;

    case 9:
        query_string = "SELECT EXTRACT(MONTH FROM b.Data_wyjazdu) AS Miesiac, \
                EXTRACT(YEAR FROM b.Data_wyjazdu) AS ROK, \
                COUNT(pol.ID_Polaczenie) AS Ilosc_Kursow \
            FROM Polaczenie pol, Bilet b \
            WHERE pol.ID_Polaczenie (+) = b.ID_Polaczenie \
            AND EXTRACT(MONTH FROM b.Data_Wyjazdu) = EXTRACT(MONTH FROM sysdate) \
            AND EXTRACT(YEAR FROM b.Data_Wyjazdu) = EXTRACT(YEAR FROM sysdate) \
            GROUP BY EXTRACT(MONTH FROM b.data_wyjazdu), EXTRACT(YEAR FROM b.Data_Wyjazdu)";

        query = db->select_query_execute(query_string);
        model->setQuery(query);
        ui->tableView_qdvanced_queries->setModel(model);
        break;
    default:
        break;
    }
}

void MainWindow::refresh_tab_view(int index)
{
    QSqlQuery query;
    QSqlQueryModel *query_model = new QSqlQueryModel();

    switch(index)
    {
    case PASSENGER:
        query = db->select_query_execute("SELECT * FROM PASAZER");
        query_model->setQuery(query);
        ui->tableView->setModel(query_model);
        break;

    case WORKER:
        query = db->select_query_execute("SELECT * FROM Pracownik");
        query_model->setQuery(query);
        ui->tableView->setModel(query_model);
        break;

    case TRAIN:
        query = db->select_query_execute("SELECT * FROM Pociag");
        query_model->setQuery(query);
        ui->tableView->setModel(query_model);
        break;

    case STATION:
        query = db->select_query_execute("SELECT * FROM Stacja");
        query_model->setQuery(query);
        ui->tableView->setModel(query_model);

        break;

    case CONNECTION:
        query = db->select_query_execute("SELECT * FROM Polaczenie");
        query_model->setQuery(query);
        ui->tableView->setModel(query_model);
        break;

    case TICKET:
        query = db->select_query_execute("SELECT * FROM Bilet");
        query_model->setQuery(query);
        ui->tableView->setModel(query_model);
        break;
    }
}
