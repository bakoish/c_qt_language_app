#include "wordcompare.h"

WordCompare::WordCompare(QObject *parent) : QObject(parent){}

void WordCompare::randomMaker()
{
    QSqlQuery query;
    QString b;

    query.prepare("select id_sl, Polish from Slowa WHERE id_sl >= (abs(random()) % (SELECT max(id_sl + 1) FROM Slowa)) limit 1");
    query.exec();
     while (query.next()) {
         id = query.value(0).toInt();
         b = query.value(1).toString();
         qDebug() <<  b;
     }
     app = 1;
     emit changed(b);
}

void WordCompare::selectTableName(QString s)
{
    this->tableName = s;
}

void WordCompare::picSelect()
{
    QSqlQuery query;
    QSqlQuery query2;
    QPixmap pixName;
    QString nazwa = this->tableName;
    int idd;
    // dane potrzebne
    QByteArray image;
    int img_id;
    qDebug() << "nazwa testu dla obrazka" << nazwa;

    query.prepare("select * from Testy where nazwa = :nazwa");
    query.bindValue(":nazwa", nazwa);
    query.exec();
    while (query.next()) {
         idd = query.value(0).toInt();
         query2.prepare("select * from Obrazki where id_test = :id order by random() limit 1");
         query2.bindValue(":id",idd);
         query2.exec();
         while (query2.next()) {
             qDebug() << "photo display" << query2.value(0);
             img_id  = query2.value(0).toInt();
             image = query2.value(1).toByteArray();
             pixName.loadFromData(image,"PNG");
        }
    }
    // do usunieci
    this->current_photo_id = img_id;
    app = 2;
    emit picSelected(pixName);
}
void WordCompare::checkCorrectWord(QString val){
    QSqlQuery query;
        QString b;
        if(lang == "English")
            query.prepare("select English from Slowa WHERE id_sl = :id ");
        if(lang == "Deutsch")
            query.prepare("select Deutsch from Slowa WHERE id_sl = :id ");
        if(lang == "Japan")
            query.prepare("select Japan from Slowa WHERE id_sl = :id ");
        query.bindValue(":id", id);

        query.exec();
        while (query.next()) {
            b = query.value(0).toString();
            qDebug() <<  b;
        }
        qDebug()<<val;

        if(!QString::compare(b, val, Qt::CaseInsensitive))
        {
            if (app == 1)
                emit correctWord("Brawo!");
            if (app == 2)
                emit correctPic("Brawo!");
        }
        else
        {
            if (app == 1)
                emit incorrectWord("Nie!");
            if (app == 2)
                emit incorrectPic("Nie!");
        }

}

void WordCompare::checkCorrect(QString val)
{
    QSqlQuery query;
    QSqlQuery query2;
    int idd;
    QString nazwa = this->tableName;
    QString title;
    QString text;

    query.prepare("select * from Testy where nazwa = :nazwa");
    query.bindValue(":nazwa", nazwa);
    query.exec();
    bool isFound = false;
    while (query.next() && !isFound) {
         idd = query.value(0).toInt();
         query2.prepare("select * from Obrazki where id_test = :id");
         query2.bindValue(":id",idd);
         query2.exec();
         while (query2.next() && !isFound) {
             auto id_img = query2.value(0).toInt();
             title = query2.value(4).toByteArray(); // nazwa testu
             text = query2.value(3).toByteArray(); // tłuamczenie
             qDebug() << "while" << text << "  " << title <<"val:" << val << "idimg" << id_img <<"current"<<this->current_photo_id;
             if(!QString::compare(text, val, Qt::CaseInsensitive) && id_img == this->current_photo_id)
             {
                 if (app == 1){
                     emit correctWord("Brawo!");
                     isFound = true;
                 }

                 if (app == 2){
                     emit correctPic("Brawo!");
                     isFound = true;
                 }
             }
        }
    }

    qDebug() << text << "  "<<val;

    if(!isFound){
        if (app == 1)
            emit incorrectWord("Nie!");
        if (app == 2)
            emit incorrectPic("Nie!");
    }
}

void WordCompare::assignValue(QString val)
{
    this->lang = val;
}
