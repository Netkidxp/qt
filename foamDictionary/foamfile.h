#ifndef FOAMFILE_H
#define FOAMFILE_H

#include "dictionary.h"
#include <QFile>
#include "monitor.h"
#include "foamsrcutil.h"
class FoamFile;
QTextStream &operator<<(QTextStream &os,FoamFile &file);
class FoamFile : public Dictionary
{
private:
    FoamFile();
    const QString anno ="\
/*--------------------------------*- C++ -*---------------------------------*\\ \n\
| =========                |                                                 |  \n\
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |  \n\
|  \\    /   O peration     | Version:  -                                     |  \n\
|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |  \n\
|    \\/     M anipulation  |                                                 |  \n\
\\*--------------------------------------------------------------------------*/  \n\
/*                 Foam Dictionary Reader/Writer Ver 1.0                    *\\ \n\
|          By netkidxp: http://www.netkidxp.cn  netkidxp@126.com             |  \n\
\\*---------------------------------------------------------------------- ---*/  \n\n";
    const QString split = "\n// ************************************************************************* //\n";
public:
    FoamFile(QTextStream &is, Monitor *moniter = nullptr);
    FoamFile(Dictionary &dic);
    FoamFile(QFile &file, Monitor *moniter = nullptr);
    FoamFile(const QString &fileName, Monitor *moniter = nullptr);
    // Dictionary interface
public:
    void write(QTextStream &os);
    bool write(const QString &fileName, Monitor *moniter=nullptr);
};

#endif // FOAMFILE_H
