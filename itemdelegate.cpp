#include "itemdelegate.h"
#include "tablemodel.h"
#include <QStyleOptionViewItem>
#include <QStyleOptionProgressBar>
#include <QProgressBar>
#include <QApplication>
#include <QPainter>

ItemDelegate::ItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QRect rect(option.rect);
    const int column(index.column());
    const bool isSelected = option.state & QStyle::State_Selected;

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::white);

    const QRect textRect = rect.marginsRemoved(QMargins(10, 0, 0, 0));

    // painting each column item.
    if (column == 0) {

        const QString name = painter->fontMetrics().elidedText(index.data(TableModel::FileName).toString(),
                                                               Qt::ElideRight, textRect.width() - 10);
        const QString size = painter->fontMetrics().elidedText(index.data(TableModel::Size).toString(),
                                                               Qt::ElideRight, textRect.width() - 10);
        QRect nameRect = textRect;
        nameRect.setHeight(rect.height() / 2);
        painter->drawText(nameRect, Qt::AlignBottom | Qt::AlignLeft, name);

        QRect sizeRect = textRect;
        sizeRect.setTop(nameRect.bottom());
        painter->drawText(sizeRect, Qt::AlignTop | Qt::AlignLeft, size);

    } else if (column == 1) {

        QRect sizeRect = textRect;
        sizeRect.setHeight(sizeRect.height() / 1.8);

        QRect barRect = sizeRect;
        barRect.setTop(sizeRect.bottom() + 7);
        barRect.setWidth(barRect.width() - 10);
        barRect.setHeight(15);

        QStyleOptionViewItem viewOption(option);
        initStyleOption(&viewOption, index);

        QStyleOptionProgressBar *optionBar = new QStyleOptionProgressBar;
        optionBar->initFrom(option.widget);
        optionBar->rect = barRect;
        optionBar->minimum = 0;
        optionBar->maximum = 100;
        optionBar->progress = index.data(TableModel::Percent).toInt();

        QProgressBar *progressbar = new QProgressBar;
        QApplication::style()->drawControl(QStyle::CE_ProgressBarContents, optionBar, painter, progressbar);

        const QString sizeText = painter->fontMetrics().elidedText(index.data(TableModel::Size).toString() + "%", Qt::ElideRight, textRect.width() - 10);
        painter->drawText(sizeRect, Qt::AlignBottom | Qt::AlignLeft, sizeText);

    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    // don't work here.
    return QSize(-1, 50);
}
