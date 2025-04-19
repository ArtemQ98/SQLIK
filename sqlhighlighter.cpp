#include "sqlhighlighter.h"

    SqlHighlighter::SqlHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    // Настройка форматов
    keywordFormat.setForeground(Qt::magenta);
    keywordFormat.setFontCapitalization(QFont::AllUppercase);
    keywordFormat.setFontWeight(QFont::Bold);

    functionFormat.setForeground(Qt::red);
    functionFormat.setFontCapitalization(QFont::AllUppercase);
    functionFormat.setFontWeight(QFont::Bold);

    stringFormat.setForeground(Qt::blue);
    stringFormat.setFontCapitalization(QFont::AllUppercase);
    numberFormat.setForeground(Qt::darkGreen);
    numberFormat.setFontCapitalization(QFont::AllUppercase);

    commentFormat.setForeground(Qt::gray);
    commentFormat.setFontItalic(true);

    // Ключевые слова
    QStringList keywordPatterns;
    keywordPatterns << "\\bSELECT\\b" << "\\bFROM\\b" << "\\bWHERE\\b"
                    << "\\bINSERT\\b" << "\\bINTO\\b" << "\\bVALUES\\b"
                    << "\\bUPDATE\\b" << "\\bSET\\b" << "\\bDELETE\\b"
                    << "\\bJOIN\\b" << "\\bLEFT\\b" << "\\bRIGHT\\b"
                    << "\\bINNER\\b" << "\\bOUTER\\b" << "\\bON\\b"
                    << "\\bGROUP BY\\b" << "\\bORDER BY\\b" << "\\bHAVING\\b"
                    << "\\bDISTINCT\\b" << "\\bAS\\b" << "\\bAND\\b"
                    << "\\bOR\\b" << "\\bNOT\\b" << "\\bNULL\\b"
                    << "\\bCREATE\\b" << "\\bTABLE\\b" << "\\bDROP\\b"
                    << "\\bALTER\\b" << "\\bINDEX\\b" << "\\bVIEW\\b"
                    << "\\bPRIMARY KEY\\b" << "\\bFOREIGN KEY\\b"
                    << "\\bREFERENCES\\b" << "\\bUNIQUE\\b";

    foreach (const QString &pattern, keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern, QRegularExpression::CaseInsensitiveOption);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Функции
    QStringList functionPatterns;
    functionPatterns << "\\bCOUNT\\b" << "\\bSUM\\b" << "\\bAVG\\b"
                     << "\\bMIN\\b" << "\\bMAX\\b" << "\\bUPPER\\b"
                     << "\\bLOWER\\b" << "\\bSUBSTRING\\b" << "\\bTRIM\\b"
                     << "\\bLENGTH\\b" << "\\bCOALESCE\\b" << "\\bNULLIF\\b";

    foreach (const QString &pattern, functionPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern, QRegularExpression::CaseInsensitiveOption);
        rule.format = functionFormat;
        highlightingRules.append(rule);
    }

    // Строки в одинарных и двойных кавычках
    HighlightingRule stringRule;
    stringRule.pattern = QRegularExpression("(\"[^\"]*\")|('[^']*')");
    stringRule.format = stringFormat;
    highlightingRules.append(stringRule);

    // Числа
    HighlightingRule numberRule;
    numberRule.pattern = QRegularExpression("\\b\\d+\\b");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);

    // Однострочные комментарии (--)
    HighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("--[^\n]*");
    commentRule.format = commentFormat;
    highlightingRules.append(commentRule);

    // Многострочные комментарии (/* ... */)
    commentRule.pattern = QRegularExpression("/\\*.*?\\*/");
    commentRule.format = commentFormat;
    highlightingRules.append(commentRule);
}

void SqlHighlighter::highlightBlock(const QString &text)
{
    // Применяем правила подсветки
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // Подсветка многострочных комментариев
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf("/*");

    while (startIndex >= 0) {
        QRegularExpressionMatch match = QRegularExpression("\\*/").match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + match.capturedLength();
        }
        setFormat(startIndex, commentLength, commentFormat);
        startIndex = text.indexOf("/*", startIndex + commentLength);
    }
}
bool SqlHighlighter::eventFilter(QObject *obj, QEvent *event)
{
    if (!m_autoUppercase) return false;

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        // Преобразуем при нажатии пробела, Enter или Tab
        if (keyEvent->key() == Qt::Key_Space ||
            keyEvent->key() == Qt::Key_Enter ||
            keyEvent->key() == Qt::Key_Return ||
            keyEvent->key() == Qt::Key_Tab) {

            QTextDocument *doc = qobject_cast<QTextDocument*>(obj);
            if (doc) {
                QTextCursor cursor(doc);
                cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
                formatLastWordToUpper(cursor);
            }
        }
    }
    return QSyntaxHighlighter::eventFilter(obj, event);
}

void SqlHighlighter::formatLastWordToUpper(QTextCursor &cursor)
{
    // Выделяем слово перед курсором
    cursor.select(QTextCursor::WordUnderCursor);
    QString word = cursor.selectedText();

    // Проверяем, является ли слово ключевым
    for (const HighlightingRule &rule : highlightingRules) {
        if (rule.format == keywordFormat) {
            QRegularExpressionMatch match = rule.pattern.match(word);
            if (match.hasMatch() && word != word.toUpper()) {
                cursor.insertText(word.toUpper());
                break;
            }
        }
    }
}
