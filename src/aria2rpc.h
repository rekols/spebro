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

#ifndef ARIA2RPC_H
#define ARIA2RPC_H

#include <QObject>

class QNetworkReply;
class Aria2RPC : public QObject
{
    Q_OBJECT

public:
    Aria2RPC(QObject *parent = nullptr);

signals:
    void addedTask(const QString &gid);
    void updateStatus(const QString &fileName, const QString &gid, const int &status, const long long &totalLength,
                      const long long &completedLenth, const long long &speed, const int &percent);

public slots:
    void addUri(const QString &uri, const QString &id);
    void remove(const QString &gid);
    void pause(const QString &gid);
    void unpause(const QString &gid);
    void tellStatus(const QString &gid);
    void tellActive();
    void tellWaiting();
    void tellStopped();

private:
    void sendMessage(const QString &method, const QString &id, QJsonArray params);
    void handleNetworkReply(QNetworkReply *reply, const QString &method);
    void handleTellStatus(const QJsonObject &object);
};

#endif // ARIA2RPC_H
