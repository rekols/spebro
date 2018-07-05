#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include "tablemodel.h"

class TableView : public QTableView
{
    Q_OBJECT

public:
    explicit TableView(QWidget *parent = nullptr);

    TableModel *customModel() { return m_model; };

private:
    TableModel *m_model;
};

#endif // TABLEVIEW_H
