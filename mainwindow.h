#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QTableView>
#include <QStackedWidget>
#include <QSqlQueryModel>
#include "sqlhighlighter.h"
#include <QLabel>
#include <QPieSlice>
#include "customchartview.h"
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    double w_kef, h_kef;
    QStackedWidget *stackedWidget = new QStackedWidget(this); // Стек виджетов
    QWidget *mainWidget;
    QWidget *TrainerWidget;
    QWidget *TasksWidget;
    QWidget *dictionaryWidget;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSplitter *splitter;
    QPlainTextEdit *sqlEditor;
    QTableView *resultsView;
    QTimer* queryTimer;
    QSqlQueryModel *resultsModel;
    SqlHighlighter *highlighter;
    QTableView *resultsTable;
    QLabel *placeholderLabel;
    QVariant nameTask;
    QVariant formula;
    QVariant description;
    QVariant done;
     QPushButton* currentTaskButton = nullptr;

    QVariant countTasks;
    QVariant countProgressTasks;

    QPieSeries *series;
    QPieSlice *slice1;
    QPieSlice *slice2;
    QLabel *goneUnder;
    QLabel *remainedUnder;
    CustomChartView* chartView;
    QLabel *progress_label;

    void refreshData();
    void updatePieChart(int remainingPercent, int donePercent);
signals:
    void dataUpdated();
private slots:
    void executeSQLQuery(const QString type_widget);
    void LoadTrainerWidget(QString type_widget = nullptr, QWidget *trainerWidget = nullptr);
    void LoadTrainerTaskWidget(QString type_widget = nullptr, QWidget *trainerWidget = nullptr);
    void executeDelayedQuery();
    void clearResultsTable();
    void DictionaryWidget(QWidget *dictionaryWidget = nullptr, const QString type_widget = "none");

private:
    void setupDatabase();
    void applyTableStyles();
    bool queriesAreEqual(const QString &query1, const QString &query2);
    QVariant getValueFromDatabase(const QString& queryString);



};
#endif // MAINWINDOW_H
