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
#include <QProcessEnvironment>
#include <QResource>
#include "SetupWizard.h"

SetupWizard::SetupWizard(QWidget *parent)
    : QDialog(parent)
{

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle(tr("Setup"));
    setFixedSize(400, 300);
    initData();
    initUI();
    initConnect();
}

void SetupWizard::initData()
{
    cmd = new QProcess;
    obj = "QFramer";
    defaultInstallPath = "E:\\";
}

void SetupWizard::initUI()
{
    setupLabel = new QLabel("Setup path:");
    setupPathLineEdit = new QLineEdit(defaultInstallPath + obj);
    changePathButton = new QPushButton("...");
    installButton = new QPushButton("install");
    outPutEdit = new QTextEdit;

    QHBoxLayout* pathLayout = new QHBoxLayout;
    pathLayout->addWidget(setupLabel);
    pathLayout->addWidget(setupPathLineEdit);
    pathLayout->addWidget(changePathButton);

    QHBoxLayout* navLayout = new QHBoxLayout;
    navLayout->addStretch();
    navLayout->addWidget(installButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(outPutEdit);
    mainLayout->addLayout(pathLayout);
    mainLayout->addLayout(navLayout);

    setLayout(mainLayout);

    rmDir(setupPathLineEdit->text());
}

void SetupWizard::initConnect()
{
    connect(installButton, SIGNAL(clicked()), this, SLOT(install()));
    connect(cmd, SIGNAL(readyRead()), this, SLOT(setOutPut()));
}


void SetupWizard::install()
{
    outPutEdit->setText("");

    QString installPath = setupPathLineEdit->text();
    tempf = QDir::toNativeSeparators(QString("%1\\%2").arg(QDir::tempPath(), obj));
    rmDir(installPath);
    QDir().mkdir(installPath);
    QDir().rmdir(tempf);
    QDir().mkdir(tempf);
    install7z(tempf);
    command_7z = QString("%1\\7z.exe x %2\\%3.7z.001 -o%4").arg(tempf, tempf, obj, defaultInstallPath);
    info = command_7z;
    cmd->start(command_7z);
}

void SetupWizard::setOutPut()
{
    info += cmd->readAll();
    outPutEdit->setText(info);
}

void SetupWizard::install7z(QString& tempf)
{
    if (QFile::exists(QString("%1\\7z.dll").arg(tempf)))
    {
        rmFile(QString("%1\\7z.dll").arg(tempf));
    }
    QString srcfName;
    srcfName = QString(":/7-Zip/7-Zip/%1").arg("7z.dll");
    instIndvfl(srcfName, QString("%1\\7z.dll").arg(tempf));

    if (QFile::exists(QString("%1\\7z.exe").arg(tempf)))
    {
        rmFile(QString("%1\\7z.exe").arg(tempf));
    }
    srcfName = QString(":/7-Zip/7-Zip/%1").arg("7z.exe");
    instIndvfl(srcfName, QString("%1\\7z.exe").arg(tempf));

    QString obj = "QFramer";
    QStringList files;
    for(int i=1; i<4; i++)
    {
        QString fname = QString("%1.7z.00").arg(obj) + QString::number(i);
        QString fpath = QString(":/QFramer/example/qrcfiles/") + fname;
        files << fpath;
        QString ftemppath = QString("%1\\%2").arg(tempf, fname);

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
