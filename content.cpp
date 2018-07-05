#include "content.h"
#include "topbar.h"
#include <QVBoxLayout>
#include <QPainter>

Content::Content(QWidget *parent)
    : QWidget(parent),
      m_tableView(new TableView)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(new TopBar);
    layout->addWidget(m_tableView);

    // test for tableview.
     for (int i = 1; i < 100; ++i) {
         DataItem *data = new DataItem;
         data->gid = QString("r%1").arg(i);
         data->status = Global::Status::Active;
         m_tableView->customModel()->append(data);
     }
}

void Content::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.fillRect(rect(), QColor("#3A3A3A"));
}
