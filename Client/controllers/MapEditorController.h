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
#include <QVector>

/**
 * @brief The MapEditorController class implements the business logic behind the map editor in this Application
 */
class MapEditorController : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief MapEditorController is the default constructor for this class.
     * @param parent is the parent of this class.
     */
    explicit MapEditorController(QObject *parent = nullptr);
    /**
     * @brief The FieldTypes enum represents the type of fields that are possible in the editor.
     */
    enum FieldTypes {Empty, Robot, Shelf, Docker, DropOffPoint};
    ~MapEditorController();
    /**
     * @brief createNewMap creates a new map in the editor, after this function the user can start editing the map.
     * @param size the width and height of the map.
     */
    void createNewMap (int size);
    /**
     * @brief getField A getter for a field in a specific position of the map.
     * @param row the row of the field
     * @param col the column of the field
     * @return Returns a pair, the first element of the pair is of type FieldTypes and it tells us what kind of field this is.
     * the second element of the pair is the actual model of that particular field. The second element is null if the field is empty.
     */
    QPair<FieldTypes, QObject*> getField (int row, int col);
    /**
     * @brief getSize A getter for the width and row of the map.
     * @return the size of the map as an int.
     */
    int getSize();
    /**
     * @brief addRobot It is possible to add a new robot with this method.
     * @param row The row of the new robot.
     * @param col The column of the new robot.
     */
    void addRobot(int row, int col);
    /**
     * @brief addShelf It is possible to add a new shelf with this method.
     * @param row The row of the new shelf.
     * @param col The column of the new shelf.
     */
    void addShelf(int row, int col);
    /**
     * @brief addDocker It is possible to add a new docker with this method.
     * @param row The row of the new docker.
     * @param col The column of the new docker.
     */
    void addDocker(int row, int col);
    /**
     * @brief addDropOffPoint It is possible to add a new docker with this method.
     * @param row The row of the new docker.
     * @param col The column of the new docker.
     * @param product
     */
    void addDropOffPoint(int row, int col, QString product);
    /**
     * @brief addProduct It is possible to add a new product to a shelf with this method.
     * @param row the row of the shelf on which we want to add the new product.
     * @param col the column of the shelf on which we want to add the new product.
     * @param productName the name of the new product.
     * @return if the new product was succesfully added to the shelf in the given row and col.
     */
    bool addProduct(int row, int col, QString productName);
    /**
     * @brief validateProductPlacement validates the placement of a product in a specific position.
     * @param row the row of the product.
     * @param col the column of the product.
     * @return true if there is a shelf in the given position and false if there is already a product in the given position.
     */
    bool validateProductPlacement(int row, int col);
    /**
     * @brief fieldIsEmpty method checks if the map is empty.
     * @return true if the map is empty, and false if it is not empty.
     */
    bool fieldIsEmpty();
    /**
     * @brief toggleShelfSelection toggles the selected state of the shelf given as a parameter. If it was selected before then it won't be selected now.
     * and the other way around.
     * @param s the shelf we want to toggle.
     */
    void toggleShelfSelection (ShelfFieldModel* s);
    /**
     * @brief rotateRobot Rotates the Robot given as a parameter with 90 degrees to the right.
     * @param r
     */
    void rotateRobot (RobotFieldModel* r);
    /**
     * @brief moveSelectedShelves moves all selected shelves 1 in the given direction if all selected shelves can move.
     * @param direction the direction in which we want to move the selected shelves. 0 = north, 1 = east, 2 = south, 3 = west.
     * @return whether the move was succesful
     */
    bool moveSelectedShelves (int direction);
    /**
     * @brief isASelectedShelf checks whether there is a selected shelf in the given position.
     * @param row the row of the shelf.
     * @param col the column of the shelf.
     * @return true if there is a shelf in the given position and it is selected, otherwise returns false.
     */
    bool isASelectedShelf(int row, int col);
    /**
     * @brief getProductsOnShelf gets the name of all products on a shelf with the given position.
     * @param row the row of the shelf.
     * @param col the column of the shelf
     * @return the name of the products on the shelf in a vector as QString
     */
    QVector<QString> getProductsOnShelf(int row, int col);
    /**
     * @brief getUnassignedProducts gets the name of the products that currently don't have a drop off points assigned to them.
     * @return the name of the products in a QVector as QString
     */
    QVector<QString> getUnassignedProducts();
    /**
     * @brief getProducts gets the name of all the products on the map.
     * @return the list of the products in a QVector as QStrings
     */
    QVector<QString> getProducts();
    /**
     * @brief validateBeforeSave checks whether it is possible to save the map in the current state.
     * @return true if it is pobbile and false if it is not possible.
     */
    QString validateBeforeSave();
    /**
     * @brief setOrders A setter for the _orders member which contains all the products which will be already ordered at the start of the simulation.
     * @param orders the new value of the orders member.
     */
    void setOrders(QVector<QString> orders);
    /**
     * @brief getOrders A getter for the _orders member which contains all the products which will be already ordered at the start of the simulation.
     * @return the _orders member.
     */
    QVector<QString> getOrders() const;
    /**
     * @brief writeToJSON writes the current state of the map to the given QJsonObject
     * @param json The QJsonObject in which we want to write to.
     */
    void writeToJSON(QJsonObject &json);
    /**
     * @brief saveToJSON saves the current satate of the map to an actual file.
     * @param file the file we want to save to.
     * @return true if the saving was succesful and false if it wasn't succesful.
     */
    bool saveToJSON(QFile* file);
signals:
    /**
     * @brief mapCreated is a signal emitted by the MapEditorController when there was a new map created.
     */
    void mapCreated();
    /**
     * @brief fieldChanged is a signal emitted by the MapEditorController when a specific field changed.
     * @param row the row of the field.
     * @param col the column of the field.
     */
    void fieldChanged(int row, int col);
    /**
     * @brief shelfSelectionChanged is a signal emitted by the MapEditorController when the selected state of a shelf was changed.
     * @param row the row of the shelf.
     * @param col the column of the shelf.
     * @param selected the selection value of the shelf.
     */
    void shelfSelectionChanged (int row, int col, bool selected);

private:
    QVector<RobotFieldModel*> _robots;
    QVector <ShelfFieldModel*> _shelves;
    QVector <ShelfFieldModel*> _selectedShelves;
    QVector <DockerFieldModel*> _dockers;
    QVector <DropOffPointFieldModel*> _dropOffPoints;
    QVector <ProductModel*> _products;
    QVector <QString> _orders;
    int _size;
};

#endif // MAPEDITORCONTROLLER_H
