#ifndef SHELFFIELDMODEL_H
#define SHELFFIELDMODEL_H


class ShelfFieldModel
{
public:
    ShelfFieldModel(int row, int col);

    int getRow() const;
    int getCol() const;

private:
    int _row;
    int _col;
};

#endif // SHELFFIELDMODEL_H
