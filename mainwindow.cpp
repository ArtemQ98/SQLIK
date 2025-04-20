#include "mainwindow.h"
#include "clickableframe.h"
#include "customchartview.h"

#include <QGuiApplication>
#include <QScreen>
#include <QLayout>
#include  <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QChartView>
#include <QPieSeries>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QSqlDatabase>
#include <QHeaderView>
#include <QMessageBox>
#include <QSqlRecord>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupDatabase();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    QSize t_size(2048,1152);
    QSize ScreenSize = screenGeometry.size();
    h_kef = static_cast<double>(ScreenSize.height()) / t_size.height();
    w_kef = static_cast<double>(ScreenSize.width()) / t_size.width();
    this->setCentralWidget(stackedWidget);
    countTasks = getValueFromDatabase("SELECT COUNT(*) FROM tasks");
    countProgressTasks = getValueFromDatabase("SELECT COUNT(*) FROM tasks WHERE done = 1");

    int countTasksInt = countTasks.toInt();
    int countProgressTasksInt = countProgressTasks.toInt();
    int countRemaindTasks = countTasksInt - countProgressTasksInt;

    mainWidget = new QWidget();
    stackedWidget->addWidget(mainWidget);
    mainWidget->setContentsMargins(0,0,0,0);
    mainWidget->setStyleSheet("background-color: #CFDCE3");

    QVBoxLayout *layout = new QVBoxLayout(mainWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);


    QFrame *header = new QFrame(mainWidget);
    header->setStyleSheet("background-color: #FFFFFF; border-bottom: 3px solid #087E8B;");
    header->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    header->setFixedSize(ScreenSize.width(), 138*h_kef);

    QHBoxLayout *header_layout = new QHBoxLayout(header);

    QPushButton *ico_img = new QPushButton(header);
    ico_img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ico_img->setFixedSize(90*w_kef,90*h_kef);
    ico_img->setIcon(QIcon(":/res/img/ico.svg"));
    ico_img->setIconSize(QSize(122*w_kef,122*h_kef));
    ico_img->setStyleSheet("QPushButton {background-color: transparent; padding: 0px; border: none;}"
                            "QPushButton:hover {background-color: transparent; border: none}");

    QLabel *SQLIK_label = new QLabel(header);
    SQLIK_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    SQLIK_label->setStyleSheet("padding-top: 15px; font-size: "+ QString::number(static_cast<int>(120*(h_kef))) +"px; font-family: Jomhuria; font-weight: 700; color: #B3D555; border: none;");
    SQLIK_label->setText("SQL’IK");
    // header_layout->setAlignment(Qt::AlignCenter);
    header_layout->addItem(new QSpacerItem(43*w_kef,0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    header_layout->addWidget(ico_img);
    header_layout->addItem(new QSpacerItem(10*w_kef,0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    header_layout->addWidget(SQLIK_label);
    header_layout->setAlignment(SQLIK_label, Qt::AlignVCenter);
    header_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));


    QHBoxLayout *main_layout = new QHBoxLayout(mainWidget);

    QPushButton *Dictionary = new QPushButton(mainWidget);
    Dictionary->setFixedSize(361*w_kef, 339*h_kef);
    Dictionary->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Dictionary->setStyleSheet("QPushButton {background-color: #F49751; border-radius: 46px;}"
                              "QPushButton:hover {background-color: #FDA868;}"
                              "QLabel {background-color: transparent;}");
    connect(Dictionary, &QPushButton::clicked, this, [=](){
        dictionaryWidget = new QWidget(this);
        MainWindow::DictionaryWidget(dictionaryWidget);
        stackedWidget->addWidget(dictionaryWidget);
        stackedWidget->setCurrentWidget(dictionaryWidget);
    });
    QVBoxLayout *Dictionary_layout = new QVBoxLayout(Dictionary);
    Dictionary_layout->setAlignment(Qt::AlignHCenter);
    QPushButton *dictionary_img = new QPushButton(Dictionary);
    dictionary_img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ico_img->setFixedSize(90*w_kef,90*h_kef);
    dictionary_img->setIcon(QIcon(":/res/img/Dictionary.svg"));
    dictionary_img->setIconSize(QSize(176*w_kef,170*h_kef));
    dictionary_img->setStyleSheet("QPushButton {background-color: transparent; padding-bottom: 20px; border: none;}"
                                    "QPushButton:hover {background-color: transparent; border: none}");
    QLabel *dictionary_label = new QLabel(Dictionary);
    dictionary_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dictionary_label->setStyleSheet("font-size: "+ QString::number(static_cast<int>(40*(h_kef))) +"px; font-family: Inter; font-weight: 700; color: white;");
    dictionary_label->setText("Словарь");
    Dictionary_layout->setAlignment(Qt::AlignCenter);
    Dictionary_layout->addWidget(dictionary_img);
    Dictionary_layout->setAlignment(dictionary_img, Qt::AlignHCenter);
    Dictionary_layout->addWidget(dictionary_label);
    Dictionary_layout->setAlignment(dictionary_label, Qt::AlignHCenter);


    ClickableFrame *Tests = new ClickableFrame(mainWidget);
    Tests->setFixedSize(772*w_kef, 222*h_kef);
    Tests->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Tests->setStyleSheet("QFrame {background-color: transparent; border: 6px solid white; border-radius: 46px;}"
                           // "QFrame:hover {background-color: tra;}"
                           "QLabel {background-color: transparent; color: white; border: none;}");
    QVBoxLayout *Tests_layout = new QVBoxLayout(Tests);

    // QPushButton *Lessons_img = new QPushButton(header);
    // Lessons_img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // // ico_img->setFixedSize(90*w_kef,90*h_kef);
    // Lessons_img->setIcon(QIcon(":/res/img/Lessons.svg"));
    // Lessons_img->setIconSize(QSize(233*w_kef,169*h_kef));
    // Lessons_img->setStyleSheet("QPushButton {background-color: transparent; padding-bottom: 20px; border: none;}"
    //                               "QPushButton:hover {background-color: transparent; border: none}");
    QLabel *Tests_label = new QLabel(Tests);
    Tests_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Tests_label->setStyleSheet("font-size: "+ QString::number(static_cast<int>(30*(h_kef))) +"px; font-family: Inter; font-weight: 700; color: white;");

    Tests_layout->setAlignment(Qt::AlignCenter);
    // Lessons_layout->addWidget(Lessons_img);
    // Lessons_layout->setAlignment(Lessons_img, Qt::AlignHCenter);
    Tests_layout->addWidget(Tests_label);
    Tests_layout->setAlignment(Tests_label, Qt::AlignHCenter);


    QPushButton *Trainer = new QPushButton(mainWidget);
    Trainer->setFixedSize(772*w_kef, 339*h_kef);
    Trainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Trainer->setStyleSheet("QPushButton {background-color: #087E8B; border-radius: 46px;}"
                           "QPushButton:hover {background-color: #0E9DAC;}"
                           "QLabel {background-color: transparent;}");


    connect(Trainer, &QPushButton::clicked, this, [=](){
        TrainerWidget = new QWidget(this);
        MainWindow::LoadTrainerTaskWidget("Trainer", TrainerWidget);
        stackedWidget->addWidget(TrainerWidget);
        stackedWidget->setCurrentWidget(TrainerWidget);
    });

    QVBoxLayout *Trainer_layout = new QVBoxLayout(Trainer);

    // QPushButton *Trainer_img = new QPushButton(Trainer);
    // Trainer_img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // // ico_img->setFixedSize(90*w_kef,90*h_kef);
    // Trainer_img->setIcon(QIcon(":/res/img/Trainer.svg"));
    // Trainer_img->setIconSize(QSize(167*w_kef,205*h_kef));
    // Trainer_img->setStyleSheet("QPushButton {background-color: transparent; padding-bottom: 20px; border: none;}"
    //                            "QPushButton:hover {background-color: transparent; border: none}");


    QLabel *Trainer_labelSQL = new QLabel(Trainer);
    Trainer_labelSQL->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Trainer_labelSQL->setStyleSheet("font-size: "+ QString::number(static_cast<int>(130*(h_kef))) +"px; font-family: Inter; font-weight: 900; color: white;");
    Trainer_labelSQL->setText("SQL");
    QLabel *Trainer_label = new QLabel(Trainer);
    Trainer_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Trainer_label->setStyleSheet("font-size: "+ QString::number(static_cast<int>(40*(h_kef))) +"px; font-family: Inter; font-weight: 900; color: white;");
    Trainer_label->setText("Тренажер");

    Trainer_layout->setAlignment(Qt::AlignCenter);
    Trainer_layout->addWidget(Trainer_labelSQL);
    Trainer_layout->setAlignment(Trainer_labelSQL, Qt::AlignHCenter);
    Trainer_layout->addItem(new QSpacerItem(0, 40*h_kef, QSizePolicy::Expanding, QSizePolicy::Fixed));
    Trainer_layout->addWidget(Trainer_label);
    Trainer_layout->setAlignment(Trainer_label, Qt::AlignHCenter);


    QPushButton *Tasks = new QPushButton(mainWidget);
    Tasks->setFixedSize(361*w_kef, 339*h_kef);
    Tasks->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Tasks->setStyleSheet("QPushButton {background-color: #B3D555; border-radius: 46px;}"
                         "QPushButton:hover {background-color: #BCE057;}"
                         "QLabel {background-color: transparent;}");
    QVBoxLayout *Tasks_layout = new QVBoxLayout(Tasks);

    QPushButton *Tasks_img = new QPushButton(Tasks);
    Tasks_img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ico_img->setFixedSize(90*w_kef,90*h_kef);
    Tasks_img->setIcon(QIcon(":/res/img/Tests.svg"));
    Tasks_img->setIconSize(QSize(182*w_kef,182*h_kef));
    Tasks_img->setStyleSheet("QPushButton {background-color: transparent; padding-bottom: 20px; border: none;}"
                               "QPushButton:hover {background-color: transparent; border: none}");
    QLabel *Tasks_label = new QLabel(Tasks);
    Tasks_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Tasks_label->setStyleSheet("font-size: "+ QString::number(static_cast<int>(40*(h_kef))) +"px; font-family: Inter; font-weight: 700; color: white;");
    Tasks_label->setText("Задания");

    Tasks_layout->setAlignment(Qt::AlignCenter);
    Tasks_layout->addWidget(Tasks_img);
    Tasks_layout->setAlignment(Tasks_img, Qt::AlignHCenter);
    Tasks_layout->addWidget(Tasks_label);
    Tasks_layout->setAlignment(Tasks_label, Qt::AlignHCenter);
    connect(Tasks, &QPushButton::clicked, this, [=](){
        TasksWidget = new QWidget(this);
        MainWindow::LoadTrainerWidget("Trainer", TasksWidget);
        stackedWidget->addWidget(TasksWidget);
        stackedWidget->setCurrentWidget(TasksWidget);
    });

    QVBoxLayout *main_VLeft_layout = new QVBoxLayout(mainWidget);
    QHBoxLayout *main_HUp_layout = new QHBoxLayout(mainWidget);
    QHBoxLayout *main_HDown_layout = new QHBoxLayout(mainWidget);
    main_VLeft_layout->setContentsMargins(118*w_kef, 84*h_kef, 0, 0);

    main_HUp_layout->addWidget(Trainer);
    main_HUp_layout->addItem(new QSpacerItem(53*w_kef, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    main_HUp_layout->addWidget(Tasks);

    main_HDown_layout->setAlignment(Qt::AlignCenter);

    main_HDown_layout->addWidget(Dictionary);
    main_HDown_layout->addItem(new QSpacerItem(53*w_kef, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    main_HDown_layout->addWidget(Tests);
    main_HDown_layout->setAlignment(Tests, Qt::AlignTop);

    main_VLeft_layout->addLayout(main_HUp_layout);
    main_VLeft_layout->addItem(new QSpacerItem(0, 53*h_kef, QSizePolicy::Expanding, QSizePolicy::Fixed));
    main_VLeft_layout->addLayout(main_HDown_layout);

    // main_left_layout->setContentsMargins(133*w_kef,107*h_kef,0,0);
    // main_left_layout->addLayout(main_VLeft_layout);
    // main_left_layout->setSpacing(50*h_kef);

    QVBoxLayout *main_right_layout = new QVBoxLayout(mainWidget);


    QFrame *progress = new QFrame(mainWidget);
    QVBoxLayout *progressLayout = new QVBoxLayout(progress);
    // Создание круговой диаграммы
    progress->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    progress->setFixedSize(510*w_kef, 650*h_kef);
    progress->setStyleSheet("background-color: white; border-radius: 46px;");

    QLocale locale(QLocale::German);

    int countProgressTasksProcent = (countProgressTasksInt*100)/countTasksInt;
    int countRemaindTasksProcent = 100 - countProgressTasksProcent;
    series = new QPieSeries();
    slice1 = series->append(QString::number(countRemaindTasksProcent), countRemaindTasksProcent);
    slice1->setBrush(QColor("#087E8B"));

    slice2 = series->append(QString::number(countProgressTasksProcent), countProgressTasksProcent);
    slice2->setBrush(QColor("#B3D555"));


    series->setLabelsVisible(true);
    series->setHoleSize(0.5);


    // series->setLabelsPosition(QPieSlice::);
    QFont labelFont("Inter 18pt", 13, QFont::Bold);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible(true);
        slice->setLabelFont(labelFont);
    }
    // Создание диаграммы и добавление серии
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->legend()->setVisible(false);
    chart->setBackgroundVisible(false);
    chartView = new CustomChartView(chart);
    chartView->setStyleSheet("border: none;");
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(450*h_kef, 450*h_kef);
    chartView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    chartView->setContentsMargins(0, 0, 0, 0);

    QFrame *GoneFrame = new QFrame(progress);
    GoneFrame->setFixedSize(40*w_kef, 40*h_kef);
    GoneFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    GoneFrame->setStyleSheet("border: none; border-radius: 5px; background-color: #087E8B");

    QFrame *RemainedFrame = new QFrame(progress);
    RemainedFrame->setFixedSize(40*w_kef, 40*h_kef);
    RemainedFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    RemainedFrame->setStyleSheet("border: none; border-radius: 5px; background-color: #B3D555");

    goneUnder = new QLabel(progress);
    goneUnder->setStyleSheet("border: none; font-size: "+ QString::number(static_cast<int>(30*(h_kef))) +"px; font-family: Inter; font-weight: regular; color: #555555");
    goneUnder->setText("- "+ QString::number(countProgressTasks.toInt()) +" заданий сделано");
    remainedUnder = new QLabel(progress);
    remainedUnder->setStyleSheet("border: none; font-size: "+ QString::number(static_cast<int>(30*(h_kef))) +"px; font-family: Inter; font-weight: regular; color: #555555");
    remainedUnder->setText("- "+ QString::number(countRemaindTasks) +" задания осталось сделать");

    QGridLayout *progressGridLayout = new QGridLayout(progress);
    progressGridLayout->setSpacing(18);

    progressGridLayout->addWidget(RemainedFrame, 0, 0);
    progressGridLayout->addWidget(goneUnder, 0, 1);
    progressGridLayout->addWidget(GoneFrame, 1, 0);
    progressGridLayout->addWidget(remainedUnder, 1, 1);

    progressLayout->setSpacing(0);
    progressLayout->setContentsMargins(0, 0, 0, 0);
    progressLayout->addItem(new QSpacerItem(0,25*h_kef, QSizePolicy::Expanding, QSizePolicy::Fixed));
    progressLayout->addItem(new QSpacerItem(0,11*h_kef, QSizePolicy::Expanding, QSizePolicy::Fixed));
    progressLayout->addWidget(chartView);
    progressLayout->setAlignment(chartView, Qt::AlignHCenter);
    progressLayout->addLayout(progressGridLayout);
    progressLayout->setAlignment(progressGridLayout, Qt::AlignHCenter);
    progressLayout->addItem(new QSpacerItem(0,45*h_kef, QSizePolicy::Expanding, QSizePolicy::Fixed));

    progressLayout->addStretch(0);

    progress_label = new QLabel(progress);
    if(countProgressTasksProcent <= 30){
        progress_label->setText("Новичок");
        Tests_label->setText("Ты только начинаешь — каждая строчка кода \nкажется загадкой");
    }
    else if(countProgressTasksProcent > 30 && countProgressTasksProcent <=70){
        progress_label->setText("Эксперт");
        Tests_label->setText("SQL для тебя — не просто инструмент, \nа продолжение мысли");
    }
    else{
        progress_label->setText("Мастер");
        Tests_label->setText("Ты не просто пишешь запросы — \nты чувствуешь их");
    }
    progress_label->setStyleSheet("font-size: "+ QString::number(static_cast<int>(60*(h_kef))) +"px; font-family: Inter; font-weight: 700; color: #087E8B;");
    main_right_layout->setContentsMargins(0,84,0,0);
    main_right_layout->setAlignment(Qt::AlignCenter);
    main_right_layout->addWidget(progress_label);
    main_right_layout->setAlignment(progress_label, Qt::AlignHCenter);
    main_right_layout->addWidget(progress);
    main_right_layout->setAlignment(progress, Qt::AlignHCenter);
    // main_right_layout->setContentsMargins(560, 107,0,0);
    main_right_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    main_layout->addLayout(main_VLeft_layout);
    main_layout->addItem(new QSpacerItem(117*w_kef,0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    main_layout->addLayout(main_right_layout);
    main_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    layout->addWidget(header);
    layout->addLayout(main_layout);
    layout->addStretch(0);
    mainWidget->setLayout(layout);



    stackedWidget->setCurrentIndex(0);
}

void MainWindow::setupDatabase()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QString connectionString = QString("DRIVER={SQL Server};SERVER=ARTTEAM_DESKTOP\\SQLEXPRESS;DATABASE=SQLIK");
    db.setDatabaseName(connectionString);

    if (!db.open()) {
        qWarning() << "Не удалось открыть базу данных:" << db.lastError().text();
        return;
    }

    // Создание тестовой таблицы
    QSqlQuery query;
    // query.exec("CREATE TABLE employees (id INTEGER PRIMARY KEY, name TEXT, department TEXT, salary REAL)");
    // query.exec("INSERT INTO employees VALUES (1, 'Иванов', 'IT', 75000)");
    // query.exec("INSERT INTO employees VALUES (2, 'Петрова', 'HR', 65000)");
    // query.exec("INSERT INTO employees VALUES (3, 'Сидоров', 'IT', 80000)");
}

void MainWindow::applyTableStyles()
{
    resultsTable->setFixedSize(750, 805);
    resultsTable->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    resultsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    resultsTable->verticalHeader()->setDefaultSectionSize(60);
    QString tableStyle = QString("QTableView {"
                                 "background-color: transparent; color: black; "
                                 "font-size: "+ QString::number(static_cast<int>(20*(h_kef))) +"px; font-family: Inter; font-weight: 400;"
                                "padding-left: 10px;"
                                "}"
                                "QHeaderView::section {"
                                "   background-color: #B3D555;"
                                "   color: white;"
                                "   border-bottom: 1px solid #B3D555;"
                                "   color: black;"
                                "   border-radius:15px;"
                                "font-size: "+ QString::number(static_cast<int>(20*(h_kef))) +"px; font-family: Inter; font-weight: 600;"
                                                                                     "padding-left: 10px; "                     // Черный цвет заголовков // Граница между столбцами
                                "}"
                                 "QTableView::item {"
                                 "border-bottom: 1px solid #B3D555;"
                                 // "padding: 10px;"
                                 "}");
    resultsTable->setStyleSheet(tableStyle);
    resultsTable->setShowGrid(false);


    resultsTable->horizontalHeader()->setStretchLastSection(true);
    resultsTable->verticalHeader()->setVisible(false);
    resultsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::executeSQLQuery(const QString type_widget)
{
    qDebug() << "executeSQLQuery";
    QString queryText = sqlEditor->toPlainText().trimmed();
    if (queryText.isEmpty()) {
        resultsModel->clear();
        return;
    }

    if (!queriesAreEqual(queryText, formula.toString()) && type_widget == "Tasks" ) {
        resultsModel->clear();
        QMessageBox msgBox;

        // Настраиваем стиль MessageBox
        msgBox.setStyleSheet(
            "QMessageBox {"
            "   background-color: #F5F5F5;"
            "   border: 2px solid #E74C3C;"
            "   border-radius: 10px;"
            "   padding: 10px;"
            "}"
            "QLabel {"
            "   color: #333333;"
            "   font-family: 'Inter';"
            "   font-size: 16px;"
            "   font-weight: 500;"
            "}"
            "QPushButton {"
            "   background-color: #E74C3C;"
            "   color: white;"
            "   border: none;"
            "   border-radius: 5px;"
            "   padding: 8px 16px;"
            "   font-family: 'Inter';"
            "   font-size: 14px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #C0392B;"
            "}"
            );

        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("<b>Неверный ответ</b>");

        // Добавляем кнопку OK
        msgBox.setStandardButtons(QMessageBox::Ok);

        // Показываем MessageBox
        msgBox.exec();
        return;
    }

    QSqlQuery query;
    if (!query.exec(queryText)) {
        if(type_widget != "Tasks")
        {
            resultsModel->clear();
            QMessageBox msgBox;

            // Настраиваем стиль MessageBox
            msgBox.setStyleSheet(
                "QMessageBox {"
                "   background-color: #F5F5F5;"
                "   border: 2px solid #E74C3C;"
                "   border-radius: 10px;"
                "   padding: 10px;"
                "}"
                "QLabel {"
                "   color: #333333;"
                "   font-family: 'Inter';"
                "   font-size: 16px;"
                "   font-weight: 500;"
                "}"
                "QPushButton {"
                "   background-color: #E74C3C;"
                "   color: white;"
                "   border: none;"
                "   border-radius: 5px;"
                "   padding: 8px 16px;"
                "   font-family: 'Inter';"
                "   font-size: 14px;"
                "}"
                "QPushButton:hover {"
                "   background-color: #C0392B;"
                "}"
                );

            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("<b>Неверный запрос</b>");

            // Добавляем кнопку OK
            msgBox.setStandardButtons(QMessageBox::Ok);

            // Показываем MessageBox
            msgBox.exec();
        }
        return;
    }

    resultsModel->setQuery(query);


    if (!query.exec("UPDATE tasks SET done = 1 WHERE name = '"+ nameTask.toString()+"'")) {

        qWarning() << "Ошибка SQL:" << query.lastError().text();
        return;
    }
    emit dataUpdated();
    QMessageBox msgBox;

    // Настраиваем стиль MessageBox
    msgBox.setStyleSheet(
        "QMessageBox {"
        "   background-color: #F5F5F5;"
        "   border: 2px solid #A9C757;"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "}"
        "QLabel {"
        "   color: #333333;"
        "   font-family: 'Inter';"
        "   font-size: 16px;"
        "   font-weight: 500;"
        "}"
        "QPushButton {"
        "   background-color: #A9C757;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   padding: 8px 16px;"
        "   font-family: 'Inter';"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #C0392B;"
        "}"
        );

    msgBox.setWindowTitle("Молодец!");
    msgBox.setText("<b>Всё верно</b>");

    // Добавляем кнопку OK
    msgBox.setStandardButtons(QMessageBox::Ok);

    // Показываем MessageBox
    msgBox.exec();

}

void MainWindow::executeDelayedQuery()
{
    QString queryText = sqlEditor->toPlainText().trimmed();

    // проверка на пустоту
    if (queryText.isEmpty()) {
        clearResultsTable();
        return;
    }

    try {
        QSqlQuery query;
        if (!query.exec(queryText)) {
            qDebug() << "SQL Error:" << query.lastError().text();
            clearResultsTable(); // Очищаем при ошибке
            return;
        }

        if (!resultsModel) {
            resultsModel = new QSqlQueryModel(this);
            resultsView->setModel(resultsModel);
        }

        resultsModel->setQuery(query);

    } catch (...) {
        clearResultsTable();
    }
}

void MainWindow::clearResultsTable()
{
    if (resultsModel) {
        resultsModel->clear();

        resultsModel->removeRows(0, resultsModel->rowCount());
        resultsModel->removeColumns(0, resultsModel->columnCount());
    }

}

bool MainWindow::queriesAreEqual(const QString &query1, const QString &query2) {
    QSqlQuery q1(query1);
    QSqlQuery q2(query2);

    if (q1.lastError().isValid() || q2.lastError().isValid()) {
        qDebug() << "Ошибка в запросе:" << q1.lastError() << q2.lastError();
        return false;
    }

    // Проверка количества строк
    if (q1.size() != q2.size()) {
        return false;
    }

    // Проверка, что набор столбцов совпадает
    QSqlRecord rec1 = q1.record();
    QSqlRecord rec2 = q2.record();
    if (rec1.count() != rec2.count()) {
        return false;
    }

    // Проверяем, что все столбцы из q1 есть в q2
    for (int i = 0; i < rec1.count(); ++i) {
        QString columnName = rec1.fieldName(i);
        if (!rec2.contains(columnName)) {
            return false;
        }
    }

    // Построчное сравнение данных, учитывая имена столбцов
    while (q1.next() && q2.next()) {
        for (int i = 0; i < rec1.count(); ++i) {
            QString columnName = rec1.fieldName(i);
            if (q1.value(columnName) != q2.value(columnName)) {
                return false;
            }
        }
    }

    return true;
}

void MainWindow::refreshData() {
    // Получаем данные
    countTasks = getValueFromDatabase("SELECT COUNT(*) FROM tasks");
    countProgressTasks = getValueFromDatabase("SELECT COUNT(*) FROM tasks WHERE done = 1");

    int countTasksInt = countTasks.toInt();
    int countProgressTasksInt = countProgressTasks.toInt();

    // Рассчитываем значения
    int countRemaindTasks = countTasksInt - countProgressTasksInt;
    int countProgressTasksProcent = countTasksInt > 0 ? (countProgressTasksInt*100)/countTasksInt : 0;
    int countRemaindTasksProcent = 100 - countProgressTasksProcent;

    // Обновляем текстовые поля
    goneUnder->setText("- "+ QString::number(countProgressTasksInt) +" заданий сделано");
    remainedUnder->setText("- "+ QString::number(countRemaindTasks) +" задания осталось сделать");

    if(countProgressTasksProcent <= 30){
        progress_label->setText("Новичок");
    }
    else if(countProgressTasksProcent > 30 && countProgressTasksProcent <=70){
        progress_label->setText("Эксперт");
    }
    else{
        progress_label->setText("Мастер");
    }

    // Обновляем диаграмму
    updatePieChart(countRemaindTasksProcent, countProgressTasksProcent);
}

void MainWindow::updatePieChart(int remainingPercent, int donePercent) {
    // Очищаем старые данные
    series->clear();

    // Добавляем новые срезы
    slice1 = series->append(QString::number(remainingPercent) + "%", remainingPercent);
    slice1->setBrush(QColor("#087E8B"));

    slice2 = series->append(QString::number(donePercent) + "%", donePercent);
    slice2->setBrush(QColor("#B3D555"));

    // Настройка отображения
    for (auto slice : series->slices()) {
        slice->setLabelVisible(true);
        slice->setLabelArmLengthFactor(0.1);
    }

    // Принудительное обновление графика
    if (chartView) {
        chartView->update();
    }
}
MainWindow::~MainWindow() {}
