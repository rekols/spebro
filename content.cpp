#include "content.h"
#include <QVBoxLayout>
#include <QPainter>

Content::Content(QWidget *parent)
    : QWidget(parent),
      m_toolBar(new TopBar),
      m_tableView(new TableView),
      m_aria2RPC(new Aria2RPC)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_tableView);

    // test for tableview.
     for (int i = 1; i < 5; ++i) {
         DataItem *data = new DataItem;
         data->gid = QString("r%1").arg(i);
         data->status = Global::Status::Active;
         m_tableView->customModel()->append(data);
     }

//    connect(m_aria2RPC, &Aria2RPC::addedTask, this, &MainWindow::handleAddedTaskToModel);
//    connect(m_aria2RPC, &Aria2RPC::updateStatus, this, &MainWindow::handleUpdateStatus);
}

void Content::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.fillRect(rect(), QColor("#3A3A3A"));
}

void Content::handleAddedTaskToModel(const QString &gid)
{
    DataItem *data = new DataItem;
    data->gid = gid;

    m_tableView->customModel()->append(data);
}

void Content::handleUpdateStatus(const QString &fileName, const QString &gid, const int &status,
                                    const long long &totalLength, const long long &completedLength,
                                    const long long &speed, const int &percent)
{
}
