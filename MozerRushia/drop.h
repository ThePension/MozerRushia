#ifndef DROP_H
#define DROP_H
#include <QGraphicsPixmapItem>
#include "settings.h"


class Drop : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Drop(int speed, QGraphicsItem* parent, QTimer *moveTimer);
    ~Drop();
    int speed;
    int type;

private slots :
    void onMove();
};

#endif // DROP_H
