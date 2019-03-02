#include "slidebar.h"
#include "slidebutton.h"
#include <QPainter>

SlideBar::SlideBar(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout),
      m_buttonGroup(new QButtonGroup)
{
    SlideButton *downloadingBtn = new SlideButton;
    SlideButton *finishedBtn = new SlideButton;

    downloadingBtn->setText(tr("Downloading"));
    finishedBtn->setText(tr("Finished"));

    downloadingBtn->setImage(":/images/nav_downloading.svg");
    finishedBtn->setImage(":/images/nav_finished.svg");

    downloadingBtn->setCheckable(true);
    finishedBtn->setCheckable(true);

    downloadingBtn->setChecked(true);

    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    m_layout->addSpacing(5);
    m_layout->addWidget(downloadingBtn);
    m_layout->addSpacing(5);
    m_layout->addWidget(finishedBtn);
    m_layout->addStretch();

    m_buttonGroup->addButton(downloadingBtn);
    m_buttonGroup->addButton(finishedBtn);

    setObjectName("SlideBar");
    setFixedWidth(210);
    setLayout(m_layout);

    connect(downloadingBtn, &QPushButton::clicked, this, [=] {
        Q_EMIT buttonClicked(0);
    });

    connect(finishedBtn, &QPushButton::clicked, this, [=] {
        Q_EMIT buttonClicked(1);
    });
}

void SlideBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.fillRect(rect(), QColor("#2B2B2B"));
}
