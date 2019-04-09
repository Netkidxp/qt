#include "dictionary.h"
#include <QRegExp>
#include <symbol.h>

uint Dictionary::level() const
{
    return _level;
}

Dictionary &Dictionary::setChild(const QString &name, const Dictionary &child)
{
    Dictionary newDic = child;
    newDic.setLevel(_level + 1);
    int i = indexOf(name);
    if(i==-1)
    {
        append(QPair<QString,Dictionary>(name,newDic));
    }
    else
    {
        replace(i,QPair<QString,Dictionary>(name,newDic));
    }
    _data = "";
    return item(name);
}

Dictionary& Dictionary::setChild(const QString &name, const QString &data)
{
    Dictionary dic = data;
    setChild(name, dic);
    _data = "";
    return item(name);
}

Dictionary &Dictionary::setChild(const QPair<QString, Dictionary> &child)
{
    setChild(child.first,child.second);
    _data = "";
    return item(child.first);
}

Dictionary& Dictionary::setChild(const QPair<QString, QString> &child)
{
    setChild(child.first,child.second);
    _data = "";
    return item(child.first);
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
        append(*it);
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
    bool res = static_cast<QList<QPair<QString,Dictionary>>>(dic).operator==(*this);
    return res;
}

Dictionary &Dictionary::lookup(const QString &url)
{
    int fir = url.indexOf(SEP);
    if(fir == -1)
    {
        if(contains(url))
            return item(url);
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

            return item(name1).item(name2);
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
    for(Dictionary::Iterator it=begin();it!=end();it++)
    {
        Dictionary &dic = it->second;
        dic.setLevel(_level +1);
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

Dictionary &Dictionary::item(const QString &name)
{
    Dictionary &dic = null;
    for(Dictionary::Iterator it = begin();it!=end();it++)
    {
        if(it->first == name)
        {
            dic = it->second;
            break;
        }
    }
    return dic;
}

int Dictionary::indexOf(const QString &name)
{
    int res = -1;
    for(Dictionary::const_iterator it = constBegin();it!=constEnd();it++)
    {
        QPair<QString,Dictionary> item = *it;
        if(it->first == name)
        {
            res = QList<QPair<QString,Dictionary>>::indexOf(item);
            break;
        }
    }
    return res;
}

bool Dictionary::contains(const QString &name)
{
    return indexOf(name) != -1;
}

Dictionary &Dictionary::operator[](const QString &name)
{
    return item(name);
}

void Dictionary::remove(const QString name)
{
    int i = indexOf(name);
    if(i==-1)
        return;
    else {
        removeAt(i);
    }
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

Dictionary::~Dictionary()
{

}

Dictionary::Dictionary(const QString &data):_data(data),_level(0),prefix("")
{

}

Dictionary::Dictionary(const Dictionary &dic)
{
    operator=(dic);
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
                QString key = it->first;
                const Dictionary dic = it->second;
                s += prefix + TAB + key + dic.str();
            }
        }
        else
        {
            s = ENTER + prefix + LBRACE + ENTER;
            for(Dictionary::const_iterator it=constBegin();it!=constEnd();it++)
            {
                QString key = it->first;
                const Dictionary dic = it->second;
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

