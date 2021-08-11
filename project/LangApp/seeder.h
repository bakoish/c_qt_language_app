#ifndef SEEDER_H
#define SEEDER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <vector>
#include <QtSql>
#include <QtWidgets>

class Seeder
{
public:
    Seeder();
    QSqlDatabase initDb();
    int MakeTables();
    int DeleteTables();
    int FillLangs();
    int FillWords();
private:
    std::vector<QString> langs;
    std::vector<QString> PolishWords;
    std::vector<QString> EnglishWords;
    std::vector<QString> DeutschWords;
    std::vector<QString> imageNames;

};

#endif // SEEDER_H
