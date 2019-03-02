#include "content.h"
#include "utils.h"
#include "newtaskdialog.h"
#include <QVBoxLayout>
#include <QDateTime>
#include <QPainter>
#include <QDebug>

Content::Content(QWidget *parent)
    : QWidget(parent),
      m_toolBar(new TopBar),
      m_tableView(new TableView),
      m_aria2RPC(new Aria2RPC),
      m_refreshTimer(new QTimer(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_tableView);

    m_refreshTimer->setInterval(1000);

    connect(m_toolBar, &TopBar::buttonClicked, this, &Content::handleToolBarClicked);
    connect(m_aria2RPC, &Aria2RPC::addedTask, this, &Content::handleAddedTaskToModel);
    connect(m_aria2RPC, &Aria2RPC::updateStatus, this, &Content::handleUpdateStatus);
    connect(m_refreshTimer, &QTimer::timeout, this, &Content::refreshEvent);
    connect(m_tableView, &TableView::doubleClicked, this, &Content::handleDoubleClicked);
}

void Content::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.fillRect(rect(), QColor("#3A3A3A"));
}

void Content::handleDialogAddTask(const QString &url)
{
    m_aria2RPC->addUri(url, "");
    m_refreshTimer->start();
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
    DataItem *data = m_tableView->customModel()->find(gid);

    if (data == nullptr) return;

    data->totalLength = Utils::formatUnit(totalLength);
    data->completedLength = Utils::formatUnit(completedLength);
    data->speed = (speed != 0) ? Utils::formatSpeed(speed) : "";
    data->fileName = (fileName.isEmpty()) ? Global::UNKNOWN : fileName;
    data->status = status;
    data->percent = percent;
    data->total = totalLength;

    if (totalLength != completedLength && totalLength != 0 &&
        data->status == Global::Status::Active)
    {
        QTime t(0, 0, 0);
        t = t.addSecs((totalLength - completedLength * 1.0) / speed);
        data->time = t.toString("mm:ss");
    } else {
        data->time = "";
    }

//    refreshTableView(m_slideBar->index());
    m_tableView->update();
}

void Content::handleToolBarClicked(const int &index)
{
    if (index == 0) {
        NewTaskDialog *dlg = new NewTaskDialog(this);
        connect(dlg, &NewTaskDialog::startDownload, this, &Content::handleDialogAddTask);
        dlg->exec();
    } else if (index == 1) {
        onPauseBtnClicked();
    } else if (index == 2) {
        onStartBtnClicked();
    } else if (index == 3) {
        onDeleteBtnClicked();
    }
}

void Content::handleDoubleClicked(const QModelIndex &index)
{
    const QString gid = index.data(TableModel::GID).toString();
    const int status = index.data(TableModel::Status).toInt();

    if (status == Global::Status::Active) {
        m_aria2RPC->pause(gid);
    } else {
        m_aria2RPC->unpause(gid);
    }
}

void Content::onStartBtnClicked()
{
    const QModelIndexList &selected = m_tableView->selectionModel()->selectedRows();

    for (const QModelIndex &index : selected) {
        const QString gid = index.data(TableModel::GID).toString();
        const int status = index.data(TableModel::Status).toInt();

        if (status != Global::Status::Active) {
            m_aria2RPC->unpause(gid);
        }
    }
}

void Content::onPauseBtnClicked()
{
    const QModelIndexList &selected = m_tableView->selectionModel()->selectedRows();

    for (const QModelIndex &index : selected) {
        const QString gid = index.data(TableModel::GID).toString();
        const int status = index.data(TableModel::Status).toInt();

        if (status != Global::Status::Paused) {
            m_aria2RPC->pause(gid);
        }
    }
}

void Content::onDeleteBtnClicked()
{
    const QModelIndexList &selected = m_tableView->selectionModel()->selectedRows();
    QList<DataItem *> deleteList;

    for (const QModelIndex &index : selected) {
        const QString gid = index.data(TableModel::GID).toString();
        const int status = index.data(TableModel::Status).toInt();

        if (status != Global::Status::Removed) {
            DataItem *data = m_tableView->customModel()->find(gid);
            deleteList << data;
        }
    }

    for (int i = 0; i < deleteList.size(); ++i) {
        DataItem *data = deleteList.at(i);
        m_aria2RPC->remove(data->gid);
        m_tableView->customModel()->removeItem(data);
    }
}

void Content::refreshEvent()
{
    const QList<DataItem *> dataList = m_tableView->customModel()->dataList();
    int activeCount = 0;

    for (const auto *item : dataList) {
        m_aria2RPC->tellStatus(item->gid);
    }

//    for (const auto *item : dataList) {
//        if (item->status == Global::Status::Active) {
//            ++activeCount;
//        }
//    }

//    if (activeCount == 0) {
//        m_refreshTimer->stop();
//    }

//    setStatusText(dataList.count(), activeCount);
}
