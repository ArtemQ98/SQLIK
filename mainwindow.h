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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    double w_kef, h_kef;
    QStackedWidget *stackedWidget = new QStackedWidget(this); // Стек виджетов
    QWidget *mainWidget;
    QWidget *TrainerWidget;
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

private slots:
    void executeSQLQuery();
    void LoadTrainerWidget(QString type_widget = nullptr, QWidget *trainerWidget = nullptr);
    void executeDelayedQuery();
    void clearResultsTable();
private:
    void setupDatabase();
    void applyTableStyles();
    bool queriesAreEqual(const QString &query1, const QString &query2);
    QVariant getValueFromDatabase(const QString& queryString);


};
#endif // MAINWINDOW_H
