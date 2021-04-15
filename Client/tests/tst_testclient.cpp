#include <QtTest>
#include "../controllers/MapEditorController.h"

// add necessary includes here

class TestClient : public QObject
{
    Q_OBJECT

public:
    TestClient();
    ~TestClient();

private slots:
    void test_case1();

};

TestClient::TestClient()
{

}

TestClient::~TestClient()
{

}

void TestClient::test_case1()
{
    MapEditorController m;
    m.createNewMap(10);
    QVERIFY(m.getSize() == 10);
}

QTEST_APPLESS_MAIN(TestClient)

#include "tst_testclient.moc"
