#include "tablemodel.h"
#include <QSize>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

void TableModel::append(DataItem *data)
{
    const int row = m_dataList.size();

    beginInsertRows(QModelIndex(), row, row);
    m_dataList.append(data);
    m_map.insert(data->gid, data);
    endInsertRows();
}

void TableModel::removeItem(DataItem *data)
{
    if (m_map.contains(data->gid)) {
        beginRemoveRows(QModelIndex(), m_dataList.indexOf(data), m_dataList.indexOf(data));
        m_map.remove(data->gid);
        m_dataList.removeOne(data);
        delete data;
        endRemoveRows();
    }
}

void TableModel::removeItems()
{
    beginRemoveRows(QModelIndex(), 0, m_dataList.size());
    qDeleteAll(m_dataList.begin(), m_dataList.end());
    m_dataList.clear();
    m_map.clear();
    endRemoveRows();
}

DataItem *TableModel::find(const QString &gid)
{
    if (m_map.contains(gid)) {
        return m_map.value(gid);
    }

    return nullptr;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_dataList.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const DataItem *data = m_dataList.at(row);
    const QChar sizeSepChar = (!data->totalLength.isEmpty()) ? '/' : ' ';

    switch (role) {
    case TableModel::FileName:
        return data->fileName;
    case TableModel::Size:
        return QString("%1%2%3  %4").arg(data->completedLength).arg(sizeSepChar).arg(data->totalLength).arg(data->percent);
    case TableModel::Speed:
        return (data->status != Global::Status::Paused) ? data->speed : "";
    case TableModel::Time:
        return data->time;
    case TableModel::Status:
        return data->status;
    case TableModel::GID:
        return data->gid;
    case TableModel::Percent:
        return data->percent;
    case TableModel::TotalLength:
        return data->totalLength;
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        // set column width.
        if (role == Qt::SizeHintRole && section == 1) {
            return QSize(300, 50);
        }
    }

    return QVariant();
}
