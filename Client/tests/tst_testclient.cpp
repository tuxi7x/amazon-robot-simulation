#include <QtTest>
#include "../controllers/MapEditorController.h"
#include <QSignalSpy>

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
    void test_fieldIsEmpty();
    void test_validateBeforeSaveChecksRobots();
    void test_validateBeforeSaveChecksShelfs();
    void test_validateBeforeSaveChecksProducts();
    void test_validateBeforeSaveChecksDockers();
    void test_validateBeforeSaveChecksDropOffs();
    void test_validateBeforeSaveChecksIfOK();
    void test_ordersGet();
    void test_ordersSet();
    void test_ifFieldChangedSignalEmitted();
    void test_ifMapCreatedSignalEmitted();

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

void TestClient::test_fieldIsEmpty()
{
    MapEditorController m;
    m.createNewMap(10);
    m.fieldIsEmpty();
}

void TestClient::test_validateBeforeSaveChecksRobots()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addShelf(2,1);
    m.addDocker(3,1);
    m.addProduct(2,1,"alma");
    m.addDropOffPoint(4,1,"alma");
    QVERIFY(m.validateBeforeSave() != "OK");
}
void TestClient::test_validateBeforeSaveChecksShelfs()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addRobot(1,1);
    m.addDocker(3,1);
    m.addDropOffPoint(4,1,"alma");
    QVERIFY(m.validateBeforeSave() != "OK");
}
void TestClient::test_validateBeforeSaveChecksProducts()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addRobot(1,1);
    m.addShelf(2,1);
    m.addDocker(3,1);
    m.addDropOffPoint(4,1,"alma");
    QVERIFY(m.validateBeforeSave() != "OK");
}
void TestClient::test_validateBeforeSaveChecksDockers()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addRobot(1,1);
    m.addShelf(2,1);
    m.addProduct(2,1,"alma");
    QVERIFY(m.validateBeforeSave() != "OK");
}
void TestClient::test_validateBeforeSaveChecksDropOffs()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addRobot(1,1);
    m.addShelf(2,1);
    m.addDocker(3,1);
    m.addProduct(2,1,"alma");
    QVERIFY(m.validateBeforeSave() != "OK");
}
void TestClient::test_validateBeforeSaveChecksIfOK()
{
    MapEditorController m;
    m.createNewMap(10);
    m.addRobot(1,1);
    m.addShelf(2,1);
    m.addDocker(3,1);
    m.addProduct(2,1,"alma");
    m.addDropOffPoint(4,1,"alma");
    QVERIFY(m.validateBeforeSave() == "OK");
}
void TestClient::test_ordersGet()
{
    MapEditorController m;
    m.createNewMap(10);
    QVector<QString> t;
    t.append("alma");
    m.setOrders(t);
    QVERIFY(m.getOrders()[0] == "alma");
}
void TestClient::test_ordersSet()
{
    MapEditorController m;
    m.createNewMap(10);
    QVector<QString> t;
    t.append("alma");
    m.setOrders(t);
    QVERIFY(m.getOrders().size() == 1);
}

void TestClient::test_ifMapCreatedSignalEmitted()
{
    MapEditorController m;
    QSignalSpy spy(&m, SIGNAL(mapCreated()));
    m.createNewMap(10);
    QCOMPARE(spy.count(), 1);
}

void TestClient::test_ifFieldChangedSignalEmitted()
{
    MapEditorController m;
    m.createNewMap(10);
    QSignalSpy spy(&m, SIGNAL(fieldChanged(int,int)));
    m.addRobot(1,1);
    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toInt() == 1);
}


QTEST_APPLESS_MAIN(TestClient)

#include "tst_testclient.moc"
