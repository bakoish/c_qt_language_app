#include "seeder.h"


Seeder::Seeder()
{
    langs = {"Polish", "English", "Deutsch", "Japan"};
    PolishWords = {"Kot","Pies",  "Bóbr", "Słoń", "Rekin", "Mysz", "Niedźwiedź", "Ptak", "Ryba","Pszczoła", "Lew", "Tygrys", "Małpa", "Bocian", "Mewa", "Krowa", "Kaczka", "Świnia", "Koń", "Osioł"};
    EnglishWords = {"Cat","Dog",  "Beaver", "Elephant", "Shark", "Mouse", "Bear", "Bird", "Fish","Bee", "Lion", "Tiger", "Monkey", "Stork", "Seagull", "Cow", "Duck", "Pig", "Horse", "Donkey"};
    DeutschWords = {"Katze","Hund",  "Biber", "Elefant", "Hai", "Maus", "Bär", "Vogel", "Fisch","Biene", "Löwe", "Tiger", "Affe", "Storch", "Möwe", "Kuh", "Ente", "Schwein","Pferd"," Esel"};
}

QSqlDatabase Seeder::initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("test");
    db.setPassword("test123");
    db.open();
    return db;
}

int Seeder::MakeTables()
{
    QSqlQuery query;
    // stworz wszystkie potrzebne tabele
    auto languages = query.exec("CREATE TABLE Jezyki(id_jez int PRIMARY KEY, nazwa VARCHAR)");
    auto tests = query.exec("CREATE TABLE Testy(id_test int PRIMARY KEY , nazwa VARCHAR, id_jez int REFERENCES Jezyki(id_jez))");
    auto words = query.exec("CREATE TABLE Slowa(id_sl int PRIMARY KEY, Polish VARCHAR, English VARCHAR, Deutsch VARCHAR, Japan VARCHAR)");
    auto images = query.exec("CREATE TABLE Obrazki(id_img int PRIMARY KEY, image BLOB, id_test int REFERENCES Testy(id_test), text VARCHAR, title VARCHAR)");
    qDebug() << "Creating languages table: " << (languages ? "SUCCESS" : "FAILED");
    qDebug() << "Creating tests table: " << (tests ? "SUCCESS" : "FAILED");
    qDebug() << "Creating words table: " << (words ? "SUCCESS" : "FAILED");
    qDebug() << "Creating images table: " << (images ? "SUCCESS" : "FAILED");
    return (languages + tests + words + images);
}

int Seeder::DeleteTables()
{
    QSqlQuery query;
    auto languages = query.exec("DROP TABLE Jezyki");
    auto categories = query.exec("DROP TABLE Testy");
    auto images = query.exec("DROP TABLE Obrazki");
    auto words = query.exec("DROP TABLE Slowa");

    return (languages + categories + words + images);
}


int Seeder::FillLangs()
{
    QSqlQuery query;
    int inserts = 0;

    for (int i = 1; i<=langs.size(); i++)
    {
        query.prepare("INSERT INTO Jezyki(id_jez, nazwa)" "VALUES (:id_jez, :nazwa)");
        query.bindValue(":id_jez", i);
        query.bindValue(":nazwa", langs[i-1]);
        auto fill = query.exec();
        if (fill)
            inserts++;
    }
    return inserts;
}

int Seeder::FillWords()
{
    QSqlQuery query;
    int inserts = 0;

    for (int i = 1; i<=PolishWords.size(); i++)
    {
        query.prepare("INSERT INTO Slowa(id_sl, Polish, English, Deutsch, Japan)" "VALUES (:id_sl, :pl, :ang, :niem, :jpn)");
        query.bindValue(":id_sl", i);
        query.bindValue(":pl", PolishWords[i-1]);
        query.bindValue(":ang", EnglishWords[i-1]);
        query.bindValue(":niem", DeutschWords[i-1]);
        auto fill = query.exec();
        if (fill)
            inserts++;
    }
    return inserts;
}

