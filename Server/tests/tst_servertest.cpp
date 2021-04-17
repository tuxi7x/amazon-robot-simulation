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
    void test_controller_constructor();
    void test_model_constructors();

};

ServerTest::ServerTest()
{

}

ServerTest::~ServerTest()
{

}

void ServerTest::test_controller_constructor()
{
    Controller c;
    QVERIFY(c.getDockers().isEmpty());
    QVERIFY(c.getDropOffPoints().isEmpty());
    QVERIFY(c.getRobots().isEmpty());
    QVERIFY(c.getOrders().isEmpty());
    QVERIFY(c.getShelves().isEmpty());
    QVERIFY(c.getProducts().isEmpty());
    c.setSize(2);
    c.setSpeed(3);

    QVERIFY(c.getSize() == 2);
    QVERIFY(c.getSpeed() == 3);
}

void ServerTest::test_model_constructors()
{
    Docker* docker = new Docker(2,3);
    QVERIFY(docker->getRow() == 2);
    QVERIFY(docker->getCol() == 3);

    DropOffPoint* dropoff = new DropOffPoint(4,5,"alma");
    QVERIFY(dropoff->getRow() == 4);
    QVERIFY(dropoff->getCol() == 5);
    QVERIFY(dropoff->getProduct() == "alma");

    Product* product = new Product("alma", 0);
    QVERIFY(product->getName() == "alma");
    QVERIFY(product->getShelf() == 0);

    Robot* robot = new Robot(2,6,1);
    QVERIFY(robot->getRow() == 2);
    QVERIFY(robot->getCol() == 6);
    QVERIFY(robot->getDirection() == 1);
    QVERIFY(robot->getBattery() == 100);

    Shelf* shelf = new Shelf(1,4);
    QVERIFY(shelf->getRow() == 1);
    QVERIFY(shelf->getCol() == 4);
    QVERIFY(shelf->getIsAvailable());
}




QTEST_APPLESS_MAIN(ServerTest)

#include "tst_servertest.moc"
