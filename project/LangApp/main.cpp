#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "seeder.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QtSql>
#include <QtWidgets>

int main(int argc, char* argv[])
{
    // Wyswietalnie okna
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //Tworzenie bazy danych i połączenie
    Seeder seeder{};
    QSqlDatabase db = seeder.initDb();
    int dels = seeder.DeleteTables();
    int tables = seeder.MakeTables();
    int langs = seeder.FillLangs();
    int words = seeder.FillWords();
    // do pomocy
    qDebug() << "Database started: " << db;
    qDebug() << "Deletions: " << dels;
    qDebug() << "Table creations: " << tables;
    qDebug() << "Language insertions: " << langs;
    qDebug() << "Words added: " << words;

    return a.exec();
}

