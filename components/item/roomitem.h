#ifndef ROOMITEM_H
#define ROOMITEM_H
#include<QWidget>
class RoomItem :public QWidget{
    public:
        explicit RoomItem(QWidget *parent,QString title,QString desc,int status);
};
#endif