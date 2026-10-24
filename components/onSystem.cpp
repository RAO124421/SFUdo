#include"onSystem.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QWidget>
#include"RamUsageWidget.h"
OnSystem::OnSystem(QWidget *parent):QWidget(parent){
    this->setObjectName("onsystem");
    this->setAttribute(Qt::WA_StyledBackground, true);
    QVBoxLayout *mainlayout=new QVBoxLayout(this);
    mainlayout->setContentsMargins(5,5,5,5);
    QWidget *cpuWidget=new QWidget(this);
    cpuWidget->setObjectName("cpuWidget");
    cpuWidget->setAttribute(Qt::WA_StyledBackground, true);
    QVBoxLayout *cpulayout=new QVBoxLayout(cpuWidget);

    QLabel *cpuName=new QLabel("11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz");
    cpuName->setObjectName("onsystem-cpuname");
    cpuName->setWordWrap(true);
    QHBoxLayout *hmain=new QHBoxLayout(this);
    hmain->setContentsMargins(0,0,0,0);
    QVBoxLayout *v1=new QVBoxLayout(this);
    QVBoxLayout *v2=new QVBoxLayout(this);
    QVBoxLayout *v3=new QVBoxLayout(this);
    hmain->addLayout(v1,5);
    hmain->addLayout(v2,25);
    hmain->addLayout(v3,25);

    QLabel *logical_pro=new QLabel("Logical processors");
    logical_pro->setObjectName("cpu-data");
    QLabel *phy_pro=new QLabel("Physical cores");
    phy_pro->setObjectName("cpu-data");
    QLabel *use_pro=new QLabel("CPU usage");
    use_pro->setObjectName("cpu-data");
    v1->addWidget(use_pro);
    v1->addWidget(phy_pro);
    v1->addWidget(logical_pro);
    

    QLabel *temp1=new QLabel("........................");
    temp1->setObjectName("cpu-temp-holder");
    QLabel *temp2=new QLabel("........................");
    temp2->setObjectName("cpu-temp-holder");
    QLabel *temp3=new QLabel("........................");
    temp3->setObjectName("cpu-temp-holder");
    v2->addWidget(temp1);
    v2->addWidget(temp2);
    v2->addWidget(temp3);


    QLabel *vallogproc=new QLabel("2.75%");
    vallogproc->setObjectName("cpu-valu");
    QLabel *valphy_pro=new QLabel("4");
    valphy_pro->setObjectName("cpu-valu");
    QLabel *valuse_pro=new QLabel("8");
    valuse_pro->setObjectName("cpu-valu");
    v3->addWidget(vallogproc);
    v3->addWidget(valphy_pro);
    v3->addWidget(valuse_pro);

    QHBoxLayout *hmain2=new QHBoxLayout(this);
    hmain2->setContentsMargins(0,0,0,0);
    QHBoxLayout *v21=new QHBoxLayout(this);
    QHBoxLayout *v22=new QHBoxLayout(this);
    QVBoxLayout *v211=new QVBoxLayout(this);
    QVBoxLayout *v212=new QVBoxLayout(this);
    QVBoxLayout *v213=new QVBoxLayout(this);
    QVBoxLayout *v221=new QVBoxLayout(this);
    QVBoxLayout *v222=new QVBoxLayout(this);
    QVBoxLayout *v223=new QVBoxLayout(this);
    hmain2->addLayout(v21,5);
    hmain2->addLayout(v22,5);
    v21->addLayout(v211,3);
    v21->addLayout(v212,4);
    v21->addLayout(v213,3);
    v22->addLayout(v221,3);
    v22->addLayout(v222,4);
    v22->addLayout(v223,3);

    QLabel *core1=new QLabel("Core1");
    core1->setObjectName("cpu-data");
    QLabel *core2=new QLabel("Core2");
    core2->setObjectName("cpu-data");
    QLabel *core3=new QLabel("Core3");
    core3->setObjectName("cpu-data");
    QLabel *core4=new QLabel("Core4");
    core4->setObjectName("cpu-data");
    v211->addWidget(core1);
    v211->addWidget(core2);
    v211->addWidget(core3);
    v211->addWidget(core4);

    QLabel *tempc1=new QLabel("..............");
    tempc1->setObjectName("cpu-temp-holder");
    QLabel *tempc2=new QLabel("..............");
    tempc2->setObjectName("cpu-temp-holder");
    QLabel *tempc3=new QLabel("..............");
    tempc3->setObjectName("cpu-temp-holder");
    QLabel *tempc4=new QLabel("..............");
    tempc4->setObjectName("cpu-temp-holder");
    v212->addWidget(tempc1);
    v212->addWidget(tempc2);
    v212->addWidget(tempc3);
    v212->addWidget(tempc4);

    QLabel *valcore1=new QLabel("2.75%");
    valcore1->setObjectName("cpu-valu");
    QLabel *valcore2=new QLabel("2.75%");
    valcore2->setObjectName("cpu-valu");
    QLabel *valcore3=new QLabel("2.75%");
    valcore3->setObjectName("cpu-valu");
    QLabel *valcore4=new QLabel("2.75%");
    valcore4->setObjectName("cpu-valu");
    v213->addWidget(valcore1);
    v213->addWidget(valcore2);
    v213->addWidget(valcore3);
    v213->addWidget(valcore4);
    v21->addStretch();


    QLabel *core5=new QLabel("Core5");
    core5->setObjectName("cpu-data");
    QLabel *core6=new QLabel("Core6");
    core6->setObjectName("cpu-data");
    QLabel *core7=new QLabel("Core7");
    core7->setObjectName("cpu-data");
    QLabel *core8=new QLabel("Core8");
    core8->setObjectName("cpu-data");
    v221->addWidget(core5);
    v221->addWidget(core6);
    v221->addWidget(core7);
    v221->addWidget(core8);

    QLabel *tempc5=new QLabel("..............");
    tempc5->setObjectName("cpu-temp-holder");
    QLabel *tempc6=new QLabel("..............");
    tempc6->setObjectName("cpu-temp-holder");
    QLabel *tempc7=new QLabel("..............");
    tempc7->setObjectName("cpu-temp-holder");
    QLabel *tempc8=new QLabel("..............");
    tempc8->setObjectName("cpu-temp-holder");
    v222->addWidget(tempc5);
    v222->addWidget(tempc6);
    v222->addWidget(tempc7);
    v222->addWidget(tempc8);

    QLabel *valcore5=new QLabel("2.75%");
    valcore5->setObjectName("cpu-valu");
    QLabel *valcore6=new QLabel("2.75%");
    valcore6->setObjectName("cpu-valu");
    QLabel *valcore7=new QLabel("2.75%");
    valcore7->setObjectName("cpu-valu");
    QLabel *valcore8=new QLabel("2.75%");
    valcore8->setObjectName("cpu-valu");
    v223->addWidget(valcore5);
    v223->addWidget(valcore6);
    v223->addWidget(valcore7);
    v223->addWidget(valcore8);
    v22->addStretch();
    

    cpuName->setObjectName("onsystem-cpuname");
    cpulayout->addWidget(cpuName);
    cpulayout->addLayout(hmain);
    cpulayout->addLayout(hmain2);
    mainlayout->addWidget(cpuWidget);


    QWidget *ramWidget=new QWidget(this);
    ramWidget->setObjectName("ramWidget");
    ramWidget->setAttribute(Qt::WA_StyledBackground, true);
    QHBoxLayout *ramHL=new QHBoxLayout(ramWidget);
    ramHL->setContentsMargins(8,0,0,0);
    QVBoxLayout *ramVL1=new QVBoxLayout();
    QVBoxLayout *ramVL2=new QVBoxLayout();
    QVBoxLayout *ramVL3=new QVBoxLayout();

    ramHL->addLayout(ramVL1,5);
    ramHL->addLayout(ramVL2,20);
    ramHL->addLayout(ramVL3,30);
    QLabel *ram_us=new QLabel("RAM usage");
    ram_us->setObjectName("cpu-data");
    QLabel *t_phy_ram=new QLabel("Total RAM");
    t_phy_ram->setObjectName("cpu-data");
    QLabel *ava_ram=new QLabel("Available RAM");
    ava_ram->setObjectName("cpu-data");
    QLabel *used_ram=new QLabel("Used RAM");
    used_ram->setObjectName("cpu-data");
    QLabel *process_w_ram=new QLabel("Working set");
    process_w_ram->setObjectName("cpu-data");
    QLabel *process_p_ram=new QLabel("Private usage");
    process_p_ram->setObjectName("cpu-data");
   
    ramVL1->addWidget(ram_us);
    ramVL1->addWidget(t_phy_ram);
    ramVL1->addWidget(ava_ram);
    ramVL1->addWidget(used_ram);
    ramVL1->addWidget(process_w_ram);
    ramVL1->addWidget(process_p_ram);

    QLabel *tempr1=new QLabel("..............");
    tempr1->setObjectName("cpu-temp-holder");
    QLabel *tempr2=new QLabel("..............");
    tempr2->setObjectName("cpu-temp-holder");
    QLabel *tempr3=new QLabel("..............");
    tempr3->setObjectName("cpu-temp-holder");
    QLabel *tempr4=new QLabel("..............");
    tempr4->setObjectName("cpu-temp-holder");
    QLabel *tempr5=new QLabel("..............");
    tempr5->setObjectName("cpu-temp-holder");
    QLabel *tempr6=new QLabel("..............");
    tempr6->setObjectName("cpu-temp-holder");

    ramVL2->addWidget(tempr1);
    ramVL2->addWidget(tempr2);
    ramVL2->addWidget(tempr3);
    ramVL2->addWidget(tempr4);
    ramVL2->addWidget(tempr5);
    ramVL2->addWidget(tempr6);


    QLabel *val_ram_us=new QLabel("87%");
    val_ram_us->setObjectName("cpu-valu");
    QLabel *vt_phy_ram=new QLabel("7834 MB");
    vt_phy_ram->setObjectName("cpu-valu");
    QLabel *vava_ram=new QLabel("985 MB");
    vava_ram->setObjectName("cpu-valu");
    QLabel *vused_ram=new QLabel("6848 MB");
    vused_ram->setObjectName("cpu-valu");
    QLabel *vprocess_w_ram=new QLabel("100 MB");
    vprocess_w_ram->setObjectName("cpu-valu");
    QLabel *vprocess_p_ram=new QLabel("200 MB");
    vprocess_p_ram->setObjectName("cpu-valu");
    
    ramVL3->addWidget(val_ram_us);
    ramVL3->addWidget(vt_phy_ram);
    ramVL3->addWidget(vava_ram);
    ramVL3->addWidget(vused_ram);
    ramVL3->addWidget(vprocess_w_ram);
    ramVL3->addWidget(vprocess_p_ram);
   


    mainlayout->addWidget(ramWidget);

    QVector<double> cpuUsageData = {
    1.20, 1.80, 2.10, 1.50, 2.80,
    3.00, 2.70, 3.20, 2.75
    };

    RamUsageWidget *cpuUsageWidget = new RamUsageWidget(
        "CPU Usage",
        2.75,
        "%",
        100.0,
        cpuUsageData,
        this
    );

    mainlayout->addWidget(cpuUsageWidget);

    QVector<double> ramUsageData = {
    72, 75, 78, 80, 82,
    84, 85, 86, 87
    };

    RamUsageWidget *ramUsageWidget = new RamUsageWidget(
        "RAM Usage",
        87.0,
        "%",
        100.0,
        ramUsageData,
        this
    );

    mainlayout->addWidget(ramUsageWidget);
   


    mainlayout->addStretch();
    

}
