#include "customchartview.h"

void CustomChartView::paintEvent(QPaintEvent *event) {
    QChartView::paintEvent(event); // Вызов метода базового класса

    // Рисуем текст в центре диаграммы
    QPainter painter(this);
    painter.setPen(Qt::black); // Цвет текста
    painter.setFont(QFont("Inter", 16)); // Шрифт и размер текста

    // Получаем размеры диаграммы
    QRectF rect = this->rect();
    QString text; // Текст для отображения

    // Рисуем текст в центре
    painter.drawText(rect, Qt::AlignCenter, text);
}
