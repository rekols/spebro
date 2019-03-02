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

#include "utils.h"
#include <QProcess>
#include <QFile>
#include <QDebug>

Utils::Utils(QObject *parent)
    : QObject(parent)
{

}

Utils::~Utils()
{
}

QString Utils::getQssContent(const QString &filePath)
{
    QFile file(filePath);
    QString qss;

    if (file.open(QIODevice::ReadOnly)) {
        qss = file.readAll();
    }

    return qss;
}

QString Utils::getFileName(const QString &url)
{
    return QString(url).right(url.length() - url.lastIndexOf('/') - 1);
}

QString Utils::formatSpeed(unsigned long long size)
{
    QString result = "";

    if (size < 1024) {
        result = QString::number(size) + " B/s";
    } else if (size / 1024 < 1024) {
        result = QString::number(size * 1.0 / 1024, 'r', 1) + " KB/s";
    } else if (size / 1024 / 1024 < 1024) {
        result = QString::number(size * 1.0 / 1024 / 1024, 'r', 1) + " MB/s";
    } else if (size / 1024 / 1024 / 1024 < 1024) {
        result = QString::number(size * 1.0 / 1024 / 1024 / 1024, 'r', 1) + " GB/s";
    }

    return result;
}

QString Utils::formatUnit(unsigned long long size)
{
    QString result = "";

    if (size < 1024) {
        result = QString::number(size) + "B";
    } else if (size / 1024 < 1024) {
        result = QString::number(size * 1.0 / 1024, 'r', 1) + "KB";
    } else if (size / 1024 / 1024 < 1024) {
        result = QString::number(size * 1.0 / 1024 / 1024, 'r', 1) + "MB";
    } else if (size / 1024 / 1024 / 1024 < 1024) {
        result = QString::number(size * 1.0 / 1024 / 1024 / 1024, 'r', 1) + "GB";
    }

    return result;
}
