#include "monitor.h"

QStringList Monitor::getErrs() const
{
    return errs;
}

QStringList Monitor::getInfs() const
{
    return infs;
}

Monitor::Monitor()
{

}

Monitor::~Monitor()
{

}

void Monitor::error(const QString &err)
{
    errs.append(err);
}

void Monitor::log(const QString &inf)
{
    infs.append(inf);
}

QString Monitor::lastError()
{
    if(errs.isEmpty())
        return "";
    else
        return errs.last();
}

QString Monitor::lastInfs()
{
    if(infs.isEmpty())
        return "";
    else
        return infs.last();
}
