#ifndef SetupWizard_H
#define SetupWizard_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFile>
#include <QTextEdit>
#include <QProgressBar>
#include <QProcess>
#include <QCloseEvent>
#include <QPropertyAnimation>
#include "fbasedialog.h"


//! [0] //! [1]
class SetupWizard : public FBaseDialog
{

    Q_OBJECT
public:
    QPushButton* installButton;
    QPushButton* changePathButton;
    QLineEdit* setupPathLineEdit;
    QLabel* setupLabel;
    QTextEdit* outPutEdit;
    QString tempf;
    QString command_7z;
    QString info;
    QProcess* cmd;
    QString obj;
    QString appExeName;
    QString defaultInstallPath;

    QPoint dragPosition;
    bool leftbuttonpressed;

    QProgressBar* progressBar;
    QPropertyAnimation* progressBarAnimation;
    int progressDuration;

public:
    explicit SetupWizard(QWidget *parent = 0);
    void initUI();
    void initData();
    void initConnect();
    void install7z(QString& tempf);
    void instIndvfl(QString srcfName, QString dstfName);
    void rmFile(QFile &fn);
    void rmFile(const QString &fn);
    bool rmDir(const QString &fn);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void closeEvent(QCloseEvent * e);

public slots:
    void install();
    void setOutPut();
    void progressAnimation();
    void progressAnimationClose();
};

#endif
