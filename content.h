#ifndef CONTENT_H
#define CONTENT_H

#include <QWidget>

class Content : public QWidget
{
    Q_OBJECT

public:
    explicit Content(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // CONTENT_H
