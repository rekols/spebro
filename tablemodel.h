#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "global.h"

using namespace Global;

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    enum DataRole {
        FileName = 0, Size, Speed, Time, Status, GID, Percent, TotalLength
    };

    explicit TableModel(QObject *parent = nullptr);

    void append(DataItem *data);

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QList<DataItem *> m_dataList;
};

#endif // TABLEMODEL_H
