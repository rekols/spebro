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

#ifndef SLIDEBUTTON_H
#define SLIDEBUTTON_H

#include <QPushButton>
#include <QSvgWidget>
#include <QLabel>

class SlideButton : public QPushButton
{
    Q_OBJECT

public:
    SlideButton(QWidget *parent = nullptr);
    ~SlideButton();

    void setImage(const QString &filePath);
    void setText(const QString &text);

protected:
    void paintEvent(QPaintEvent *);

private:
    QSvgWidget *m_iconWidget;
    QLabel *m_textLabel;
};

#endif
