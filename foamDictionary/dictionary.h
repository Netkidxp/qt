#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QTextStream>
#include <QPair>

class Dictionary;
std::ostream& operator<<(std::ostream &os,const Dictionary &dic);
QTextStream& operator<<(QTextStream &os,Dictionary &dic);
class Dictionary : public QHash<QString,Dictionary>
{
private:
    QString _data;
    uint _level;
    const QString TAB = "\t";
    const QString SPACE = " ";
    const QString ENTER = "\r\n";
    const QString LBRACE = "{";
    const QString RBRACE = "}";
    const QString END = ";";
    const QString SEP = "\\";
    QString prefix;

public:
    static Dictionary null;
    Dictionary();
    Dictionary(const QString &data);
    Dictionary(const Dictionary &dic);
    Dictionary(const QStringList &code);
    QString str() const;
    QString name() const;
    uint level() const;
    void setLevel(uint level);
    Dictionary& setChild(const QString &name, const Dictionary &child);
    Dictionary& setChild(const QString &name, const QString &data);
    Dictionary& setChild(const QPair<QString,Dictionary> &child);
    Dictionary& setChild(const QPair<QString,QString> &child);
    Dictionary& addChild(const QString &name);
    Dictionary& operator=(const Dictionary &dic);
    Dictionary& operator=(const QString &data);
    Dictionary& operator<<(const QPair<QString,Dictionary> &child);
    Dictionary& operator<<(const QPair<QString,QString> &child);
    bool equals(const Dictionary& dic);
    Dictionary& lookup(const QString &url);
    QString data() const;
    void setData(const QString &data);
    bool root() const;
    bool foot() const;
    void write(QTextStream &os);

};
Dictionary Dictionary::null = Dictionary("null");

#endif // DICTIONARY_H