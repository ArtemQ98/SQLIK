#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QChart>
#include <QChartView>

class CustomChartView : public QChartView {
public:
    CustomChartView(QChart *chart, QWidget *parent = nullptr) : QChartView(chart, parent) {}

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CUSTOMCHARTVIEW_H

