#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>

namespace Global
{
    const QString ACTIVE = QObject::tr("Downloading");
    const QString WAITING = QObject::tr("Waiting");
    const QString PAUSED = QObject::tr("Paused");
    const QString ERROR = QObject::tr("Error");
    const QString COMPLETE = QObject::tr("Complete");
    const QString REMOVED = QObject::tr("Removed");
    const QString UNKNOWN = QObject::tr("Unknown");

    struct DataItem {
        int status = 0;
        int percent = 0;
        int total = 0;

        QString fileName = Global::UNKNOWN;
        QString completedLength;
        QString totalLength;
        QString savePath;
        QString speed;
        QString gid;
        QString url;
        QString time;
    };

    enum Status {
        Active = 0, Waiting, Paused, Error, Complete, Removed
    };

};


#endif

