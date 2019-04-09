#ifndef FOAMSRCUTIL_H
#define FOAMSRCUTIL_H
#include <QStringList>
#include <QRegExp>
#include "symbol.h"
#include <QPair>
#include <dictionary.h>
#include <monitor.h>
class FoamSrcUtil
{
public:
    static QRegExp R_MT_ANNO;//多行注释
    static QRegExp R_ST_ANNO;//单行注释
    static QRegExp R_ENTER;//换行
    static QRegExp R_TWOMORE_ENTER;//多余2个连续的换行
    static QRegExp R_MUTI_SPACE;//多于2个连续的空格或者TAB
    static QRegExp R_FIRSTLINE_ENTER;//首行换行
    static QRegExp R_LASTLINE_ENTER;//末行换行
    static QRegExp R_FOOT_ENTRY;//单值单元
    static QRegExp R_SUB_DICTIONARY;//子字典
    static QRegExp R_ENTRY_NAME;//key name
    static QRegExp R_ENTRY_VALUE;//value key
    static QRegExp R_ENTRY_DICTIONARY;//dictionary key
    static QRegExp R_OUT_BRACE;

    static QString& clearAnno(QString &src);
    static QString& clearEnter(QString &src);
    static Dictionary decode(const QString &src, Monitor *monitor = nullptr);
    static QString& clearOutBrace(QString &src);
    static int findSubDictionary(QString &src, int &len);
    static int findValue(QString &src, int &len);
    static int findFunctionValue(QString &src, int &len);
    static bool empty(const QString &src);
};
QRegExp FoamSrcUtil::R_MT_ANNO = QRegExp("/\\*(.|\\r?\\n)*\\*/");
QRegExp FoamSrcUtil::R_ST_ANNO = QRegExp("//[^\\n]*\\r?\\n");
QRegExp FoamSrcUtil::R_ENTER = QRegExp("\\r?\\n");
QRegExp FoamSrcUtil::R_TWOMORE_ENTER = QRegExp("(\\r?\\n){2,}");
QRegExp FoamSrcUtil::R_MUTI_SPACE = QRegExp("\\s{2,}");
QRegExp FoamSrcUtil::R_FIRSTLINE_ENTER = QRegExp("^\\r?\\n");
QRegExp FoamSrcUtil::R_LASTLINE_ENTER = QRegExp("\\r?\\n$");
QRegExp FoamSrcUtil::R_OUT_BRACE = QRegExp("(?<=\\{).*(?=\\})");
QRegExp FoamSrcUtil::R_FOOT_ENTRY = QRegExp("[^\\{\\}\\s]+\\s+[^\\{\\}\\s]+(\\s+[^\\{\\}\\s])?;$");
QRegExp FoamSrcUtil::R_SUB_DICTIONARY = QRegExp("\\s*[\\w\"\\(\\)\\.\\[\\]\\$\\|]+\\s+\\{+");
QRegExp FoamSrcUtil::R_ENTRY_NAME = QRegExp("\\s?([^\\s\\{\\}]+)\\s");
QRegExp FoamSrcUtil::R_ENTRY_VALUE = QRegExp("^\\s[^\\{\\}\\s]+[^;]*;");//^\s[^\{\}\s;]+[^;]*;
QRegExp FoamSrcUtil::R_ENTRY_DICTIONARY = QRegExp("(?<=\\{).*(?=\\})");


#endif // FOAMSRCUTIL_H
