#ifndef SHELFFIELDMODEL_H
#define SHELFFIELDMODEL_H

#include <QObject>
#include <QJsonObject>


class ShelfFieldModel : public QObject
{
    Q_OBJECT
public:
    ShelfFieldModel(int row, int col, QObject* parent = nullptr);

    int getRow() const;
    int getCol() const;

    void write(QJsonObject &json);
    void read(const QJsonObject &json);

private:
    int _row;
    int _col;
};

#endif // SHELFFIELDMODEL_H
