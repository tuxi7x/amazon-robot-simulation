#ifndef DOCKERFIELDMODEL_H
#define DOCKERFIELDMODEL_H

#include <QObject>
#include <QJsonObject>

class DockerFieldModel: public QObject
{
    Q_OBJECT
public:
    DockerFieldModel(int row, int col, QObject* parent = nullptr);
    int getRow() const;
    int getCol() const;

    void write(QJsonObject &json);
    void read(const QJsonObject &json);


private:
    int _row;
    int _col;
};

#endif // DOCKERFIELDMODEL_H
