#ifndef CLICKABLEFRAME_H
#define CLICKABLEFRAME_H

#include <QFrame>
#include <QMouseEvent>

    class ClickableFrame : public QFrame
{
    Q_OBJECT
public:
    explicit ClickableFrame(QWidget *parent = nullptr, QString type_frame = nullptr) : QFrame(parent) {

    }

protected:
    void mousePressEvent(QMouseEvent *event) override
    {

    }

signals:
    void clicked(); // Сигнал, который можно подключить к слотам
};

#endif // CLICKABLEFRAME_H
