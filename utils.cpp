#include "utils.h"
#include <QFile>

Utils::Utils(QObject *parent) : QObject(parent)
{

}

QString Utils::getQssContent(const QString &filePath)
{
    QFile file(filePath);
    QString content;

    if (file.open(QIODevice::ReadOnly)) {
        content = file.readAll();
    }

    return content;
}
