#include"OnRoomList.h"
#include<QListWidget>
#include<QListWidgetItem>
#include<QVBoxLayout>
#include"./item/roomitem.h"
OnRoomList::OnRoomList(QWidget *parent):QWidget(parent){
    // this->setObjectName("onnetwrok");
    this->setAttribute(Qt::WA_StyledBackground, true);
    QVBoxLayout *mainlayout=new QVBoxLayout(this);
    mainlayout->setContentsMargins(0, 0, 0, 0);
    mainlayout->setSpacing(0);
    QListWidget *list=new QListWidget(this);
    list->setObjectName("room-list");
    for(int i=0;i<3;i++){
        QListWidgetItem *item=new QListWidgetItem(list);
        RoomItem *roomItem=new RoomItem(list,"Android Studio","This class is for Android studio Devlopment",i);
        item->setSizeHint(QSize(0,200));
        list->addItem(item);
        list->setItemWidget(item, roomItem);
    }
    mainlayout->addWidget(list,1);


}