#include "foamsrcutil.h"

QString& FoamSrcUtil::clearAnno(QString &src)
{
    src.remove(FoamSrcUtil::R_ST_ANNO);
    src.remove(FoamSrcUtil::R_MT_ANNO);
    return src;
}

QString &FoamSrcUtil::clearEnter(QString &src)
{
    src.replace(FoamSrcUtil::R_TWOMORE_ENTER,"\n");
    src.remove(FoamSrcUtil::R_FIRSTLINE_ENTER);
    src.remove(FoamSrcUtil::R_LASTLINE_ENTER);
    src.replace(FoamSrcUtil::R_ENTER," ");
    src.replace(FoamSrcUtil::R_MUTI_SPACE," ");

    return src;
}

Dictionary FoamSrcUtil::splitEntries(const QString &src)
{
    Dictionary dic;
    QString s(src);
    clearAnno(s);
    clearEnter(s);
    QRegExp r_name(FoamSrcUtil::R_ENTRY_NAME);
    QRegExp r_value(FoamSrcUtil::R_ENTRY_VALUE);
    QRegExp r_dictionary(FoamSrcUtil::R_ENTRY_DICTIONARY);
    int pos = 0;
    while(s!=" ")
    {
        pos = r_name.indexIn(s,pos);
        if(pos == -1)
        {
            break;
        }
        else
        {
            QString name = r_name.capturedTexts()[0];
            pos +=r_name.matchedLength();
            int vpos = r_value.indexIn(s,pos);
            if(vpos == -1)//非value格式，要么非法要么就是子字典
            {
                int len = 0;
                vpos = findSubDictionary(s,pos,len);
                if(vpos == -1)
                    break;
                else
                {
                    pos = vpos + len;
                    QString subdic = s.mid(vpos+1,len-2);
                    dic.setChild(name,splitEntries(subdic));
                }
            }
            else //value格式
            {
                pos +=r_value.matchedLength();
                QString value = r_value.capturedTexts()[0];
                dic.setChild(name,value);
            }
        }
    }
    return dic;
}

QString &FoamSrcUtil::clearOutBrace(QString &src)
{
    src.remove(QRegExp("^\\s\\{"));
    src.remove(QRegExp("\\}$"));
    return src;
}

int FoamSrcUtil::findSubDictionary(QString &src, int start, int &len)
{
    int l = -1;
    int r = -1;
    int level = 0;
    for(int i=start;i<src.length();i++)
    {
        if(src[i] == LBRACE)
        {
            if(level == 0)
                l = i;
            level++;
        }
        else if(src[i] == RBRACE)
        {
            level--;
            if(level == 0)
                r = i;
        }
        if(level == 0 && r > l)
            break;
    }
    if(level == 0 && r > l)
    {
        len = r - l;
        return l;
    }
    else
    {
        return -1;
    }
}

