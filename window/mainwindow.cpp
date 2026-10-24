#include"mainwindow.h"
#include"../components/header.h"
#include <QLabel>
#include<QPushButton>
#include<QVBoxLayout>
#include"loginwindow.h"
#include<iostream>
#include<QFile>
#include <windows.h>
#include <dwmapi.h>
MainWindow::MainWindow(QWidget *parent):QWidget(parent){
    this->setWindowTitle("SFUdo");
    this->setObjectName("mainwindow");
    this->setWindowFlags(
    Qt::FramelessWindowHint |
    Qt::Window
    );
    this->showMaximized();
    HWND hwnd = (HWND)this->winId();

    const DWORD DWMWC       P_DONOTROUND = 1;

    DwmSetWindowAttribute(
        hwnd,
        33,
        &DWMWCP_DONOTROUND,
        sizeof(DWMWCP_DONOTROUND)
    );
    QVBoxLayout *mainlayout=new QVBoxLayout(this);
    mainlayout->setContentsMargins(0,0,0,0);
    mainlayout->setSpacing(0);
    Header *header=new Header(this);
    // mainlayout->addWidget(header->getHeaderWidget());


    QWidget *contentWidget = new QWidget;

    QHBoxLayout *contentLayout = new QHBoxLayout(contentWidget);

    // NO margins
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(0);

    // =====================================================
    // LEFT SIDE = 70%
    // =====================================================
    QFrame *mainSection = new QFrame;
    mainSection->setObjectName("MainPanel");

    QVBoxLayout *mainLayout70 = new QVBoxLayout(mainSection);
    mainLayout70->setSpacing(12);
    mainLayout70->setContentsMargins(15, 15, 15, 15);
    

    // =====================================================
    // RIGHT SIDE = 30%
    // =====================================================
    QWidget *rightSection = new QWidget;

    QVBoxLayout *rightLayout = new QVBoxLayout(rightSection);

    // NO margins
    rightLayout->setContentsMargins(0,0,0,0);
    rightLayout->setSpacing(0);

    // ================= PANEL 1 =================
    QFrame *panel1 = new QFrame;
    panel1->setObjectName("RightPanel1");
    

    QVBoxLayout *p1Layout = new QVBoxLayout(panel1);
    p1Layout->setContentsMargins(0,0,0,0);
    p1Layout->setSpacing(0);    

    QLabel *p1Text = new QLabel("SFU Server");
    p1Text->setObjectName("PanelText");
    p1Text->setStyleSheet(R"(
    background-color: #191919;
    color: white;
    )");
//     PLAYIT_HOST = "147.185.221.29"   # e.g. abc123.playit.gg
// PLAYIT_PORT = 4985   
    p1Text->setContentsMargins(0,0,0,0);
    QLabel *iplable = new QLabel(
        "<span style='color:white;'>IP:</span> "
        "<span style='color:#0ed35d;'>147.185.221.29 IPv4</span>"
    );

    iplable->setStyleSheet(R"(
        background: transparent;
        margin-bottom:0px;
        padding-top: 8px;
        padding-bottom: 0px;
        padding-left: 12px;
        padding-right: 12px;

        font-size: 20px;

        font-family: 'Segoe UI';
    )");
    QLabel *portlable = new QLabel(
        "<span style='color:white;'>PORT:</span> "
        "<span style='color:#213bbc;'>4985</span>"
    );

    portlable->setStyleSheet(R"(
        background: transparent;
        margin-top:0px;
        padding-bottom: 8px;
        padding-left: 12px;
        padding-right: 12px;

        font-size: 20px;

        font-family: 'Segoe UI';
    )");
    // QLabel *ip =new Qlable("")
    p1Layout->addWidget(p1Text);
    p1Layout->addWidget(iplable);
    p1Layout->addWidget(portlable);
    p1Layout->addStretch();

    // ================= PANEL 2 =================
    QFrame *panel2 = new QFrame;
    panel2->setObjectName("RightPanel2");

    QVBoxLayout *p2Layout = new QVBoxLayout(panel2);
    p2Layout->setContentsMargins(0,0,0,0);
    p2Layout->setSpacing(0);    

    QLabel *p2Text = new QLabel("Panel 2");
    p2Text->setObjectName("PanelText");
    p2Text->setStyleSheet(R"(
    background-color: #191919;
    color: white;
    )");
    p2Text->setContentsMargins(0,0,0,0);


    p2Layout->addWidget(p2Text);
    p2Layout->addStretch();

    // ================= PANEL 3 =================
    QFrame *panel3 = new QFrame;
    panel3->setObjectName("RightPanel3");
        
    QVBoxLayout *p3Layout = new QVBoxLayout(panel3);
    p3Layout->setContentsMargins(0,0,0,0);
    p3Layout->setSpacing(0);
    QLabel *p3Text = new QLabel("Panel 3");
    p3Text->setObjectName("PanelText");

    p3Text->setStyleSheet(R"(
    background-color: #191919;
    color: white;
    )");
    p3Text->setContentsMargins(0,0,0,0);
    p3Layout->addWidget(p3Text);
    p3Layout->addStretch();

    // ADD PANELS
    rightLayout->addWidget(panel1);
    rightLayout->addWidget(panel2);
    rightLayout->addWidget(panel3);

    // ================= ADD SECTIONS =================
    contentLayout->addWidget(mainSection, 7);
    contentLayout->addWidget(rightSection, 3);

    // ================= FINAL =================
    mainlayout->addWidget(contentWidget);



    // QPushButton *btn=new QPushButton("OPEN Login window",this);

    
    // connect(btn,&QPushButton::clicked,[=](){
        // std::cout<<"This is Rao"<<std::endl;
    //     LoginWindow *loginwindow=new LoginWindow(); // if i pass this inside this and we closed the main window so login window run and cloased becuase of our main window
    //     loginwindow->show();
    //     this->close();
    // });


    
}