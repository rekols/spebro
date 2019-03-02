#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>
#include <QSvgWidget>
#include <QLabel>

class IconButton : public QPushButton
{
    Q_OBJECT

public:
    explicit IconButton(QWidget *parent = nullptr);

    void setImage(const QString &filePath);
    void setText(const QString &text);
    void setIconSize(const QSize &size);

private:
    QSvgWidget *m_iconWidget;
    QLabel *m_textLabel;
};

#endif // ICONBUTTON_H
