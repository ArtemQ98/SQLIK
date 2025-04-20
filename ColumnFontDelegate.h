#ifndef COLUMNFONTDELEGATE_H
#define COLUMNFONTDELEGATE_H
#include <QStyledItemDelegate>
#include <QFont>

class ColumnFontDelegate : public QStyledItemDelegate {
public:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override {
        QStyledItemDelegate::initStyleOption(option, index);

        // Настраиваем шрифт только для нужного столбца (например, столбец 0)

        if (index.column() == 0) {
            QFont font;
            font.setFamily("Miriam Libre");
            font.setPixelSize(24);
            option->font = font;
        }
        else if (index.column() == 1) {
            QFont font;
            font.setFamily("Inter");
            font.setPixelSize(24);
            font.setBold(true);
            option->font = font;

            // Выравнивание по правому краю
            option->displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
        }
    }
};
#endif // COLUMNFONTDELEGATE_H
