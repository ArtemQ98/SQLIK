#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>

QVariant MainWindow::getValueFromDatabase(const QString& queryString) {
    QVariant result;

    QSqlQuery query;
    query.prepare(queryString);

    if (query.exec()) {
        if (query.next()) { // Переходим к первой строке результата
            result = query.value(0); // Извлекаем значение из первого столбца
        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }

    return result;
}
