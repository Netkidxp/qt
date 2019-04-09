#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>

class Monitor
{
private:
    QStringList errs;
    QStringList infs;
public:
    Monitor();
    virtual ~Monitor();
    virtual void error(const QString &err);
    virtual void log(const QString &inf);
    virtual void progress(float pro) = 0;
    QString lastError();
    QString lastInfs();
    QStringList getErrs() const;
    QStringList getInfs() const;
};

#endif // MONITOR_H
