#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unistd.h>
#include <QtWidgets>
#include <vector>

#include "wordcompare.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void correct();
    void incorrect();
    void done();
    void error();

    void langChange(QString val);
   // void jpnPl(QString);



public slots:
    void assignValue(QString val);
    void picDisplay(QPixmap);


private slots:
    void on_WordCompare_clicked();
    void on_MainMenu_clicked();
    void on_EnglishBtn_clicked();
    void on_DeutschBtn_clicked();
//    void on_JapanBtn_clicked();
    void on_CheckBtn1_clicked();
    void on_MainMenu_2_clicked();
    void on_CheckBtn2_clicked();
    void on_select_img_bt_clicked();

   // void on_jpnMainMenu_clicked();
   // void on_jpnRand_clicked();

    void on_CheckBtn3_clicked();
    void on_listBtn_clicked();
    void on_createTestBtn_clicked();
    void on_backBtn_clicked();
    void on_add_img_bt_clicked();
    void on_pushButton_clicked();
    void on_list_tests();
    void on_start_test_clicked();
    void on_ImgBtn_clicked();

private:
    Ui::MainWindow *ui;
    WordCompare* wordCmp;
    QString word;
    QString lang;
    QString fileName;
    int idImg;
    int testId = 0;
    QVector<QRadioButton*> buttons;
};

#endif // MAINWINDOW_H
