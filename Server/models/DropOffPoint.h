#ifndef DROPOFFPOINT_H
#define DROPOFFPOINT_H

#include <QObject>

class DropOffPoint : public QObject
{
    Q_OBJECT
public:
    explicit DropOffPoint(QObject *parent = nullptr);

private:
    int _id;
    int _index;

signals:

};

#endif // DROPOFFPOINT_H
