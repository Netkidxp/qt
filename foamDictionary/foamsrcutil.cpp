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
    src.replace(FoamSrcUtil::R_ENTER,SPACE);
    src.replace(FoamSrcUtil::R_MUTI_SPACE,SPACE);

    return src;
}

Dictionary FoamSrcUtil::decode(const QString &src, Monitor *monitor)
{
    Dictionary dic;
    QString s(src);
    clearAnno(s);
    clearEnter(s);
    QRegExp r_name(FoamSrcUtil::R_ENTRY_NAME);
    QRegExp r_value(FoamSrcUtil::R_ENTRY_VALUE);
    QRegExp r_dictionary(FoamSrcUtil::R_ENTRY_DICTIONARY);
    while(!empty(s))
    {
        int pos = r_name.indexIn(s);
        if(pos == -1)
        {
            if(monitor)
            {
                QString err = QString("FoamSrcUtil::decode:\n{type:\t%1\nsrc:\t%2\n}")
                        .arg("decode entry name")
                        .arg(s);
                monitor->error(err);
            }
            dic = null;
            break;
        }
        else
        {
            int len = 0;
            QString name = r_name.capturedTexts()[1];
            s = s.right(s.length()-pos-r_name.matchedLength());
            if(name.startsWith(SHARP))
            {
                pos = findFunctionValue(s, len);
                if(pos == -1)
                {
                    if(monitor)
                    {
                        QString err = QString("FoamSrcUtil::decode:\n{type:\t%1\nentry:\t%2\nsrc:\t%3\n}")
                                .arg("decode function value")
                                .arg(name)
                                .arg(s);
                        monitor->error(err);
                    }
                    dic =  null;
                    break;
                }
                else
                {
                    QString value = s.mid(pos,len);
                    value.remove(END);
                    dic.setChild(name,value);
                    s = s.right(s.length() - pos - len);
                }
            }
            else
            {
                pos = findValue(s, len);
                if(pos == -1)//非value格式，要么非法要么就是子字典
                {
                    pos = findSubDictionary(s,len);
                    if(pos == -1)
                    {
                        if(monitor)
                        {
                            QString err = QString("FoamSrcUtil::decode:\n{type:\t%1\nentry:\t%2\nsrc:\t%3\n}")
                                    .arg("decode entry value")
                                    .arg(name)
                                    .arg(s);
                            monitor->error(err);
                        }
                        dic = null;
                        break;
                    }
                    else
                    {

                        QString subdicstr = s.mid(pos+1,len-2);
                        Dictionary subdic = decode(subdicstr, monitor);
                        if(subdic == null)
                        {
                            dic = null;
                            break;
                        }
                        else
                        {
                            dic.setChild(name,subdic);
                            s = s.right(s.length() - pos - len - 1);
                        }

                    }
                }
                else //value格式
                {
                    QString value = s.mid(pos,len);
                    value.remove(END);
                    dic.setChild(name,value);
                    s = s.right(s.length() - pos - len);
                }
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

int FoamSrcUtil::findSubDictionary(QString &src, int &len)
{
    int l = -1;
    int r = -1;
    int level = 0;
    for(int i=0;i<src.length();i++)
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

int FoamSrcUtil::findValue(QString &src, int &len)
{
    int l = -1;
    int r = -1;
    for(int i=0;i<src.length();i++)
    {
        if(src[i] == LBRACE || src[i] == RBRACE)
            return -1;
        else if(src[i] == END)
        {
            r = i;
            break;
        }
        else if(src[i] == SPACE)
        {
            continue;
        }
        else
        {
            if(l == -1)
                l = i;
        }
    }
    len = r - l + 1;
    if(len >= 1)
        return l;
    else
    {
        return -1;
    }
}

int FoamSrcUtil::findFunctionValue(QString &src, int &len)
{
    int l = -1;
    int r = -1;
    for(int i=0;i<src.length();i++)
    {
        if(src[i] == QUOTE)
        {
            if(l == -1)
            {
                l = i;
            }
            else
            {
                r = i;
                break;
            }
        }
    }
    len = r - l + 1;
    if(len >= 2)
        return l;
    else
    {
        return -1;
    }
}

bool FoamSrcUtil::empty(const QString &src)
{
    if(src.length() ==0)
        return true;
    else
    {
        QRegExp r("^[\\s]*$");
        return r.indexIn(src) != -1;
    }
}

