#ifndef CONTENT_H
#define CONTENT_H

#include <QWidget>
#include <QTimer>
#include "topbar.h"
#include "tableview.h"
#include "aria2rpc.h"

class Content : public QWidget
{
    Q_OBJECT

public:
    explicit Content(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void handleDialogAddTask(const QString &url);
    void handleAddedTaskToModel(const QString &gid);
    void handleUpdateStatus(const QString &fileName, const QString &gid, const int &status,
                                const long long &totalLength, const long long &completedLenth,
                                const long long &speed, const int &percent);
    void handleToolBarClicked(const int &index);
    void handleDoubleClicked(const QModelIndex &index);
    void onStartBtnClicked();
    void onPauseBtnClicked();
    void onDeleteBtnClicked();
    void refreshEvent();

private:
    TopBar *m_toolBar;
    TableView *m_tableView;
    Aria2RPC *m_aria2RPC;
    QTimer *m_refreshTimer;
};

#endif // CONTENT_H
