#include <QtTest>
#include <QtWidgets>

// add necessary includes here

class FirstTest : public QObject
{
    Q_OBJECT


private slots:
    void test_case1();
    void test_case2();
    //void testGui();

};


void FirstTest::test_case1()
{
    /*
    QString str="Hello";
    QVERIFY(str.toUpper()=="HELLO");*/
}
void FirstTest::test_case2()
{/*
    QString str="Hello";
    QCOMPARE(str.toUpper(),QString("HELO"));*/
}
/*
void FirstTest::testGui()
{
    QLineEdit lineEdit;
    QTest::keyClicks(&lineEdit,"hello wordl");
    QCOMPARE(lineEdit.text(),QString("hello world"));
}
*/
QTEST_APPLESS_MAIN(FirstTest)

#include "tst_firsttest.moc"
