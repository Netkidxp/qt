#include "foamsrcutil.h"

QString& FoamSrcUtil::clearAnno(QString &src)
{
    src.remove(FoamSrcUtil::R_ST_ANNO);
    src.remove(FoamSrcUtil::R_MT_ANNO);
    return src;
}

QStringList FoamSrcUtil::getRegexp(const QString &src, const QString &exp)
{
    QRegExp r(exp);
    r.indexIn(src);
    return r.capturedTexts();
}

QString &FoamSrcUtil::clearRedundantEnter(QString &src)
{
    src.replace(FoamSrcUtil::R_TWOMORE_ENT,"\n");
    src.remove(FoamSrcUtil::R_FIRSTLINE_ENT);
    src.remove(FoamSrcUtil::R_LASTLINE_ENT);
    return src;
}

QStringList FoamSrcUtil::splitEntries(const QString &src)
{

}
