#ifndef MAPEDITORCONTROLLER_H
#define MAPEDITORCONTROLLER_H
#include "models/DockerFieldModel.h"
#include "models/DropOffPointFieldModel.h"
#include "models/ProductModel.h"
#include "models/RobotFieldModel.h"
#include "models/ShelfFieldModel.h"
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

class MapEditorController : public QObject
{
    Q_OBJECT
public:
    explicit MapEditorController(QObject *parent = nullptr);
    enum FieldTypes {Empty, Robot, Shelf, Docker, DropOffPoint};
    ~MapEditorController();

    void createNewMap (int size);
    QPair<FieldTypes, QObject*> getField (int row, int col);
    int getSize();
    void addRobot(int row, int col);
    void addShelf(int row, int col);
    void addDocker(int row, int col);
    void addDropOffPoint(int row, int col, QString product);
    bool addProduct(int row, int col, QString productName);
    bool validateProductPlacement(int row, int col);
    bool fieldIsEmpty();
    QVector<QString> getProductsOnShelf(int row, int col);
    QVector<QString> getUnassignedProducts();
    QVector<QString> getProducts();
    QString validateBeforeSave();


    void writeToJSON(QJsonObject &json);
    bool saveToJSON(QFile* file);

signals:
    void mapCreated();
    void fieldChanged(int row, int col);

private:
    QVector<RobotFieldModel*> _robots;
    QVector <ShelfFieldModel*> _shelves;
    QVector <DockerFieldModel*> _dockers;
    QVector <DropOffPointFieldModel*> _dropOffPoints;
    QVector <ProductModel*> _products;
    int _size;


};

#endif // MAPEDITORCONTROLLER_H
