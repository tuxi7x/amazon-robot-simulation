#ifndef MAPEDITORCONTROLLER_H
#define MAPEDITORCONTROLLER_H
#include "models/DockerFieldModel.h"
#include "models/DropOffPointFieldModel.h"
#include "models/ProductModel.h"
#include "models/RobotFieldModel.h"
#include "models/ShelfFieldModel.h"

#include <QMap>
#include <QObject>

class MapEditorController : public QObject
{
    Q_OBJECT
public:
    explicit MapEditorController(QObject *parent = nullptr);
    enum FieldTypes {Empty, Robot, Shelf, Docker, DropOffPoint};

    void createNewMap (int size);
    QPair<FieldTypes, QObject*> getField (int row, int col);
    int getSize();
    void addRobot(int row, int col);
    void addShelf(int row, int col);
    void addDocker(int row, int col);
    void addDropOffPoint(int row, int col);
    void addProduct(int row, int col, QString productName);

signals:
    void mapCreated();
    void fieldChanged(int row, int col);

private:
    QVector<RobotFieldModel*> _robots;
    QVector <ShelfFieldModel*> _shelves;
    QVector <DockerFieldModel*> _dockers;
    QVector <DropOffPointFieldModel*> _dropOffPoints;
    QMap <int, ProductModel*> _products;

    int _size;


};

#endif // MAPEDITORCONTROLLER_H
