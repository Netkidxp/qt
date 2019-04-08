#include <QCoreApplication>
#include "dictionary.h"
#include <iostream>
#include <string>
#include <QRegExp>
#include <foamsrcutil.h>
#include <QFile>
#include <QDebug>
#include <QTextStream>
void test_foamlib()
{
    Dictionary d;
    std::cout << d << std::endl;
    Dictionary child1("child1");
    d.setChild("k1",child1);
    d.setChild("k2","child2");
    Dictionary child3;
    child3.setChild("k3.k1","child3.child1");
    child3.setChild("k3.k2","child3.child2");
    Dictionary child3_child3;
    child3_child3.setChild("k3.k3.k1","c3.c3.c1");
    child3.setChild("k3.k3",child3_child3);
    d.setChild("k3",child3);
    d["sd"].setData("sd");
    d.setChild("qq","qq");
    //d.setChild("sd","newsd");
    d.setChild("haha1",Dictionary()).setChild("h1.h2","h1.h2.value");
    d.addChild("f1").setData("f1_value");
    d.addChild("g1").addChild("g1.g2").addChild("g1.g2.g3").setData("g1.g2.g3_value");
    d["g1"].addChild("g1.g2_").setData("g1.g2_value");
    d.remove("qq");
    std::cout << d <<std::endl <<std::endl;
    std::cout << "d.lookup(\"k3\\k3.k1\"):" << d.lookup("k3\\k3.k1") <<std::endl;
    d.lookup("k3\\k3.k1").setData("cedan");
    std::cout << "d.lookup(\"k3\\k3.k1\"):" << d.lookup("k3\\k3.k1") <<std::endl;
    d["g1"]["g1.g2"].remove("g1.g2.g3");
    std::cout << d <<std::endl <<std::endl;
}

QString regexp_choose(const QString str, const QString reg)
{
    QRegExp r(reg);
    int pos = r.indexIn(str);
    if(pos == -1)
        return "";
    else {
        QStringList txts = r.capturedTexts();
        QString res;
        for(QStringList::const_iterator it = txts.constBegin();it!=txts.constEnd();it++)
        {
            if(res == "")
                res = *it;
            else {
                res += "-" + *it;
            }
        }
        return res;
    }
}
void test_regexp()
{
    QFile f("F:\\blueCFD-Core-2017\\OpenFOAM-5.x\\tutorials_bak\\incompressible\\porousSimpleFoam\\angledDuctImplicit\\system\\fvSchemes");
    f.open(QFile::ReadOnly|QFile::Text);
    QString str(f.readAll());
    FoamSrcUtil::clearAnno(str);
    FoamSrcUtil::clearRedundantEnter(str);
    f.close();
    QFile f1("f:\\text.txt");
    f1.open(QFile::NewOnly|QFile::Text);
    QTextStream ts(&f1);
    ts << str;
    f1.close();
}
void test_regexp2()
{
    QString s("dff   ;");
    QRegExp r = FoamSrcUtil::R_FOOT_ENT;
    int i = r.indexIn(s);
    std::cout << i << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    test_regexp2();
    return a.exec();
}
