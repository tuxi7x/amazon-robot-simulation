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
    void test_size();
    void test_addRobot();
    void test_addDocker();
    void test_addShelf();
    void test_addProduct();
    void test_testSelection();

};

TestClient::TestClient()
{

}

TestClient::~TestClient()
{

}

void TestClient::test_size()
{
    MapEditorController m;
    m.createNewMap(10);
    QVERIFY(m.getSize() == 10);
}

void TestClient::test_addRobot()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addRobot(1,1);
    QVERIFY(m.getField(1,1).first == MapEditorController::Robot);
}

void TestClient::test_addDocker()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addDocker(1,1);
    QVERIFY(m.getField(1,1).first == MapEditorController::Docker);
}

void TestClient::test_addShelf()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addShelf(1,1);
    QVERIFY(m.getField(1,1).first == MapEditorController::Shelf);
}

void TestClient::test_addProduct()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addShelf(1,1);
    m.addProduct(1,1,"alma");
    QString a = m.getProductsOnShelf(1,1).at(0);
    QVERIFY(a == "alma");
}

void TestClient::test_testSelection()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addShelf(1,1);
    m.toggleShelfSelection(qobject_cast<ShelfFieldModel*>(m.getField(1,1).second));
    QVERIFY(m.isASelectedShelf(1,1));
}

QTEST_APPLESS_MAIN(TestClient)

#include "tst_testclient.moc"
