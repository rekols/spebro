#include "newtaskdialog.h"
#include "iconbutton.h"
#include <QVBoxLayout>
#include <QLabel>

NewTaskDialog::NewTaskDialog(QWidget *parent)
    : QDialog(parent),
      m_linkEdit(new QLineEdit),
      m_pathEdit(new QLineEdit)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *bottomLayout = new QHBoxLayout;

    QLabel *linkTips = new QLabel("链接:");
    QLabel *pathTips = new QLabel("下载目录:");

    IconButton *downloadBtn = new IconButton;
    downloadBtn->setImage(":/images/nav_downloading.svg");
    downloadBtn->setText("下载");
    downloadBtn->setIconSize(QSize(16, 16));

    IconButton *canelBtn = new IconButton;
    canelBtn->setImage(":/images/canel.svg");
    canelBtn->setText("取消");
    canelBtn->setIconSize(QSize(16, 16));

    IconButton *selectBtn = new IconButton;
    selectBtn->setImage(":/images/select_directory.svg");
    selectBtn->setText("选择目录");
    selectBtn->setIconSize(QSize(16, 16));

    m_linkEdit->setFixedHeight(40);
    m_pathEdit->setFixedHeight(40);

    layout->setContentsMargins(QMargins(10, 10, 10, 15));
    layout->addWidget(linkTips);
    layout->addWidget(m_linkEdit);
    layout->addSpacing(10);
    layout->addWidget(pathTips);
    layout->addWidget(m_pathEdit);
    layout->addSpacing(10);
    layout->addStretch();
    layout->addLayout(bottomLayout);

    bottomLayout->addWidget(selectBtn);
    bottomLayout->addWidget(downloadBtn);
    bottomLayout->addWidget(canelBtn);
    bottomLayout->addStretch();

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("新建下载");
    setFixedSize(500, 300);

    // set background color.
    QPalette pa = palette();
    pa.setColor(backgroundRole(), QColor("#3A3A3A"));
    setPalette(pa);

    connect(downloadBtn, &IconButton::clicked, this, &NewTaskDialog::onDownloadBtnClicked);
    connect(canelBtn, &IconButton::clicked, this, &NewTaskDialog::close);
}

void NewTaskDialog::onDownloadBtnClicked()
{
    const QString urls = m_linkEdit->text();

    if (!urls.isEmpty()) {
        Q_EMIT startDownload(urls);
    } else {
        return;
    }

    close();
}
