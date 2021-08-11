#ifndef WORDCOMPARE_H
#define WORDCOMPARE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <vector>
#include <QObject>
#include <QPixmap>

#include <algorithm>
#include <cctype>
#include <string>

class WordCompare : public QObject
{
    Q_OBJECT
public:
    explicit WordCompare(QObject *parent = nullptr);
    // Function that checks if translation is correct
    void checkCorrect(QString);
    void checkCorrectWord(QString);

public slots:
    // Function that assigns current language
    void assignValue(QString val);
    // Function that gets random word from DB
    void randomMaker();
    // Function that gets random picture from DB
    void picSelect();
    // Function that
    //void selectJpn();
    // Function that checks if Japan translation is correct
   // void checkJpn(QString);
    void selectTableName(QString s);

signals:
    void changed(QString);
    void correctWord(QString);
    void incorrectWord(QString);
    void correctPic(QString);
    void incorrectPic(QString);
    void picSelected(QPixmap);
  //  void jpnRanded(QString);
   // void jpnOk(QString);
   // void jpnNo(QString);


private:
    QString lang;
    int id;
    QString word;
    int app;
    QString tableName;
    int current_photo_id;
};

#endif // WORDCOMPARE_H
