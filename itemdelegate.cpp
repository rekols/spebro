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

    const QRect textRect = rect.marginsRemoved(QMargins(70, 0, 30, 0));

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

        QImage img = QIcon(":/images/file.svg").pixmap(QSize(32, 32) * qApp->devicePixelRatio()).toImage();
        const int iconY = rect.y() + (rect.height() - img.height() / img.devicePixelRatio()) / 2;
        painter->drawImage(20, iconY, img);

        const QString total = painter->fontMetrics().elidedText(index.data(TableModel::TotalLength).toString(),
                                                               Qt::ElideRight, textRect.width() - 10);

        QRect totalRect = textRect;
        totalRect.setTop(nameRect.bottom() + 2);
        painter->drawText(totalRect, Qt::AlignTop | Qt::AlignLeft, total);

    } else if (column == 1) {

        const int barHeight = 10;
        QRect barRect = textRect;
        barRect.setTop(rect.y() + rect.height() / 2 - barHeight - 5);
        barRect.setHeight(barHeight);

        QRect speedRect = textRect;
        speedRect.setTop(barRect.bottom() + 6);

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

        QString speedText = painter->fontMetrics().elidedText(index.data(TableModel::Speed).toString(),
                                                                   Qt::ElideRight, textRect.width() - 10);

        if (index.data(TableModel::Status) == Global::Status::Paused) {
            speedText = "暂停中";
        }

        painter->drawText(speedRect, Qt::AlignTop | Qt::AlignLeft, speedText);
        painter->drawText(speedRect, Qt::AlignTop | Qt::AlignRight, index.data(TableModel::Time).toString());

    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    // don't work here.
    return QSize(-1, 50);
}
