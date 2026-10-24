#include"header.h"
#include<QFile>
#include<QVBoxLayout>
#include<QLabel>
#include<QHBoxLayout>
#include<QPushButton>
#include<QStyle>
#include"TopProfile.h"
Header::Header(QWidget *parent):QWidget(parent){
    this->setObjectName("header");
    setAttribute(Qt::WA_StyledBackground, true);
    this->setFixedHeight(40);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    QLabel *title = new QLabel("SFUdo", this);
    QLabel *logo = new QLabel(this);
    logo->setObjectName("header-logo");
    title->setObjectName("header-logo-title");
    logo->setPixmap(QPixmap(":/icons/logo.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));


    QPushButton *minBtn = new QPushButton(this);
    QPushButton *maxBtn = new QPushButton(this);
    QPushButton *closeBtn = new QPushButton(this);
    minBtn->setObjectName("minBtn");
    maxBtn->setObjectName("maxBtn");
    closeBtn->setObjectName("closeBtn");

    minBtn->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    maxBtn->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    closeBtn->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));

    minBtn->setFixedSize(40, 40);
    maxBtn->setFixedSize(40, 40);
    closeBtn->setFixedSize(40, 40);
    TopProfile *profile = new TopProfile("Om Wanave", this);
    QPushButton *stopsfu=new QPushButton("SFU STOP");
    stopsfu->setObjectName("header-stop-btn");
    QPushButton *stopsign=new QPushButton("SIGNALING STOP");
    stopsign->setObjectName("header-stop-btn");

    QLabel *copyright = new QLabel("@2026 BashDot. All Rights Reserved", this);
    copyright->setObjectName("copyright-txt");



    layout->addWidget(logo);
    layout->addWidget(title);
    layout->addWidget(copyright);
    layout->addStretch();
    layout->addWidget(stopsfu);
    layout->addWidget(stopsign);
    layout->addWidget(profile, 0, Qt::AlignLeft);
    layout->addWidget(minBtn);
    layout->addWidget(maxBtn);
    layout->addWidget(closeBtn);

}