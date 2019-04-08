#include "dictionary.h"

uint Dictionary::level() const
{
    return _level;
}

Dictionary &Dictionary::setChild(const QString &name, const Dictionary &child)
{
    Dictionary newDic = child;
    newDic.setLevel(_level + 1);
    insert(name,newDic);
    _data = "";
    return operator[](name);
}

Dictionary& Dictionary::setChild(const QString &name, const QString &data)
{
    Dictionary dic = data;
    setChild(name, dic);
    _data = "";
    return operator[](name);
}

Dictionary &Dictionary::setChild(const QPair<QString, Dictionary> &child)
{
    setChild(child.first,child.second);
    _data = "";
    return operator[](child.first);
}

Dictionary& Dictionary::setChild(const QPair<QString, QString> &child)
{
    setChild(child.first,child.second);
    _data = "";
    return operator[](child.first);
}

Dictionary &Dictionary::addChild(const QString &name)
{
    Dictionary d;
    return setChild(name,d);
}

Dictionary &Dictionary::operator=(const Dictionary &dic)
{
    if(this == &dic)
        return *this;
    clear();
    for(Dictionary::const_iterator it=dic.constBegin();it!=dic.constEnd();it++)
    {
        insert(it.key(),it.value());
    }
    this->setLevel(dic.level());
    this->setData(dic.data());
    return *this;
}

Dictionary &Dictionary::operator=(const QString &data)
{
    this->setLevel(0);
    this->setData(data);
    return *this;
}

Dictionary &Dictionary::operator<<(const QPair<QString, Dictionary> &child)
{
    setChild(child.first,child.second);
    return *this;
}

Dictionary &Dictionary::operator<<(const QPair<QString, QString> &child)
{
    setChild(child.first,child.second);
    return *this;
}

bool Dictionary::equals(const Dictionary &dic)
{
    if(this == &dic)
        return true;
    if(_data != dic.data())
        return false;
    bool res = static_cast<QHash<QString,Dictionary>>(dic).operator==(*this);
    return res;
}

Dictionary &Dictionary::lookup(const QString &url)
{
    int fir = url.indexOf(SEP);
    if(fir == -1)
    {
        if(contains(url))
            return operator[](url);
        else
        {
            return null;
        }
    }
    else
    {
        QString name1 = url.left(fir);
        QString name2 = url.right(url.length()- fir - SEP.length());
        if(contains(name1))
        {

            return operator[](name1).lookup(name2);
        }
        else
        {
            return null;
        }
    }
}

void Dictionary::setLevel(uint level)
{
    _level = level;
    prefix = "";
    for(uint i=0;i<level;i++)
        prefix += TAB;
    for(Dictionary::const_iterator it=constBegin();it!=constEnd();it++)
    {
        QString key = it.key();
        Dictionary dic = it.value();
        dic.setLevel(_level +1);
        insert(key,dic);
    }
}

QString Dictionary::data() const
{
    return _data;
}

bool Dictionary::root() const
{
    return _level == 0;
}

bool Dictionary::foot() const
{
    return _data != "";
}

void Dictionary::write(QTextStream &os)
{
    os << *this;
}


void Dictionary::setData(const QString &data)
{
    _data = data;
}

Dictionary::Dictionary():_data(""),_level(0),prefix("")
{

}

Dictionary::Dictionary(const QString &data):_data(data),_level(0),prefix("")
{

}

Dictionary::Dictionary(const Dictionary &dic)
{
    operator=(dic);
}

Dictionary::Dictionary(const QStringList &code)
{
}

QString Dictionary::str() const
{
    QString s = "";
    if(foot())
        s = TAB + _data + END + ENTER;
    else
    {
        if(root())
        {
            for(Dictionary::const_iterator it=constBegin();it!=constEnd();it++)
            {
                QString key = it.key();
                const Dictionary dic = it.value();
                s += prefix + TAB + key + dic.str();
            }
        }
        else
        {
            s = ENTER + prefix + LBRACE + ENTER;
            for(Dictionary::const_iterator it=constBegin();it!=constEnd();it++)
            {
                QString key = it.key();
                const Dictionary dic = it.value();
                s += prefix + TAB + key + dic.str();
            }
            s +=prefix + RBRACE + ENTER;
        }
    }
    return s;
}

std::ostream &operator<<(std::ostream &os, const Dictionary &dic)
{
    os << dic.str().toStdString();
    return os;
}

QTextStream &operator<<(QTextStream &os, Dictionary &dic)
{
    os << dic.str();
    return os;
}
