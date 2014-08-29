#include "setupwizard.h"
#include "futil.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setSkinForApp("://skin/theme.qss");
    SetupWizard w;
    w.show();
    return a.exec();
}
