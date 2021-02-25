#ifndef DOCKERFIELDMODEL_H
#define DOCKERFIELDMODEL_H

#include <QObject>

class DockerFieldModel
{
public:
    DockerFieldModel(int row, int col);

    int getRow() const;
    int getCol() const;

private:
    int _row;
    int _col;
};

#endif // DOCKERFIELDMODEL_H
