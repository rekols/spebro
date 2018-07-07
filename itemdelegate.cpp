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

    // painting selection item background.
    if (isSelected) {
        painter->fillRect(rect, QColor("#4D4D4D"));
    }

    const QRect textRect = rect.marginsRemoved(QMargins(10, 0, 0, 0));

    // painting each column item.
    if (column == 0) {

        const QString name = painter->fontMetrics().elidedText(index.data(TableModel::FileName).toString(),
                                                               Qt::ElideRight, textRect.width() - 10);

        QRect nameRect = textRect;
        nameRect.setHeight(rect.height() / 2);
        painter->drawText(nameRect, Qt::AlignBottom | Qt::AlignLeft, name);

        if (index.data(TableModel::TotalLength) == 0) {
            return;
        }
        const QString total = painter->fontMetrics().elidedText(index.data(TableModel::TotalLength).toString(),
                                                               Qt::ElideRight, textRect.width() - 10);

        QRect totalRect = textRect;
        totalRect.setTop(nameRect.bottom());
        painter->drawText(totalRect, Qt::AlignTop | Qt::AlignLeft, total);

    } else if (column == 1) {

        const int barHeight = 10;
        QRect barRect = textRect;
        barRect.setTop(rect.y() + rect.height() / 2 - barHeight - 5);
        barRect.setWidth(barRect.width() - 20);
        barRect.setHeight(barHeight);

        QRect sizeRect = textRect;
        sizeRect.setTop(barRect.bottom() + 5);

        QStyleOptionViewItem viewOption(option);
        initStyleOption(&viewOption, index);

        QStyleOptionProgressBar *optionBar = new QStyleOptionProgressBar;
        optionBar->initFrom(option.widget);
        optionBar->rect = barRect;
        optionBar->minimum = 0;
        optionBar->maximum = 100;
        optionBar->progress = index.data(TableModel::Percent).toInt();

        QProgressBar *progressbar = new QProgressBar;
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, optionBar, painter, progressbar);

        const QString sizeText = painter->fontMetrics().elidedText(index.data(TableModel::Speed).toString(),
                                                                   Qt::ElideRight, textRect.width() - 10);
        painter->drawText(sizeRect, Qt::AlignTop | Qt::AlignLeft, sizeText);

    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    // don't work here.
    return QSize(-1, 50);
}
