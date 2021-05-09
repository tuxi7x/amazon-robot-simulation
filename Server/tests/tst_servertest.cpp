#include <QtTest>
#include "Controller.h"
#include "QDebug"
#include "QSignalSpy"

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
    void test_consumedEnergy();
    void test_robotBattery();
    void test_ifRobotMoved();
    void test_robotBatteryAfterSim();
    void test_sumRobotBattery();
    void test_ordersAfterSim();
    void test_alreadyOrderedAfterSim();
    void test_productOnShelfAfterSim();
    void test_ifNearestRobotWent();
    void test_robotStateFree();
    void test_robotStateGoingForShelf();
    void test_moreRobots();
    void test_ifBatteryDecreased();
    void test_orderedFirstProduct();
    void test_orderedMiddleProduct();
    void test_moreProductsOnShelfIfFirstOrdered();
    void test_moreProductsOnShelfIfLastOrdered();
    void test_moreProductsOnShelfIfMiddleOrdered();
    void test_robotPathIsEmpty();
    void test_robotPathIsEmptyAfterSim();
    void test_ifProductDeliveredSignalEmitted();


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
void ServerTest::test_ifRobotMoved()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(2,2);
    c.addProduct("alma", 0);
    c.addDropOffPoint(3,3, "alma");
    c.addOrder("alma");
    QVERIFY(c.getOrders().size() == 1);
    c.addDocker(3,4);
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
         c.tickForTest();
    }
    QVERIFY(c.getRobots()[0]->getBattery() !=100);
}
void ServerTest::test_robotBatteryAfterSim()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    QVERIFY(c.getRobots()[0]->getBattery() == 100);
    c.addRobot(4,4,0);
    QVERIFY(c.getRobots()[1]->getBattery() == 100);
    c.addShelf(2,2);
    c.addProduct("alma", 0);
    c.addDropOffPoint(3,3, "alma");
    c.addOrder("alma");
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
         c.tickForTest();
    }
    QVERIFY(c.getRobots()[0]->getBattery() !=100);
    QVERIFY(c.getRobots()[1]->getBattery() == 100);

}
void ServerTest::test_sumRobotBattery()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    QVERIFY(c.getRobots()[0]->getConsumedEnergy() == 0);
    c.addRobot(4,4,0);
    QVERIFY(c.getRobots()[1]->getConsumedEnergy() == 0);
    c.addShelf(2,2);
    c.addProduct("alma", 0);
    c.addDropOffPoint(3,3, "alma");
    c.addOrder("alma");
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
         c.tickForTest();
    }
    QVERIFY(c.sumConsumedEnergy() > 0);
}

void ServerTest::test_ordersAfterSim()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(2,2);
    c.addProduct("alma", 0);
    c.addDropOffPoint(3,3, "alma");
    c.addOrder("alma");
    QVERIFY(c.getOrders().size() == 1);
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
          c.tickForTest();
    }
    QVERIFY(c.getOrders().size() == 0);
}

void ServerTest::test_ifNearestRobotWent()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    QVERIFY(c.getRobots()[0]->getConsumedEnergy() == 0);
    c.addRobot(6,6,0);
    QVERIFY(c.getRobots()[1]->getConsumedEnergy() == 0);
    c.addShelf(2,2);
    c.addProduct("alma", 0);
    c.addDropOffPoint(3,3, "alma");
    c.addOrder("alma");
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
          c.tickForTest();
    }
    QVERIFY(c.getRobots()[0]->getConsumedEnergy() > 0);
    QVERIFY(c.getRobots()[1]->getConsumedEnergy() == 0);
}
void ServerTest::test_alreadyOrderedAfterSim()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(2,2);
    c.addProduct("alma", 0);
    c.addDropOffPoint(3,3, "alma");
    c.addOrder("alma");
    c.alreadyOrdered("alma");
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
          c.tickForTest();
    }
    QVERIFY(c.getAlreadyOrdered().size() == 1);
}
void ServerTest::test_productOnShelfAfterSim()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(2,2);
    c.addProduct("alma", 0);
    c.addDropOffPoint(3,3, "alma");
    c.addOrder("alma");
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
          c.tickForTest();
    }
    int count = 0;
    for(int i = 0; i< c.getProducts().size(); i++){
        if(c.getProducts()[i]->getShelf() == 0){
            count++;
        }
    }
    QVERIFY(count == 0);
}
void ServerTest::test_robotStateFree()
{
    Controller c;
    c.addRobot(1,1,0);
    QVERIFY(c.getRobots()[0]->getState()== FREE);
}

void ServerTest::test_robotStateGoingForShelf()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(2,2);
    c.addProduct("alma", 0);
    c.addDropOffPoint(3,3, "alma");
    c.addOrder("alma");
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
          c.tickForTest();
          if(c.getRobots()[0]->getRow() != c.getShelves()[0]->getRow() && c.getRobots()[0]->getCol() != c.getShelves()[0]->getCol() && c.getProducts().size() != 0 && c.getRobots()[0]->getBattery() > 60){
              QVERIFY(c.getRobots()[0]->getState()== GOINGFORSHELF);
          }
    }
}
void ServerTest::test_moreRobots()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addRobot(1,2,0);
    c.addShelf(2,2);
    c.addShelf(2,3);
    c.addProduct("alma", 0);
    c.addProduct("banan", 1);
    c.addDropOffPoint(3,3, "alma");
    c.addDropOffPoint(3,4, "banan");
    c.addOrder("alma");
    c.addOrder("banan");
    c.addDocker(5,5);
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
          c.tickForTest();
    }
    QVERIFY(c.getRobots()[0]->getBattery() < 100);
    QVERIFY(c.getRobots()[1]->getBattery() < 100);
}

void ServerTest::test_ifBatteryDecreased()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(5,5);
    c.addProduct("alma", 0);
    c.addProduct("banan", 0);
    c.addDropOffPoint(1,2, "alma");
    c.addDropOffPoint(2,5, "banan");
    c.addOrder("alma");
    c.addOrder("banan");
    c.addDocker(2,1);
    int count = 101;
    int i = 0;
    int j = 0;
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
         c.tickForTest();
         if(i != c.getRobots()[0]->getRow() && j != c.getRobots()[0]->getCol()){
             i = c.getRobots()[0]->getRow();
             j = c.getRobots()[0]->getCol();
         if(c.getRobots()[0]->getRow() != c.getDropOffPoints()[0]->getRow() && c.getRobots()[0]->getRow() != c.getDropOffPoints()[0]->getCol()){
             QVERIFY(c.getRobots()[0]->getBattery() < count);
             count = c.getRobots()[0]->getBattery();
         }
         }

    }
}

void ServerTest::test_orderedFirstProduct()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(1,3);
    c.addProduct("alma", 0);
    c.addProduct("banan", 0);
    c.addDropOffPoint(2,2, "alma");
    c.addDropOffPoint(2,3, "banan");
    c.addOrder("alma");
    c.addDocker(2,1);
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 1)){
         c.tickForTest();
         }
    QVERIFY(c.getProducts()[0]->getName() == "banan");
}
void ServerTest::test_orderedMiddleProduct()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(1,3);
    c.addProduct("alma", 0);
    c.addProduct("banan", 0);
    c.addProduct("citrom",0);
    c.addDropOffPoint(2,2, "alma");
    c.addDropOffPoint(2,3, "banan");
    c.addDropOffPoint(2,4, "citrom");
    c.addOrder("banan");
    c.addDocker(2,1);
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 2)){
         c.tickForTest();
         }
    QVERIFY(c.getProducts()[0]->getName() == "alma");
    QVERIFY(c.getProducts()[1]->getName() == "citrom");
}


void ServerTest::test_moreProductsOnShelfIfFirstOrdered()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(1,3);
    c.addProduct("alma", 0);
    c.addProduct("banan", 0);
    c.addProduct("citrom",0);
    c.addDropOffPoint(2,2, "alma");
    c.addDropOffPoint(2,3, "banan");
    c.addDropOffPoint(2,4, "citrom");
    c.addOrder("banan");
    c.addDocker(2,1);
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 2)){
          c.tickForTest();
    }
    int count = 0;
    for(int i = 0; i< c.getProducts().size(); i++){
        if(c.getProducts()[i]->getShelf() == 0){
            count++;
        }
    }
    QVERIFY(count == 2);
}
void ServerTest::test_moreProductsOnShelfIfLastOrdered()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(1,3);
    c.addProduct("alma", 0);
    c.addProduct("banan", 0);
    c.addProduct("citrom",0);
    c.addDropOffPoint(2,2, "alma");
    c.addDropOffPoint(2,3, "banan");
    c.addDropOffPoint(2,4, "citrom");
    c.addOrder("citrom");
    c.addDocker(2,1);
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 2)){
          c.tickForTest();
    }
    int count = 0;
    for(int i = 0; i< c.getProducts().size(); i++){
        if(c.getProducts()[i]->getShelf() == 0){
            count++;
        }
    }
    QVERIFY(count == 2);
}

void ServerTest::test_moreProductsOnShelfIfMiddleOrdered()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(1,3);
    c.addProduct("alma", 0);
    c.addProduct("banan", 0);
    c.addProduct("citrom",0);
    c.addDropOffPoint(2,2, "alma");
    c.addDropOffPoint(2,3, "banan");
    c.addDropOffPoint(2,4, "citrom");
    c.addOrder("banan");
    c.addDocker(2,1);
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 2)){
          c.tickForTest();
    }
    int count = 0;
    for(int i = 0; i< c.getProducts().size(); i++){
        if(c.getProducts()[i]->getShelf() == 0){
            count++;
        }
    }
    QVERIFY(count == 2);
}
void ServerTest::test_robotPathIsEmpty()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(1,3);
    c.addProduct("alma", 0);
    c.addProduct("banan", 0);
    c.addProduct("citrom",0);
    c.addDropOffPoint(2,2, "alma");
    c.addDropOffPoint(2,3, "banan");
    c.addDropOffPoint(2,4, "citrom");
    c.addDocker(2,1);
    c.tickForTest();
    QVERIFY(c.getRobots()[0]->pathIsEmpty() == true);
}

void ServerTest::test_robotPathIsEmptyAfterSim()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(1,3);
    c.addProduct("alma", 0);
    c.addDropOffPoint(2,2, "alma");
    c.addDocker(2,1);
    c.addOrder("alma");
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0 && c.getRobots()[0]->getRow() == 1 && c.getRobots()[0]->getCol() == 1)){
          c.tickForTest();
    }
    QVERIFY(c.getRobots()[0]->pathIsEmpty() == true);
}

void ServerTest::test_ifProductDeliveredSignalEmitted()
{
    Controller c;
    c.setSize(6);
    c.addRobot(1,1,0);
    c.addShelf(1,3);
    c.addProduct("alma", 0);
    c.addDropOffPoint(2,2, "alma");
    c.addDocker(2,1);
    c.addOrder("alma");
    QSignalSpy spy(&c, SIGNAL(updateState()));
    while(!(c.getRobots()[0]->getState() == FREE && c.getProducts().size() == 0)){
         c.tickForTest();
    }
    QVERIFY(spy.count() > 1);
}

QTEST_APPLESS_MAIN(ServerTest)

#include "tst_servertest.moc"
