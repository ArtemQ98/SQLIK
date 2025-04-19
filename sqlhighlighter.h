#ifndef SQLHIGHLIGHTER_H
#define SQLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class SqlHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    SqlHighlighter(QTextDocument *parent = nullptr);
    void setAutoUppercase(bool enabled) { m_autoUppercase = enabled; }
protected:
    void highlightBlock(const QString &text) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    bool m_autoUppercase = true;
    QTextCharFormat keywordFormat;
    QTextCharFormat stringFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat functionFormat;
    void formatLastWordToUpper(QTextCursor &cursor);
};

#endif // SQLHIGHLIGHTER_H
