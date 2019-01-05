#include "topbar.h"
#include "iconbutton.h"
#include <QHBoxLayout>

TopBar::TopBar(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    IconButton *newTaskBtn = new IconButton;
    newTaskBtn->setText(tr("New Task"));
    newTaskBtn->setImage(":/images/new_enable.svg");

    IconButton *pauseBtn = new IconButton;
    pauseBtn->setText(tr("Pause"));
    pauseBtn->setImage(":/images/pause_enable.svg");

    IconButton *continueBtn = new IconButton;
    continueBtn->setText(tr("Continue"));
    continueBtn->setImage(":/images/continue_enable.svg");

    IconButton *deleteBtn = new IconButton;
    deleteBtn->setText(tr("Delete"));
    deleteBtn->setImage(":/images/delete_enable.svg");

    layout->addWidget(newTaskBtn);
    layout->addSpacing(10);
    layout->addWidget(pauseBtn);
    layout->addSpacing(10);
    layout->addWidget(continueBtn);
    layout->addSpacing(10);
    layout->addWidget(deleteBtn);
    layout->addStretch();

    setFixedHeight(100);

    connect(newTaskBtn, &IconButton::clicked, this, [=] { emit buttonClicked(0); });
    connect(pauseBtn, &IconButton::clicked, this, [=] { emit buttonClicked(1); });
    connect(continueBtn, &IconButton::clicked, this, [=] { emit buttonClicked(2); });
    connect(deleteBtn, &IconButton::clicked, this, [=] { emit buttonClicked(3); });
}
