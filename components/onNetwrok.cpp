#include "onNetwrok.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "RamUsageWidget.h"

OnNetwrok::OnNetwrok(QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName("onnetwrok");
    this->setAttribute(Qt::WA_StyledBackground, true);

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->setContentsMargins(5, 15, 5, 5);
    mainlayout->setSpacing(10);

    QLabel *ip = new QLabel("IP ADDRESS : 157.20.184.67", this);
    ip->setObjectName("onNetwork-ip");

    QLabel *port = new QLabel("PORT : 20058", this);
    port->setObjectName("onNetwork-ip");

    mainlayout->addWidget(ip);
    mainlayout->addWidget(port);

    QHBoxLayout *hmain = new QHBoxLayout();
    hmain->setContentsMargins(0, 0, 0, 0);
    hmain->setSpacing(8);

    /*
     * Important:
     * Do not pass 'this' to inner layouts.
     */
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

    addRow("PUBLIC STATUS", "FAILD");
    addRow("CONNECTION TYPE", "Wi-Fi");
    addRow("UPLOAD TOTAL", "27.482 MB");
    addRow("DOWNLOAD TOTAL", "258.76 MB");
    addRow("UPLOAD TRAFFIC", "0.00308 Mbps");
    addRow("DOWNLOAD TRAFFIC", "0.003696 Mbps");
    addRow("TOTAL TRAFFIC", "0.006776 Mbps");

    mainlayout->addLayout(hmain);

    /*
     * RAM graph widget
     * This will take full available parent width.
     */
    QVector<double> uploadTrafficData = {
    0.00120, 0.00180, 0.00210, 0.00150, 0.00280,
    0.00300, 0.00270, 0.00320, 0.00308
    };

    RamUsageWidget *uploadTrafficWidget = new RamUsageWidget(
        "Upload Traffic",
        0.00308,
        "Mbps",
        0.01000,
        uploadTrafficData,
        this
    );

    mainlayout->addWidget(uploadTrafficWidget);
    QVector<double> downloadTrafficData = {
    0.00150, 0.00220, 0.00280, 0.00310, 0.00340,
    0.00360, 0.00320, 0.00390, 0.003696
    };

    RamUsageWidget *downloadTrafficWidget = new RamUsageWidget(
        "Download Traffic",
        0.003696,
        "Mbps",
        0.01000,
        downloadTrafficData,
        this
    );

    mainlayout->addWidget(downloadTrafficWidget);

    

    mainlayout->addStretch();
}
