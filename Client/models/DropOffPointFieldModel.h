#ifndef DROPOFFPOINTFIELDMODEL_H
#define DROPOFFPOINTFIELDMODEL_H


class DropOffPointFieldModel
{
public:
    DropOffPointFieldModel(int row, int col, int product);

    int getProduct() const;
    int getCol() const;
    int getRow() const;

private:
    int _row;
    int _col;
    int _product;
};

#endif // DROPOFFPOINTFIELDMODEL_H
