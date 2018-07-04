#include "content.h"
#include "topbar.h"
#include <QVBoxLayout>
#include <QPainter>

Content::Content(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(new TopBar);
    layout->addStretch();
}

void Content::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.fillRect(rect(), QColor("#3A3A3A"));
}
