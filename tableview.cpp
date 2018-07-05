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
    verticalHeader()->setDefaultSectionSize(50);
    headerView->setSectionResizeMode(0, QHeaderView::Stretch);
    headerView->setSectionResizeMode(1, QHeaderView::Stretch);
    headerView->setHighlightSections(false);
    headerView->setVisible(false);

    QHeaderView *vheaderView = verticalHeader();
    vheaderView->setSectionResizeMode(QHeaderView::Fixed);
    vheaderView->setDefaultSectionSize(80);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setAlternatingRowColors(false);
    setSortingEnabled(false);
    setShowGrid(false);

    resizeColumnsToContents();
}
