#ifndef CONTENT_H
#define CONTENT_H

#include <QWidget>
#include "tableview.h"

class Content : public QWidget
{
    Q_OBJECT

public:
    explicit Content(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);

private:
    TableView *m_tableView;
};

#endif // CONTENT_H
