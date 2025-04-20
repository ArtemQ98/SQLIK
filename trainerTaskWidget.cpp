#include "mainwindow.h"
#include "sqlhighlighter.h"

#include <QGuiApplication>
#include <QScreen>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QSqlQuery>

void MainWindow::LoadTrainerTaskWidget(QString type_widget, QWidget *trainerWidget){
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    QSize t_size(2048,1152);
    QSize ScreenSize = screenGeometry.size();
    h_kef = static_cast<double>(ScreenSize.height()) / t_size.height();
    w_kef = static_cast<double>(ScreenSize.width()) / t_size.width();

    trainerWidget->setStyleSheet("background-color: #DFEFFF;");
    QVBoxLayout *layout = new QVBoxLayout(trainerWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);


    QFrame *header = new QFrame(trainerWidget);
    header->setStyleSheet("background-color: #C8D7E6;");
    header->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    header->setFixedSize(ScreenSize.width(), 138*h_kef);


    QHBoxLayout *header_layout = new QHBoxLayout(header);

    QPushButton *ico_img = new QPushButton(header);
    ico_img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ico_img->setFixedSize(90*w_kef,90*h_kef);
    ico_img->setIcon(QIcon(":/res/img/ico.svg"));
    ico_img->setIconSize(QSize(90*w_kef,90*h_kef));
    ico_img->setStyleSheet("QPushButton {background-color: transparent; padding: 0px; border: none;}"
                           "QPushButton:hover {background-color: transparent; border: none}");

    connect(ico_img, &QPushButton::clicked, this, [=]() mutable {
        refreshData();
        stackedWidget->setCurrentWidget(mainWidget);
    });

    header_layout->addItem(new QSpacerItem(43*w_kef, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    header_layout->addWidget(ico_img);
    header_layout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));

    QPushButton *dictionari_img = new QPushButton(header);
    dictionari_img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ico_img->setFixedSize(90*w_kef,90*h_kef);
    dictionari_img->setIcon(QIcon(":/res/img/Dictionary2.svg"));
    dictionari_img->setIconSize(QSize(80*w_kef,80*h_kef));
    dictionari_img->setStyleSheet("QPushButton {background-color: transparent; padding: 0px; border: none;}"
                                  "QPushButton:hover {background-color: transparent; border: none}");

    connect(ico_img, &QPushButton::clicked, this, [=]() mutable {
        stackedWidget->setCurrentWidget(mainWidget);
    });
    // Добавляем финальный спейсер
    header_layout->setAlignment(Qt::AlignCenter);
    header_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    header_layout->addWidget(dictionari_img);
    header_layout->setAlignment(dictionari_img, Qt::AlignRight);
    header_layout->addItem(new QSpacerItem(43*w_kef, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));


    // Показываем первую задачу по умолчанию

    QHBoxLayout *main_layout = new QHBoxLayout(trainerWidget);
    QVBoxLayout *main_left_layout = new QVBoxLayout(trainerWidget);
    main_left_layout->setContentsMargins(95,68,0,0);


    sqlEditor = new QPlainTextEdit(trainerWidget);
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(sqlEditor);
    shadowEffect->setBlurRadius(105);
    shadowEffect->setColor(QColor(0, 0, 0, 40));
    shadowEffect->setOffset(8, 5);
    sqlEditor->setGraphicsEffect(shadowEffect);

    queryTimer = new QTimer(this);
    queryTimer->setSingleShot(true);
    queryTimer->setInterval(0); // Задержка 0 мс

    // connect(sqlEditor, &QPlainTextEdit::textChanged, this, [this]() {

    //     if (sqlEditor->toPlainText().trimmed().isEmpty()) {
    //         clearResultsTable();
    //         return;
    //     }

    //     queryTimer->start();
    // });

    // connect(queryTimer, &QTimer::timeout, this, &MainWindow::executeDelayedQuery);

    new SqlHighlighter(sqlEditor->document()); // Подключаем подсветку синтаксиса
    sqlEditor->setFixedSize(854*w_kef, 571*h_kef);
    sqlEditor->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sqlEditor->setStyleSheet("QPlainTextEdit {background-color: white; color: black; border: none; border-radius: 42px;"
                             "font-size: "+ QString::number(static_cast<int>(30*(h_kef))) +"px; font-family: Inter; font-weight: 400; padding: 15px;}"
                                                                                 "QPlainTextEdit::focus{border: 1px solid #B3D555;}");


    sqlEditor->setPlaceholderText("Введите запрос");


    main_left_layout->addWidget(sqlEditor);
    main_left_layout->addStretch(0);


    QHBoxLayout *main_right_layout = new QHBoxLayout(trainerWidget);
    main_right_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QFrame *resultsFrame = new QFrame(trainerWidget);
    resultsFrame->setFixedSize(819 * w_kef, 805 * h_kef);
    resultsFrame->setStyleSheet(
        "QFrame {"
        "   background-color: white;"
        "   border: none;"
        "   border-radius: 42px;"
        "}"
        );

    QVBoxLayout *resultsLayout = new QVBoxLayout(resultsFrame);
    // resultsLayout->setContentsMargins(15, 15, 15, 15);
    resultsLayout->setAlignment(Qt::AlignCenter);
    resultsTable = new QTableView(resultsFrame);
    resultsLayout->setAlignment(resultsFrame, Qt::AlignHCenter);
    resultsModel = new QSqlQueryModel(this);
    resultsTable->setModel(resultsModel);

    applyTableStyles();

    resultsLayout->addWidget(resultsTable);
    resultsLayout->addStretch(0);
    resultsFrame->setLayout(resultsLayout);

    QPushButton *executeButton = new QPushButton(trainerWidget);
    executeButton->setFixedSize(140*w_kef, 140*h_kef);
    executeButton->setStyleSheet("QPushButton {background-color: #A9C757;}");
    executeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ico_img->setFixedSize(90*w_kef,90*h_kef);
    executeButton->setIcon(QIcon(":/res/img/execute.svg"));
    executeButton->setIconSize(QSize(96*w_kef,96*h_kef));
    connect(executeButton, &QPushButton::clicked,
            this, &MainWindow::executeSQLQuery);

    main_layout->addLayout(main_left_layout);
    // main_layout->addItem(new QSpacerItem(140*w_kef,0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    main_layout->addWidget(executeButton);
    main_layout->addWidget(resultsFrame);
    main_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    // main_layout->addLayout(main_right_layout);
    layout->addWidget(header);
    layout->addLayout(main_layout);
    layout->addStretch(0);
    trainerWidget->setLayout(layout);


}
