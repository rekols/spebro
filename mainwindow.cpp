/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QProcess>
#include <QScreen>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_slideBar(new SlideBar),
      m_content(new Content)
{
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    centralLayout->addWidget(m_slideBar);
    centralLayout->addWidget(m_content);

    startAria2c();
    setWindowTitle("Spebro");
    setWindowIcon(QIcon(":/images/spebro.svg"));
    setCentralWidget(centralWidget);
    setMinimumSize(900, 550);
    move(qApp->primaryScreen()->geometry().center() - geometry().center());
}

MainWindow::~MainWindow()
{
}

void MainWindow::startAria2c()
{
    QProcess *process = new QProcess(this);

    // first killed aria2c.
    process->start("killall aria2c");
    process->waitForFinished(-1);

    QStringList args;
    args << QString("--dir=%1/Desktop").arg(QDir::homePath());
    args << "--enable-rpc=true";
    args << "--rpc-listen-port=7200";
    args << "--rpc-allow-origin-all=true";
    args << "--rpc-save-upload-metadata=true";
    args << "--check-certificate=false";
    args << "--disable-ipv6";

    process->start("/usr/bin/aria2c", args);
}
