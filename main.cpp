#include "setupwizard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetupWizard w;
    w.show();
    return a.exec();
}
