#include"onServer.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QPushButton>
OnServer::OnServer(QWidget *parent):QWidget(parent){
    this->setObjectName("onserver");
    this->setAttribute(Qt::WA_StyledBackground, true);
    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->setContentsMargins(5, 15, 5, 5);
    mainlayout->setSpacing(10);
    QLabel *signaling_txt = new QLabel("SIGNALING", this);
    signaling_txt->setObjectName("onServer-title");
    mainlayout->addWidget(signaling_txt);
    QPushButton *sigl_reload=new QPushButton("SIGNALING RELOAD");
    sigl_reload->setObjectName("room-item-startbtn");

    mainlayout->addWidget(sigl_reload);
    QHBoxLayout *hmain = new QHBoxLayout();
    hmain->setContentsMargins(0, 0, 0, 0);
    hmain->setSpacing(8);
    QVBoxLayout *v1 = new QVBoxLayout();
    QVBoxLayout *v2 = new QVBoxLayout();
    QVBoxLayout *v3 = new QVBoxLayout();

    v1->setContentsMargins(0, 0, 0, 0);
    v2->setContentsMargins(0, 0, 0, 0);
    v3->setContentsMargins(0, 0, 0, 0);

    v1->setSpacing(6);
    v2->setSpacing(6);
    v3->setSpacing(6);

    hmain->addLayout(v1, 5);
    hmain->addLayout(v2, 25);
    hmain->addLayout(v3, 25);

    auto addRow = [&](const QString &name, const QString &value) {
        QLabel *label = new QLabel(name, this);
        label->setObjectName("cpu-data");
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

        QLabel *dots = new QLabel("..............", this);
        dots->setObjectName("cpu-temp-holder");
        dots->setAlignment(Qt::AlignCenter);
        dots->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        QLabel *val = new QLabel(value, this);
        val->setObjectName("cpu-valu");
        val->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        val->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

        v1->addWidget(label);
        v2->addWidget(dots);
        v3->addWidget(val);
    };
    addRow("SERVER STATUS", "CONNECTED");
    addRow("SERVER IP", "157.20.184.67");
    addRow("SERVER PORT", "20058");
    addRow("PROTOCOL", "WebSocket");
    addRow("UPTIME", "12m 34s");
    addRow("RECONNECTS", "0");
    mainlayout->addLayout(hmain);

   

    QLabel *sfu_txt = new QLabel("SFU", this);
    sfu_txt->setObjectName("onServer-title");
    mainlayout->addWidget(sfu_txt);
    QPushButton *sfu_reload=new QPushButton("SFU RELOAD");
    sfu_reload->setObjectName("room-item-startbtn");

    mainlayout->addWidget(sfu_reload);

    QHBoxLayout *hmain2 = new QHBoxLayout();
    hmain2->setContentsMargins(0, 0, 0, 0);
    hmain2->setSpacing(8);
    QVBoxLayout *v21 = new QVBoxLayout();
    QVBoxLayout *v22 = new QVBoxLayout();
    QVBoxLayout *v23 = new QVBoxLayout();

    v21->setContentsMargins(0, 0, 0, 0);
    v22->setContentsMargins(0, 0, 0, 0);
    v23->setContentsMargins(0, 0, 0, 0);

    v21->setSpacing(6);
    v22->setSpacing(6);
    v23->setSpacing(6);

    hmain2->addLayout(v21, 5);
    hmain2->addLayout(v22, 25);
    hmain2->addLayout(v23, 25);

    auto addsfuRow = [&](const QString &name, const QString &value) {
        QLabel *label = new QLabel(name, this);
        label->setObjectName("cpu-data");
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

        QLabel *dots = new QLabel("..............", this);
        dots->setObjectName("cpu-temp-holder");
        dots->setAlignment(Qt::AlignCenter);
        dots->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        QLabel *val = new QLabel(value, this);
        val->setObjectName("cpu-valu");
        val->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        val->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

        v21->addWidget(label);
        v22->addWidget(dots);
        v23->addWidget(val);
        
    };
    addsfuRow("SFU STATUS", "RUNNING");
    addsfuRow("SFU HOST", "127.0.0.1");
    addsfuRow("SFU PORT", "20058");
    addsfuRow("SFU PROTOCOL", "UDP");
    // addsfuRow("SFU UPTIME", "12m 34s");
    // addsfuRow("SFU PID", "8420");

    addsfuRow("SFU CPU USAGE", "2.75%");
    addsfuRow("SFU RAM USAGE", "187 MB");
    addsfuRow("SFU THREADS", "14");
    addsfuRow("SFU HANDLES", "356");
    addsfuRow("SFU PROCESS STATUS", "Healthy");
//     addRow("ACTIVE ROOMS", "3");
// addRow("ACTIVE PEERS", "8");
// addRow("PUBLISHERS", "3");
// addRow("SUBSCRIBERS", "5");
// addRow("ACTIVE TRANSPORTS", "16");
// addRow("INBOUND BITRATE", "4.8 Mbps");
// addRow("OUTBOUND BITRATE", "12.4 Mbps");
// addRow("TOTAL BITRATE", "17.2 Mbps");
// addRow("RTP PACKETS IN", "128420");
// addRow("RTP PACKETS OUT", "342800");
// addRow("RTCP PACKETS", "1840");
    mainlayout->addLayout(hmain2);

    
    mainlayout->addStretch();


}