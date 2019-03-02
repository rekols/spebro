#include "tableview.h"
#include "itemdelegate.h"
#include <QHeaderView>

TableView::TableView(QWidget *parent)
    : QTableView(parent),
      m_model(new TableModel)
{
    setModel(m_model);
    setItemDelegate(new ItemDelegate);

    QHeaderView *headerView = horizontalHeader();
    headerView->setSectionResizeMode(0, QHeaderView::Stretch);
    headerView->setSectionResizeMode(1, QHeaderView::Fixed);
    headerView->setVisible(false);

    // set row height.
    QHeaderView *vheaderView = verticalHeader();
    vheaderView->setDefaultSectionSize(80);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setAlternatingRowColors(true);
    setSortingEnabled(true);
    setShowGrid(false);

    resizeColumnsToContents();
}
