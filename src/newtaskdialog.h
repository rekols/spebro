#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include <QDialog>
#include <QLineEdit>

class NewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskDialog(QWidget *parent = nullptr);

signals:
    void startDownload(const QString &url);

private slots:
    void initDownloadFolder();
    void onDownloadBtnClicked();

private:
    QLineEdit *m_linkEdit;
    QLineEdit *m_pathEdit;
};

#endif // NEWTASKDIALOG_H
