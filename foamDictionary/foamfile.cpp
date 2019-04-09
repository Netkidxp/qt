#include "foamfile.h"

FoamFile::FoamFile()
{

}
FoamFile::FoamFile(QTextStream &is, Monitor *moniter)
{
    QString code = is.readAll();
    Dictionary d = FoamSrcUtil::decode(code,moniter);
    Dictionary::operator=(d);
}

FoamFile::FoamFile(Dictionary &dic)
{
    Dictionary::operator=(dic);
}

FoamFile::FoamFile(QFile &file, Monitor *moniter)
{
    if(!file.exists())
    {
        if(moniter)
        {
            moniter->error("init foamfile error:file not exist");
            Dictionary::operator=(null);
        }
        Dictionary::operator=(null);
    }
    else
    {
        if(file.open(QFile::ReadOnly|QFile::Text))
        {
            QTextStream is(&file);
            QString code = is.readAll();
            Dictionary d = FoamSrcUtil::decode(code,moniter);
            Dictionary::operator=(d);
        }
        else
        {
            if(moniter)
            {
                moniter->error("init foamfile error:can not open file");
                Dictionary::operator=(null);
            }
        }
    }
}

FoamFile::FoamFile(const QString &fileName, Monitor *moniter)
{
    QFile file(fileName);
    if(!file.exists())
    {
        if(moniter)
        {
            moniter->error("init foamfile error:file not exist");
            Dictionary::operator=(null);
        }
        Dictionary::operator=(null);
    }
    else
    {
        if(file.open(QFile::ReadOnly|QFile::Text))
        {
            QTextStream is(&file);
            QString code = is.readAll();
            Dictionary d = FoamSrcUtil::decode(code,moniter);
            Dictionary::operator=(d);
        }
        else
        {
            if(moniter)
            {
                moniter->error("init foamfile error:can not open file");
                Dictionary::operator=(null);
            }
        }
    }
}

void FoamFile::write(QTextStream &os)
{
    os << anno;
    os << static_cast<Dictionary &>(*this);
    os << split;
}

bool FoamFile::write(const QString &fileName, Monitor *moniter)
{
    bool res = false;
    QFile f(fileName);
    if(f.exists())
    {
        res = f.open(QFile::WriteOnly|QFile::Text);
    }
    else
    {
        res = f.open(QFile::NewOnly|QFile::Text);
    }
    if(!res)
    {
        if(moniter)
            moniter->error(QString("open foamfile error: filename is \"%1\"").arg(fileName));
        return false;
    }
    else
    {
        QTextStream os(&f);
        os << *this;
        f.close();
    }
    return true;
}

QTextStream &operator<<(QTextStream &os, FoamFile &file)
{
    file.write(os);
    return os;
}
