#ifndef FOAMSRCUTIL_H
#define FOAMSRCUTIL_H
#include <QStringList>
#include <QRegExp>
#include "symbol.h"
#include <QPair>
class FoamSrcUtil
{
public:
    static QRegExp R_MT_ANNO;//多行注释
    static QRegExp R_ST_ANNO;//单行注释
    static QRegExp R_TWOMORE_ENT;//多余2个连续的换行
    static QRegExp R_FIRSTLINE_ENT;//首行换行
    static QRegExp R_LASTLINE_ENT;//末行换行
    static QRegExp R_FOOT_ENT;//单值单元
    static QRegExp R_SUB_DIC;//子字典
    static QRegExp R_ENT;
    static QRegExp R_OUT_BRACE;

    static QString& clearAnno(QString &src);
    static QStringList getRegexp(const QString &src, const QString &exp);
    static QString &clearRedundantEnter(QString &src);
    static QStringList splitEntries(const QString &src);
};
QRegExp FoamSrcUtil::R_MT_ANNO = QRegExp("/\\*(.|\\r?\\n)*\\*/");
QRegExp FoamSrcUtil::R_ST_ANNO = QRegExp("//[^\\n]*\\r?\\n");
QRegExp FoamSrcUtil::R_TWOMORE_ENT = QRegExp("(\\r?\\n){2,}");
QRegExp FoamSrcUtil::R_FIRSTLINE_ENT = QRegExp("^\\r?\\n");
QRegExp FoamSrcUtil::R_LASTLINE_ENT = QRegExp("\\r?\\n$");
QRegExp FoamSrcUtil::R_OUT_BRACE = QRegExp("(?<=\\{).*(?=\\})");
QRegExp FoamSrcUtil::R_FOOT_ENT = QRegExp("[^\\{\\}\\s]+\\s+[^\\{\\}\\s]+(\\s+[^\\{\\}\\s])?;$");
QRegExp FoamSrcUtil::R_SUB_DIC = QRegExp("\\s*[\\w\"\\(\\)\\.\\[\\]\\$\\|]+\\s+\\{+");
QRegExp FoamSrcUtil::R_ENT = QRegExp("");

#endif // FOAMSRCUTIL_H
