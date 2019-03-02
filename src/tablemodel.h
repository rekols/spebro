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
    void removeItem(DataItem *data);
    void removeItems();
    DataItem *find(const QString &gid);
    const QList<DataItem *> dataList() { return m_dataList; };

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<DataItem *> m_dataList;
    QMap<QString, DataItem *> m_map;
};

#endif // TABLEMODEL_H
