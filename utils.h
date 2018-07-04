#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);

    static QString getQssContent(const QString &filePath);

signals:

public slots:
};

#endif // UTILS_H
