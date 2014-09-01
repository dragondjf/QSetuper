#include "QSetup/setupwizard.h"
#include "QSetup/futil.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setSkinForApp("://skin/theme.qss");
    SetupWizard w;
    w.show();
    return a.exec();
}
