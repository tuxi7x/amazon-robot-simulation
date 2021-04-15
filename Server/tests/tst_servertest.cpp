#include <QtTest>
#include "Controller.h"

// add necessary includes here

class ServerTest : public QObject
{
    Q_OBJECT

public:
    ServerTest();
    ~ServerTest();

private slots:
    void test_case1();

};

ServerTest::ServerTest()
{

}

ServerTest::~ServerTest()
{

}

void ServerTest::test_case1()
{
    QVERIFY(1 != 2);
    QVERIFY(true);
    Controller c;
    c.setSize(10);
    QVERIFY(c.getSize() == 10);
}

QTEST_APPLESS_MAIN(ServerTest)

#include "tst_servertest.moc"
