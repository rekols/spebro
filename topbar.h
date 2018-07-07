#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>

class TopBar : public QWidget
{
    Q_OBJECT

public:
    explicit TopBar(QWidget *parent = nullptr);

signals:
    void buttonClicked(const int index);
};

#endif // TOPBAR_H
