/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "slidebutton.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>

SlideButton::SlideButton(QWidget *parent)
    : QPushButton(parent),
      m_iconWidget(new QSvgWidget),
      m_textLabel(new QLabel)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_iconWidget, 0, Qt::AlignVCenter);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(m_textLabel, 0, Qt::AlignVCenter);

    m_textLabel->setStyleSheet("QLabel { color: #FFFFFF; }");
    m_iconWidget->setFixedSize(16, 16);

    setLayout(mainLayout);
    setFixedHeight(50);
}

SlideButton::~SlideButton()
{
}

void SlideButton::setImage(const QString &filePath)
{
    m_iconWidget->load(filePath);
}

void SlideButton::setText(const QString &text)
{
    m_textLabel->setText(text);
}

void SlideButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (!isChecked())
        return;

    // draw left separator line.
    QRect leftRect(0, 10, 5, rect().height() - 20);
    painter.fillRect(leftRect, QColor("#0078D7"));
}
