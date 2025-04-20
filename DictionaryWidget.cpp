#include "mainwindow.h"
#include <QLayout>
#include <QTableWidget>
#include <QHeaderView>
#include "ColumnFontDelegate.h"
#include <QPushButton>

void MainWindow::DictionaryWidget(QWidget *dictionaryWidget, const QString type_widget){
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    QSize t_size(2048,1152);
    QSize ScreenSize = screenGeometry.size();
    h_kef = static_cast<double>(ScreenSize.height()) / t_size.height();
    w_kef = static_cast<double>(ScreenSize.width()) / t_size.width();

    dictionaryWidget->setStyleSheet("background-color: white;");

    QLabel *dictionary = new QLabel(dictionaryWidget);
    dictionary->setText("СЛОВАРЬ");
    dictionary->setStyleSheet("color: #087E8B;"
                              "font-size: "+ QString::number(static_cast<int>(70*(h_kef))) +"px; font-family: Inter; font-weight: 700;");

    QFrame *logoFrame = new QFrame(dictionaryWidget);
    logoFrame->setStyleSheet("background-color: transparent;");
    logoFrame->setFixedSize(t_size.width(), 100);
    logoFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QHBoxLayout *logoLayout = new QHBoxLayout(logoFrame);
    QPushButton *ico_img = new QPushButton(logoFrame);
    ico_img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ico_img->setFixedSize(90*w_kef,90*h_kef);
    ico_img->setIcon(QIcon(":/res/img/ico.svg"));
    ico_img->setIconSize(QSize(122*w_kef,122*h_kef));
    ico_img->setStyleSheet("QPushButton {background-color: transparent; padding: 0px; border: none;}"
                           "QPushButton:hover {background-color: transparent; border: none}");

    connect(ico_img, &QPushButton::clicked, this, [=]() mutable {
        refreshData();
        stackedWidget->setCurrentWidget(mainWidget);
    });


    QPushButton *back= new QPushButton(logoFrame);
    back->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ico_img->setFixedSize(90*w_kef,90*h_kef);
    back->setIcon(QIcon(":/res/img/back.svg"));
    back->setIconSize(QSize(83*w_kef,72*h_kef));
    back->setStyleSheet("QPushButton {background-color: transparent; padding: 0px; border: none;}"
                           "QPushButton:hover {background-color: transparent; border: none}");


    connect(back, &QPushButton::clicked, this, [=]() mutable {
        refreshData();
        if(type_widget == "Tasks"){
            stackedWidget->setCurrentWidget(TasksWidget);
        }
        else if(type_widget == "Trainer"){
            stackedWidget->setCurrentWidget(TrainerWidget);
        }

    });
    if(type_widget == "Tasks" || type_widget == "Trainer"){
        logoLayout->addItem(new QSpacerItem(43*w_kef, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
        logoLayout->addWidget(back);
        back->setVisible(true);
    }
    else{
        back->setVisible(false);
    }
    logoLayout->addItem(new QSpacerItem(43*w_kef, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    logoLayout->addWidget(ico_img);
    logoLayout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QVBoxLayout *general_layout = new QVBoxLayout(dictionaryWidget);

    QFrame* header = new QFrame(dictionaryWidget);
     header->setFixedSize(t_size.width(), 61);
    header->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    header->setStyleSheet("background-color: #087E8B;");

    QHBoxLayout *headerLayout = new QHBoxLayout(header);

    QLabel* command = new QLabel(header);
    command->setStyleSheet("color: white;"
                           "font-size: "+ QString::number(static_cast<int>(24*(h_kef))) +"px;"
                                                                               "font-family: Inter;"
                                                                               "font-weight: 700;");
    command->setText("Команда");

    QLabel* naznach = new QLabel(header);
    naznach->setStyleSheet("color: white;"  // Исправлено: naznach вместо command
                           "font-size: "+ QString::number(static_cast<int>(24*(h_kef))) +"px;"
                                                                               "font-family: Inter;"
                                                                               "font-weight: 700;");
    naznach->setText("Назначение");  // Исправлено: naznach вместо command
    headerLayout->setAlignment(Qt::AlignCenter);
    headerLayout->addItem(new QSpacerItem(100*w_kef, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    headerLayout->addWidget(command);
    command->setAlignment(Qt::AlignLeft);
    headerLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    headerLayout->addWidget(naznach);
    headerLayout->addItem(new QSpacerItem(100*w_kef, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    naznach->setAlignment(Qt::AlignRight);

    QHBoxLayout *layout = new QHBoxLayout(dictionaryWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    // Создаем таблицу со словарем
    QTableWidget *table = new QTableWidget;
    table->setRowCount(40); // По количеству команд
    table->setColumnCount(2);
    table->horizontalHeader()->setVisible(false);


    // Заполняем таблицу (пример для нескольких строк)
    // A
    table->setItem(0, 0, new QTableWidgetItem("ALTER TABLE"));
    table->setItem(0, 1, new QTableWidgetItem("Изменение структуры таблицы"));
    table->setItem(1, 0, new QTableWidgetItem("AND"));
    table->setItem(1, 1, new QTableWidgetItem("Логическое И в условиях"));
    table->setItem(2, 0, new QTableWidgetItem("AVG()"));
    table->setItem(2, 1, new QTableWidgetItem("Вычисление среднего значения"));

    // B
    table->setItem(3, 0, new QTableWidgetItem("BEGIN / START TRANSACTION"));
    table->setItem(3, 1, new QTableWidgetItem("Начало транзакции"));
    table->setItem(4, 0, new QTableWidgetItem("BETWEEN"));
    table->setItem(4, 1, new QTableWidgetItem("Проверка на вхождение в диапазон"));

    // C
    table->setItem(5, 0, new QTableWidgetItem("CASE WHEN ... THEN ... ELSE ... END"));
    table->setItem(5, 1, new QTableWidgetItem("Условное выражение"));
    table->setItem(6, 0, new QTableWidgetItem("COMMIT"));
    table->setItem(6, 1, new QTableWidgetItem("Подтверждение транзакции"));
    table->setItem(7, 0, new QTableWidgetItem("COUNT()"));
    table->setItem(7, 1, new QTableWidgetItem("Подсчет количества записей"));
    table->setItem(8, 0, new QTableWidgetItem("CREATE INDEX"));
    table->setItem(8, 1, new QTableWidgetItem("Создание индекса"));
    table->setItem(9, 0, new QTableWidgetItem("CREATE TABLE"));
    table->setItem(9, 1, new QTableWidgetItem("Создание новой таблицы"));
    table->setItem(10, 0, new QTableWidgetItem("CROSS JOIN"));
    table->setItem(10, 1, new QTableWidgetItem("Декартово произведение таблиц"));

    // D
    table->setItem(11, 0, new QTableWidgetItem("DELETE"));
    table->setItem(11, 1, new QTableWidgetItem("Удаление записей из таблицы"));
    table->setItem(12, 0, new QTableWidgetItem("DENY"));
    table->setItem(12, 1, new QTableWidgetItem("Запрет прав доступа (SQL Server)"));
    table->setItem(13, 0, new QTableWidgetItem("DISTINCT"));
    table->setItem(13, 1, new QTableWidgetItem("Удаление дубликатов"));
    table->setItem(14, 0, new QTableWidgetItem("DROP INDEX"));
    table->setItem(14, 1, new QTableWidgetItem("Удаление индекса"));

    // F
    table->setItem(15, 0, new QTableWidgetItem("FETCH"));
    table->setItem(15, 1, new QTableWidgetItem("Получение строки курсора"));
    table->setItem(16, 0, new QTableWidgetItem("FULL JOIN"));
    table->setItem(16, 1, new QTableWidgetItem("Полное внешнее соединение"));

    // G
    table->setItem(17, 0, new QTableWidgetItem("GRANT"));
    table->setItem(17, 1, new QTableWidgetItem("Предоставление прав доступа"));
    table->setItem(18, 0, new QTableWidgetItem("GROUP BY"));
    table->setItem(18, 1, new QTableWidgetItem("Группировка результатов"));

    // H
    table->setItem(19, 0, new QTableWidgetItem("HAVING"));
    table->setItem(19, 1, new QTableWidgetItem("Условие для групп"));

    // I
    table->setItem(20, 0, new QTableWidgetItem("IN"));
    table->setItem(20, 1, new QTableWidgetItem("Проверка вхождения в список"));
    table->setItem(21, 0, new QTableWidgetItem("INNER JOIN"));
    table->setItem(21, 1, new QTableWidgetItem("Внутреннее соединение таблиц"));
    table->setItem(22, 0, new QTableWidgetItem("INSERT"));
    table->setItem(22, 1, new QTableWidgetItem("Добавление новых записей в таблицу"));
    table->setItem(23, 0, new QTableWidgetItem("IS NOT NULL"));
    table->setItem(23, 1, new QTableWidgetItem("Проверка на не NULL значение"));
    table->setItem(24, 0, new QTableWidgetItem("IS NULL"));
    table->setItem(24, 1, new QTableWidgetItem("Проверка на NULL значение"));

    // L
    table->setItem(25, 0, new QTableWidgetItem("LEFT JOIN"));
    table->setItem(25, 1, new QTableWidgetItem("Левое внешнее соединение"));
    table->setItem(26, 0, new QTableWidgetItem("LIKE"));
    table->setItem(26, 1, new QTableWidgetItem("Поиск по шаблону"));
    table->setItem(27, 0, new QTableWidgetItem("LIMIT"));
    table->setItem(27, 1, new QTableWidgetItem("Ограничение количества возвращаемых строк"));

    // M
    table->setItem(28, 0, new QTableWidgetItem("MAX()"));
    table->setItem(28, 1, new QTableWidgetItem("Максимальное значение"));
    table->setItem(29, 0, new QTableWidgetItem("MIN()"));
    table->setItem(29, 1, new QTableWidgetItem("Минимальное значение"));

    // N
    table->setItem(30, 0, new QTableWidgetItem("NOT"));
    table->setItem(30, 1, new QTableWidgetItem("Логическое НЕ"));

    // O
    table->setItem(31, 0, new QTableWidgetItem("OFFSET"));
    table->setItem(31, 1, new QTableWidgetItem("Пропуск указанного количества строк"));
    table->setItem(32, 0, new QTableWidgetItem("OR"));
    table->setItem(32, 1, new QTableWidgetItem("Логическое ИЛИ"));
    table->setItem(33, 0, new QTableWidgetItem("ORDER BY"));
    table->setItem(33, 1, new QTableWidgetItem("Сортировка результатов"));

    // R
    table->setItem(34, 0, new QTableWidgetItem("REVOKE"));
    table->setItem(34, 1, new QTableWidgetItem("Отзыв прав доступа"));
    table->setItem(35, 0, new QTableWidgetItem("RIGHT JOIN"));
    table->setItem(35, 1, new QTableWidgetItem("Правое внешнее соединение"));
    table->setItem(36, 0, new QTableWidgetItem("ROLLBACK"));
    table->setItem(36, 1, new QTableWidgetItem("Откат транзакции"));

    // S
    table->setItem(37, 0, new QTableWidgetItem("SAVEPOINT"));
    table->setItem(37, 1, new QTableWidgetItem("Точка сохранения в транзакции"));
    table->setItem(38, 0, new QTableWidgetItem("SELECT"));
    table->setItem(38, 1, new QTableWidgetItem("Выборка данных из таблицы"));
    table->setItem(39, 0, new QTableWidgetItem("SUM()"));
    table->setItem(39, 1, new QTableWidgetItem("Сумма значений"));

    // T
    table->setItem(40, 0, new QTableWidgetItem("TRUNCATE TABLE"));
    table->setItem(40, 1, new QTableWidgetItem("Очистка таблицы (с удалением данных)"));

    // U
    table->setItem(41, 0, new QTableWidgetItem("UPDATE"));
    table->setItem(41, 1, new QTableWidgetItem("Обновление записей в таблице"));

    // W
    table->setItem(42, 0, new QTableWidgetItem("WHERE"));
    table->setItem(42, 1, new QTableWidgetItem("Условие выборки данных"));
    // ... заполняем остальные строки ...

    // Настраиваем внешний вид
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setDefaultSectionSize(60);
    table->horizontalHeader()->setFixedHeight(60);
    table->setItemDelegate(new ColumnFontDelegate());
    table->setShowGrid(false);
    table->setStyleSheet("QTableView {"
                         "background-color: transparent; color: black; "
                         "font-size: "+ QString::number(static_cast<int>(20*(h_kef))) +"px; font-family: Inter; font-weight: 400;"
                         "padding-left: 10px;"
                         "}"
                         "QHeaderView::section {"
                         "   background-color: #B3D555;"
                         "   color: white;"
                         "   color: black;"
                        "border: none;"
                         "   border-radius:15px;"
                         "font-size: "+ QString::number(static_cast<int>(24*(h_kef))) +"px; font-family: Inter; font-weight: 600;"
                         "padding-left: 10px; "                     // Черный цвет заголовков // Граница между столбцами
                         "}"
                         "QTableView::item {"
                         "border-bottom: 1px solid #979797;"
                         // "padding: 10px;"
                         "}");
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Создаем область прокрутки
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(table);
    scrollArea->setWidgetResizable(true);

// Для QTableWidget/QTableView
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Для QScrollArea
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Добавляем в главный layout
    layout->setContentsMargins(100,0,100,0);
    layout->addWidget(scrollArea);
    general_layout->setContentsMargins(0,0,0,0);
    general_layout->setAlignment(Qt::AlignCenter);
    general_layout->addItem(new QSpacerItem(0, 75*h_kef, QSizePolicy::Expanding, QSizePolicy::Fixed));
    general_layout->addWidget(dictionary);
    general_layout->setAlignment(dictionary, Qt::AlignHCenter);
    general_layout->addItem(new QSpacerItem(0, 70*h_kef, QSizePolicy::Expanding, QSizePolicy::Fixed));
    general_layout->addWidget(header);
    general_layout->setAlignment(header, Qt::AlignHCenter);
    general_layout->addItem(new QSpacerItem(0, 40*h_kef, QSizePolicy::Expanding, QSizePolicy::Fixed));
    general_layout->addLayout(layout);

}
