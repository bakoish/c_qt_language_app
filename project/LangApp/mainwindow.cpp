#include "mainwindow.h"
#include "wordcompare.h"
#include "ui_mainwindow.h"
#include <QStateMachine>
#include <QDebug>
#include <QStackedWidget>
#include <QResource>
#include <QPixmap>
#include <QFileDialog>
#include <QtSql>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    wordCmp = new WordCompare();
    ui->setupUi(this);
    idImg=0;

    auto stateMachine = new QStateMachine(this);

    auto Startup = new QState(stateMachine);
    auto Lang = new QState(stateMachine);
    auto Checker = new QState(stateMachine);
    auto Edit = new QState(stateMachine);
    auto PicTest = new QState(stateMachine);
    auto picSelect = new QState(stateMachine);
    auto CreateTest = new QState(stateMachine);
    auto CreateTest_SelectPic = new QState(stateMachine);
    auto CreateTest_SelectTrans = new QState(stateMachine);
    auto CreateTest_Allset = new QState(stateMachine);
    auto SelectTest = new QState(stateMachine);



    //-----------------------------CONNECTS-------------------------------------------

    connect(this, SIGNAL(langChange(QString)), wordCmp, SLOT(assignValue(QString)));
    connect(ui->RandomWord, SIGNAL(clicked()), wordCmp, SLOT(randomMaker()));
    connect(ui->ImgBtn, SIGNAL(clicked()), wordCmp, SLOT(picSelect()));
    connect(wordCmp,SIGNAL(picSelected(QPixmap)),this,SLOT(picDisplay(QPixmap)));
    connect(wordCmp,SIGNAL(changed(QString)),this,SLOT(assignValue(QString)));
    connect(wordCmp,SIGNAL(changed(QString)),ui->ShowText,SLOT(setText(QString)));
    connect(wordCmp,SIGNAL(correctPic(QString)),ui->ImgAnswer,SLOT(setText(QString)));
    connect(wordCmp,SIGNAL(incorrectPic(QString)),ui->ImgAnswer,SLOT(setText(QString)));
    connect(wordCmp,SIGNAL(correctWord(QString)),ui->pbAnswer,SLOT(setText(QString)));
    connect(wordCmp,SIGNAL(incorrectWord(QString)),ui->pbAnswer,SLOT(setText(QString)));

    connect(SelectTest, SIGNAL(entered()), this, SLOT(on_list_tests()));
    connect(CreateTest_SelectPic,SIGNAL(entered()),this,SLOT(on_select_img_bt_clicked()));
    connect(ui->add_img_bt,SIGNAL(clicked(bool)),this,SLOT(on_add_img_bt_clicked()), Qt::UniqueConnection); //wyslanie zdj z testem


    //---------------------------TRANSITIONS--------------------------------------

    Startup->addTransition(this, SIGNAL(langChange(QString)), Lang);
    //Startup->addTransition(ui->JapanBtn, SIGNAL(clicked(bool)), Japan);

    Startup->addTransition(ui->createTestBtn, SIGNAL(clicked(bool)), CreateTest);
    Startup->addTransition(ui->listBtn, SIGNAL(clicked(bool)), SelectTest);
    CreateTest->addTransition(ui->select_img_bt, SIGNAL(clicked(bool)), CreateTest_SelectPic);
    CreateTest_SelectPic->addTransition(this, SIGNAL(error()),CreateTest);
    CreateTest_SelectPic->addTransition(this, SIGNAL(done()),CreateTest_SelectTrans);
    CreateTest_SelectTrans->addTransition(ui->text_createtest_transl,SIGNAL(textChanged()),CreateTest_Allset);


    CreateTest_Allset->addTransition(this,SIGNAL(done()),CreateTest);
    CreateTest_Allset->addTransition(this,SIGNAL(error()),CreateTest);

    //wyjscie
    CreateTest->addTransition(ui->backBtn, SIGNAL(clicked(bool)), Startup);
    CreateTest_SelectPic->addTransition(ui->backBtn, SIGNAL(clicked(bool)), Startup);
    CreateTest_SelectTrans->addTransition(ui->backBtn, SIGNAL(clicked(bool)), Startup);
    CreateTest_Allset->addTransition(ui->backBtn, SIGNAL(clicked(bool)), Startup);
    SelectTest->addTransition((ui->pushButton), SIGNAL(clicked(bool)), Startup);
    //--------------

    //Lang->addTransition(ui->JapanBtn, SIGNAL(clicked(bool)), Japan);
    Lang->addTransition(ui->WordCompare, SIGNAL(clicked(bool)), Checker);

    PicTest->addTransition(ui->MainMenu_2, SIGNAL(clicked(bool)), Startup);
    PicTest->addTransition(ui->ImgBtn, SIGNAL(clicked(bool)), picSelect);
    picSelect->addTransition(ui->MainMenu_2, SIGNAL(clicked(bool)), Startup);


    Checker->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Checker->addTransition(wordCmp, SIGNAL(changed(QString)), Edit);

    Edit->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);



    //-----------------------ASSIGN PROPERTY----------------------------------
    Startup->assignProperty(ui->stackedWidget,"currentIndex", 0);
    Startup->assignProperty(ui->WordCompare, "enabled", true);
    //Startup->assignProperty(ui->JapanBtn, "enabled", true);
    Lang->assignProperty(ui->WordCompare, "enabled", true);

    Checker->assignProperty(ui->CheckBtn1, "enabled", false);
    Checker->assignProperty(ui->RandomWord, "enabled", true);
    Checker->assignProperty(ui->pbAnswer, "enabled", false);
    Checker->assignProperty(ui->ShowText, "enabled", false);
    Checker->assignProperty(ui->TypeText, "enabled", false);
    Checker->assignProperty(ui->ShowText, "text", "Losowe słowo");
    Checker->assignProperty(ui->TypeText, "placeholderText","Twoja odpowiedź");

    Edit->assignProperty(ui->CheckBtn1, "enabled", true);
    Edit->assignProperty(ui->TypeText, "enabled", true);
    Edit->assignProperty(ui->TypeText, "placeholderText","Twoja odpowiedź");

    PicTest->assignProperty(ui->ImgAnswer, "text", "");
    PicTest->assignProperty(ui->picText, "enabled", false);
    PicTest->assignProperty(ui->CheckBtn2, "enabled", false);
    picSelect->assignProperty(ui->picText, "enabled", true);
    picSelect->assignProperty(ui->CheckBtn2, "enabled", true);



    CreateTest->assignProperty(ui->stackedWidget,"currentIndex", 5); //chyba nie trzeba
    CreateTest->assignProperty(ui->add_img_bt,"enabled",false);
    CreateTest->assignProperty(ui->text_createtest_transl,"enabled",false);

    CreateTest_SelectTrans->assignProperty(ui->text_createtest_transl,"enabled",true); //pic

    //CreateTest_SelectTrans->assignProperty(ui->add_img_bt,"enabled",true);

    CreateTest_Allset->assignProperty(ui->add_img_bt,"enabled",true);



    stateMachine->setInitialState(Startup);

    stateMachine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::assignValue(QString val)
{
    word = val;
}

void MainWindow::picDisplay(QPixmap pixmap)
{
    ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->setScaledContents(true);
}

void MainWindow::on_WordCompare_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_MainMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_EnglishBtn_clicked()
{
    lang = "English";
    emit langChange(lang);
}


void MainWindow::on_DeutschBtn_clicked()
{
    lang = "Deutsch";
    emit langChange(lang);
}


void MainWindow::on_CheckBtn1_clicked()
{
    wordCmp->checkCorrectWord(ui->TypeText->text());
}

void MainWindow::on_MainMenu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_CheckBtn2_clicked()
{
    wordCmp->checkCorrect(ui->picText->text());
}
/*
void MainWindow::on_jpnMainMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_jpnRand_clicked()
{
    ui->jpnRes->setText("");
    wordCmp->selectJpn();
}

void MainWindow::on_CheckBtn3_clicked()
{
    wordCmp->checkJpn(ui->jpnTranslate->text());
}
*/
void MainWindow::on_listBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_createTestBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->label_img_watch->clear();
}

void MainWindow::on_backBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_select_img_bt_clicked()
{
    fileName = nullptr;
    fileName = QFileDialog::getOpenFileName(
            this, tr("Open img file"),
            QDir::currentPath(),
            tr("Images (*.png *.jpg)"));

    QPixmap zdj(this->fileName);

    if (zdj.isNull()) {
        ui->text_createtest_transl->setPlainText("error");
        emit error();
        return;
    }

    ui->label_img_watch->setPixmap(zdj.scaled(221,221,Qt::KeepAspectRatio));
    ui->text_createtest_transl->setPlainText("podaj tłumaczenie...");
    emit done();
}
void MainWindow::on_add_img_bt_clicked()
{
    //SEND TO DATABASE
    qDebug() << "WYSYLANIE:";
    qDebug() << idImg << " idIMG";
    qDebug() << ui->testName->toPlainText() << " title";
    qDebug() << fileName << " fileName";
    qDebug() << ui->comboBox->currentIndex() << " Ang,Niem,Jap"; // 0-Angielski 1-Niemiecki , 2-Japoński
    qDebug() << ui->text_createtest_transl->toPlainText(); //tlumaczenie


    QSqlQuery query_test;
    int test_id;
    query_test.prepare("select id_test from Testy WHERE nazwa=:nazwa");
    query_test.bindValue(":nazwa", ui->testName->toPlainText());
    bool test_exists = false;
    query_test.exec();
    while (query_test.next()) {
        test_id = query_test.value(1).toInt();
        qDebug() << "Test znaleziony" << test_id;
        test_exists = true;
    }

    // jesli nie ma takiego testu to stworz wpis w bazie danych
    if(!test_exists){
        QSqlQuery query_test_create;
        query_test_create.prepare("INSERT INTO Testy(id_test, nazwa, id_jez)"
                            "VALUES (:id_test, :nazwa, :id_jez)");
        query_test_create.bindValue(":id_test", this->testId++);
        query_test_create.bindValue(":nazwa", ui->testName->toPlainText());
        query_test_create.bindValue(":id_jez", ui->comboBox->currentIndex() + 1);
        auto fill = query_test_create.exec();
        if(fill){
            test_id = this->testId - 1;
            qDebug() << "Test stworzony";
        } else {
            qDebug() << "Error tworzenie testu";
            ui->text_createtest_transl->setPlainText("error send during test creation");
            emit error();
        }
    }

    QSqlQuery query;

    query.prepare("INSERT INTO Obrazki(id_img, image, id_test, text, title)"
                        "VALUES (:id_img, :image, :id_test, :text, :title)");

    query.bindValue(":id_img", idImg);
    query.bindValue(":id_jez", idImg);

    QPixmap inPixmap(fileName);
    QByteArray inByteArray;
    QBuffer inBuffer( &inByteArray );
    inBuffer.open( QIODevice::WriteOnly );
    inPixmap.save( &inBuffer, "PNG" );

    qDebug() << "Obrazek dodawanie" << test_id;

    query.bindValue(":image", inByteArray);
    query.bindValue(":id_test", test_id);
    query.bindValue(":text", ui->text_createtest_transl->toPlainText());
    query.bindValue(":title", ui->testName->toPlainText());

    auto fill = query.exec();
    if (fill) {
        ui->label_img_watch->clear();
        ui->text_createtest_transl->clear();
        idImg++;
        emit done();
    }
    else {
        ui->text_createtest_transl->setPlainText("error send");
        emit error();
    }
}

void MainWindow::on_list_tests()
{
    QSqlQuery query;
    QListWidgetItem *it;
    buttons.clear();
    ui->listWidget_test->clear();

    query.prepare("Select id_test, nazwa FROM Testy");
    query.exec();
    QString name;
    QString id;
     while (query.next()) {
         id = query.value(0).toString();
         name = query.value(1).toString();
         qDebug() <<  name << " " << id;
         it = new QListWidgetItem(ui->listWidget_test);
         auto btn = new QRadioButton(name);
         ui->listWidget_test->setItemWidget(it, btn);
         buttons.insert(0, btn);
     }
}

void MainWindow::on_start_test_clicked()
{
    for(const auto iterator : buttons){
         if(iterator->isChecked()){
             wordCmp->selectTableName(iterator->text());
             qDebug() << "Test: "<<iterator->isChecked() << iterator->text();
         }
    }
    ui->stackedWidget->setCurrentIndex(3);
}
