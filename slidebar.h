#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QButtonGroup>

class SlideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SlideBar(QWidget *parent = nullptr);

signals:
    void buttonClicked(const int index);

protected:
    void paintEvent(QPaintEvent *);

private:
    QVBoxLayout *m_layout;
    QButtonGroup *m_buttonGroup;
};

#endif // SLIDEBAR_H
