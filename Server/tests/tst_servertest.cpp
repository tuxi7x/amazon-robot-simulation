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
    void test_productsInController();
    void test_ordersInController();
    void test_alreadyOrdered();
    void test_pauseSim();
    void test_resumeSim();
    void test_consumedEnergy();
    void test_robotBattery();

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


void ServerTest::test_productsInController()
{
    Controller c;
    c.addShelf(1,1);
    c.addProduct("alma", 0);
    QVERIFY(c.getProducts()[0]->getName() == "alma");
}
void ServerTest::test_ordersInController()
{
    Controller c;
    c.addShelf(1,1);
    c.addProduct("alma", 0);
    c.addOrder("alma");
    QVERIFY(c.getOrders()[0] == "alma");
}

void ServerTest::test_alreadyOrdered()
{
    Controller c;
    c.alreadyOrdered("alma");
    c.alreadyOrdered("banan");

    QVERIFY(c.getAlreadyOrdered()[0] == "alma");
    QVERIFY(c.getAlreadyOrdered().size() == 2);

}

void ServerTest::test_pauseSim()
{
    Controller c;
    c.pauseSimulation();
    QVERIFY(c.getPaused() == true);
}
void ServerTest::test_resumeSim()
{
    Controller c;
    c.resumeSimulation();
    QVERIFY(c.getPaused() == false);
}

void ServerTest::test_consumedEnergy()
{
    Controller c;
    c.addRobot(1,1,0);
    QVERIFY(c.getRobots()[0]->getConsumedEnergy() == 0);
    QVERIFY(c.sumConsumedEnergy() == 0);
}
void ServerTest::test_robotBattery()
{
    Controller c;
    c.addRobot(1,1,0);
    QVERIFY(c.getRobots()[0]->getBattery() == 100);
    c.getRobots()[0]->setBattery(50);
    QVERIFY(c.getRobots()[0]->getBattery() == 50);
}


QTEST_APPLESS_MAIN(ServerTest)

#include "tst_servertest.moc"
