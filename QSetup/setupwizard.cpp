/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include <QApplication>
#include <QDesktopWidget>
#include <QProcessEnvironment>
#include <QResource>
#include <QSettings>
#include <QFileDialog>
#include "SetupWizard.h"
#include "pictureview.h"


SetupWizard::SetupWizard(QWidget *parent)
    : FBaseDialog(parent)
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    setWindowTitle(tr("Setup"));
    initData();
    initUI();
    initConnect();
}

void SetupWizard::initData()
{
    largeHeight = 500;
    smallHeight = 437;
    cmd = new QProcess;

    QSettings *configer = new QSettings(":/appConfig/example/qrcfiles/app.ini", QSettings::IniFormat);
    configer->beginGroup("Basic");
    obj = configer->value("appfoldername").toString();
    appExeName = configer->value("appexename").toString();
    count7z = configer->value("count7z").toInt();
    defaultInstallPath = QDir(configer->value("appdestinationdir").toString()).absolutePath();
    isShortCut = (bool)configer->value("isShortCut").toInt();
    progressDuration = 2800;
}

void SetupWizard::initUI()
{
    PictureView* pictureView = new PictureView;
    pictureView->setFixedHeight(300);

    progressBar = new QProgressBar(this);
    progressBar->setFixedHeight(10);
    progressBar->setObjectName(QString("AntimationBar"));
    progressBar->setRange(0, 100);
    progressBarAnimation = new QPropertyAnimation(progressBar, "value");
    progressBarAnimation->setDuration(progressDuration);
    progressBarAnimation->setStartValue(0);
    progressBarAnimation->setEndValue(100);
    progressBarAnimation->setEasingCurve(QEasingCurve::OutCubic);

    setupPathLineEdit = new QLineEdit(QDir::toNativeSeparators(QString("%1/%2").arg(defaultInstallPath, obj)));
    setupPathLineEdit->setFixedHeight(30);
    setupPathLineEdit->setObjectName("setupPathLineEdit");
    changePathButton = new QPushButton("...");
    changePathButton->setFixedSize(60, 30);
    installButton = new QPushButton("Quick install");
    installButton->setObjectName("installButton");
    installButton->setFixedSize(200, 50);

    QLabel* settingLabel = new QLabel(tr("Custom options"));
    settingButton = new QToolButton;
    settingButton->setObjectName("settingButton");
    settingButton->setFixedSize(QSize(36, 36));
    QHBoxLayout* settingLayout = new QHBoxLayout;
    settingLayout->addStretch();
    settingLayout->addWidget(settingLabel);
    settingLayout->addWidget(settingButton);
    settingLayout->addSpacing(5);

    settingWidget = new QWidget;
    QVBoxLayout* settingMainLayout = new QVBoxLayout;
    QHBoxLayout* pathLayout = new QHBoxLayout;
    pathLayout->setSpacing(0);
    pathLayout->addSpacing(20);
    pathLayout->addWidget(setupPathLineEdit);
    pathLayout->addWidget(changePathButton);
    pathLayout->addSpacing(20);
    pathLayout->setContentsMargins(0, 0, 0, 0);

    settingMainLayout->addLayout(pathLayout);
    settingWidget->setLayout(settingMainLayout);

    QHBoxLayout* navLayout = new QHBoxLayout;
    navLayout->addStretch();
    navLayout->addWidget(installButton);
    navLayout->addStretch();

    QVBoxLayout* mainLayout = (QVBoxLayout*)layout();

    mainLayout->addWidget(pictureView);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(navLayout);
    mainLayout->addWidget(settingWidget);
    mainLayout->addStretch();
    mainLayout->addLayout(settingLayout);
    mainLayout->addWidget(progressBar);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

    normalSize = size();
    progressBar->hide();
    settingWidget->hide();
    setFixedWidth(587);
    resize(QSize(587, smallHeight));
}

void SetupWizard::initConnect()
{
    connect(installButton, SIGNAL(clicked()), this, SLOT(progressAnimation()));
    connect(installButton, SIGNAL(clicked()), this, SLOT(install()));
    connect(settingButton, SIGNAL(clicked()), this, SLOT(showOptionAnimation()));
    connect(settingButton, SIGNAL(clicked()), this, SLOT(showOptionSettings()));
    connect(changePathButton, SIGNAL(clicked()), this, SLOT(changePath()));
    connect(progressBarAnimation, SIGNAL(finished()), progressBarAnimation, SLOT(start()));
    connect(cmd, SIGNAL(readyRead()), this, SLOT(setOutPut()));
}


void SetupWizard::moveCenter()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    int x = (desktopWidget->availableGeometry().size().width() - width()) / 2;
    int y = (desktopWidget->availableGeometry().size().height() - height()) / 2;
    move(x , y);
}

void SetupWizard::showOptionAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    disconnect(animation, SIGNAL(finished()), settingWidget, 0);
    if (height() == smallHeight)
    {
        animation->setStartValue(geometry());
        animation->setEndValue(QRect(x(), y(), width(),largeHeight));
        connect(animation, SIGNAL(finished()), settingWidget, SLOT(show()));
    }
    else if (height() == largeHeight)
    {
        animation->setStartValue(geometry());
        animation->setEndValue(QRect(x(), y(), width(), smallHeight));
        settingWidget->hide();
    }
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::InOutCubic);
    animation->start();
}

void SetupWizard::showOptionSettings()
{

}


void SetupWizard::createLink()
{
    QString linkScript;
    if(isShortCut)
    {
        linkScript = QString("$shell = New-Object -ComObject WScript.Shell;\n\
                                     $desktop = [System.Environment]::GetFolderPath('Desktop');\n\
                                     $shortcut = $shell.CreateShortcut(\"$desktop\\%1.lnk\");\n\
                                     $shortcut.TargetPath = \"%2\";\n\
                                     $shortcut.IconLocation = \"%3,0\";\n\
                                     $shortcut.WorkingDirectory  = \"%4\";\n\
                                     $shortcut.Save();\n\
                                     $shell.CurrentDirectory=\"%5\";\n\
                                     $shell.exec(\"%6\");\n\
                                     echo craeteLinkok;");
        QString command = QString("%1/%2/%3").arg(defaultInstallPath, obj, appExeName);
        QString workingDirectory = QString("%1/%2/").arg(defaultInstallPath, obj);
        QString exePath = QDir::toNativeSeparators(command);
        linkScript = linkScript.arg(obj, exePath, exePath, workingDirectory,workingDirectory, command);
    }
    else{
        linkScript = QString("$shell = New-Object -ComObject WScript.Shell;\n\
                                     $shell.CurrentDirectory=\"%1\";\n\
                                     $shell.exec(\"%2\");\n\
                                     echo craeteLinkok;");\
        QString command = QString("%1/%2/%3").arg(defaultInstallPath, obj, appExeName);
        QString workingDirectory = QString("%1/%2/").arg(defaultInstallPath, obj);
        linkScript = linkScript.arg(workingDirectory, command);
    }

    QFile file("link.ps1");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << linkScript;
    file.close();

    powershellProcess = new QProcess;
//    qDebug(qPrintable(linkScript));
    connect(powershellProcess, SIGNAL(readyRead()), this, SLOT(clearLinkFile()));
    powershellProcess->start(QString("powershell ./link.ps1"));
}


void SetupWizard::clearLinkFile()
{
    psInfo += powershellProcess->readAll();
//    qDebug(qPrintable(psInfo));
    if (psInfo.contains("craeteLinkok"))
    {
        rmFile("link.ps1");
//        qDebug(qPrintable("delete linkps1"));
        qApp->quit();
    }
}

void SetupWizard::changePath()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose setup Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    defaultInstallPath = dir;
    setupPathLineEdit->setText(QDir::toNativeSeparators(dir));
}

void SetupWizard::progressAnimation()
{
    if(installButton->text() == QString("Quick install")){
        progressBar->show();
        progressBar->setTextVisible(true);
        progressBarAnimation->start();
    }
}

void SetupWizard::progressAnimationClose()
{
    progressBar->setTextVisible(false);
    QPropertyAnimation *animation = new QPropertyAnimation(progressBar, "geometry");
    connect(animation, SIGNAL(finished()), progressBar, SLOT(hide()));
    animation->setDuration(500);
    int h = progressBar->height();
    animation->setStartValue(progressBar->geometry());
    animation->setEndValue(QRect(progressBar->x(), progressBar->y() + h * 0.5 + 5, progressBar->width(), 0));
    animation->start();
}

void SetupWizard::mousePressEvent(QMouseEvent *e)
{
    if(e->button() & Qt::LeftButton)
    {
        dragPosition = e->globalPos() - frameGeometry().topLeft();
        leftbuttonpressed = true;
    }
    e->accept();
}


void SetupWizard::mouseReleaseEvent(QMouseEvent *e)
{
    leftbuttonpressed = false;
    e->accept();
}

void SetupWizard::mouseMoveEvent(QMouseEvent *e)
{
    if(leftbuttonpressed)
    {
        move(e->globalPos() - dragPosition);
        e->accept();
    }
}

void SetupWizard::closeEvent(QCloseEvent *event)
{

    cmd->kill();
    delete cmd;
    cmd = NULL;
    FBaseDialog::closeEvent(event);
}

void SetupWizard::install()
{
    if(installButton->text() == QString("Quick install")){
        rmDir(QString("%1/%2").arg(defaultInstallPath, obj));
        QString installPath = defaultInstallPath;
        tempf = QDir::toNativeSeparators(QString("%1/%2").arg(QDir::tempPath(), obj));
        rmDir(installPath);
        QDir().mkdir(installPath);
        QDir().rmdir(tempf);
        QDir().mkdir(tempf);
        install7z(tempf);
        command_7z = QString("%1/7z.exe x %2/%3.7z.001 -o\"%4\"").arg(tempf, tempf, obj, QDir::toNativeSeparators(defaultInstallPath));
//        qDebug(qPrintable(command_7z));
        info = command_7z;
        cmd->start(command_7z);
    }
    else if (installButton->text() == QString("Quick experience")){
        createLink();
        clearLinkFile();
    }
}

void SetupWizard::setOutPut()
{
    info += cmd->readAll();
//    qDebug(qPrintable(info));
    if(info.contains("Everything is Ok"))
    {
        installButton->setText(tr("Quick experience"));
        progressBar->setValue(100);
        progressBarAnimation->stop();
        progressAnimationClose();
    }
}

void SetupWizard::install7z(QString& tempf)
{
    if (QFile::exists(QString("%1/7z.dll").arg(tempf)))
    {
        rmFile(QString("%1/7z.dll").arg(tempf));
    }
    QString srcfName;
    srcfName = QString(":/7-Zip/7-Zip/%1").arg("7z.dll");
    instIndvfl(srcfName, QString("%1/7z.dll").arg(tempf));

    if (QFile::exists(QString("%1/7z.exe").arg(tempf)))
    {
        rmFile(QString("%1/7z.exe").arg(tempf));
    }
    srcfName = QString(":/7-Zip/7-Zip/%1").arg("7z.exe");
    instIndvfl(srcfName, QString("%1/7z.exe").arg(tempf));

    QStringList files;
    for(int i=1; i<count7z + 1; i++)
    {
        QString fname = QString("%1.7z.00").arg(obj) + QString::number(i);
        QString fpath = QString(":/%1/example/qrcfiles/").arg(obj) + fname;
        files << fpath;
        QString ftemppath = QString("%1/%2").arg(tempf, fname);

        if (QFile::exists(ftemppath))
        {
            rmFile(ftemppath);
        }
        srcfName = fpath;
        instIndvfl(srcfName, ftemppath);
    }
}

void SetupWizard::rmFile(QFile &fn)
{
    if (!fn.exists()) return;
    fn.setPermissions(QFile::WriteUser);
    fn.remove();
}

void SetupWizard::rmFile(const QString &fn)
{
    if (!QFile::exists(fn)) return;
    QFile::setPermissions(fn, QFile::WriteUser);
    QFile::remove(fn);
}

void SetupWizard::instIndvfl(QString srcfName, QString dstfName)
{
    QFile srcF(srcfName);
    if (!srcF.exists())
    {
        return;
    }
    if (QFile::exists(dstfName))
    {
        rmFile(dstfName);
    }
    QFile dstF(dstfName);
    dstF.open(QIODevice::WriteOnly);
    srcF.open(QIODevice::ReadOnly);
    dstF.write(srcF.readAll());
    dstF.close();
    srcF.close();
}


bool SetupWizard::rmDir(const QString &fn)
{
    bool result = true;
    QDir dir(fn);

    if (dir.exists(fn)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = rmDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(fn);
    }
    return result;
}


