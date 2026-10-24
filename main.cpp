#include <QApplication>
// #include"window/mainwindow.h"
// #include"window/loginwindow.h"
#include"window/onboard.h"
#include<QFile>
#include<QFontDatabase>
#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>
#include<QDebug>
#endif
int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    int id1 = QFontDatabase::addApplicationFont(":/fonts/inter-bold.ttf");
    int id2 = QFontDatabase::addApplicationFont(":/fonts/inter-regl.ttf");
    int id3 = QFontDatabase::addApplicationFont(":/fonts/inter-semibold.ttf");
    if (id1 == -1 || id2 == -1 || id3 == -1) {
        qWarning() << "Warning: One or more Inter fonts failed to load from resources!";
    }
    QFile file(":/styles/global.qss");
    if(file.open(QFile::ReadOnly))
    {
        app.setStyleSheet(file.readAll());
    }
    app.setWindowIcon(QIcon(":/icons/logo.png"));
    OnBoardScreen mainWindow;
    mainWindow.showMaximized();
    #ifdef Q_OS_WIN
    HWND hwnd = reinterpret_cast<HWND>(mainWindow.winId());

    const DWORD DWMWCP_DONOTROUND = 1;
    DwmSetWindowAttribute(
        hwnd,
        33, // DWMWA_WINDOW_CORNER_PREFERENCE
        &DWMWCP_DONOTROUND,
        sizeof(DWMWCP_DONOTROUND)
    );
    #endif


    return app.exec();


}
