#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

void TableModel::append(DataItem *data)
{
    const int row = m_dataList.size();

    beginInsertRows(QModelIndex(), row, row);
    m_dataList.append(data);
    endInsertRows();
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
        return data->total;
    }

    return QVariant();
}
