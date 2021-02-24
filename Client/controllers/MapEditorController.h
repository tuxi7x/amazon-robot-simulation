#ifndef MAPEDITORCONTROLLER_H
#define MAPEDITORCONTROLLER_H

#include <QObject>

class MapEditorController : public QObject
{
    Q_OBJECT
public:
    explicit MapEditorController(QObject *parent = nullptr);
    enum FieldTypes {Empty, Robot, Shelf, Docker, DropOffPoint};

    void createNewMap (int size);
    FieldTypes getField (int row, int col);
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
    QVector<QVector<FieldTypes>> _field;
    int _size;


};

#endif // MAPEDITORCONTROLLER_H
