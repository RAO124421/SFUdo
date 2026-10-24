#include"roomitem.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include <QSizePolicy>
#include<QPushButton>
RoomItem::RoomItem(QWidget *parent,QString title,QString desc,int status):QWidget(parent){
    // this->samyak mahendra khobragade ceo of the company and aslo driver of the the virtus
    this->setObjectName("room-item");
    this->setAttribute(Qt::WA_StyledBackground, true);
    QVBoxLayout *itemLayout=new QVBoxLayout(this);
    itemLayout->setContentsMargins(20, 20, 20, 20);
    QLabel *label1=new QLabel(title);
    label1->setObjectName("room-item-title");
    label1->setWordWrap(true);
    label1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QLabel *label2=new QLabel(desc);
    label2->setObjectName("room-item-desc");
    label2->setWordWrap(true);
    label2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    itemLayout->addWidget(label1);
    itemLayout->addWidget(label2);
    QLabel *statustxt;
    QPushButton *startbtn=new QPushButton("Start");
    startbtn->setObjectName("room-item-startbtn");
    switch (status)
    {
    case 0:
        /* code */
        statustxt=new QLabel("STATUS : NOTSTARTED");
        statustxt->setObjectName("room-item-status-running");
        break;
    case 1:
        statustxt=new QLabel("STATUS : STARTED");
        statustxt->setObjectName("room-item-status-started");
        startbtn->setText("Join");
        break;
    case 2:
        statustxt=new QLabel("STATUS : END");
        statustxt->setObjectName("room-item-status-end");
        break;
    default:
        break;
    }
    
    itemLayout->addWidget(statustxt);
    itemLayout->addStretch();
    if(status!=2){
    itemLayout->addWidget(startbtn);

    }





}
