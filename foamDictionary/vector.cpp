#include "vector.h"
#include <sstream>
#include <iostream>
#include <util.h>
namespace OpenFOAM {

void Vector::setVectorValue(double x,double y,double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    ostringstream ostr;
    ostr << "( " << x << " " << y << " " << z << " )" << endl;
    setValue(ostr.str());
}

double Vector::getX() const
{
    return x;
}

void Vector::setX(double value)
{
    x = value;
    ostringstream ostr;
    ostr << "( " << x << " " << y << " " << z << " )" << endl;
    setValue(ostr.str());
}

double Vector::getY() const
{
    return y;
}

void Vector::setY(double value)
{
    y = value;
    ostringstream ostr;
    ostr << "( " << x << " " << y << " " << z << " )" << endl;
    setValue(ostr.str());
}

double Vector::getZ() const
{
    return z;
}

void Vector::setZ(double value)
{
    z = value;
    ostringstream ostr;
    ostr << "( " << x << " " << y << " " << z << " )" << endl;
    setValue(ostr.str());
}

Vector::Vector()
{
    setVectorValue(0.0,0.0,0.0);
}

Vector::Vector(double x, double y, double z)
{
    setVectorValue(x,y,z);
}

Vector::Vector(const string &value)
{
    operator<<(value);
}

Vector::Vector(const OpenFOAM::Vector &value)
{
    setVectorValue(value.getX(),value.getY(),value.getZ());
}

Vector& Vector::operator<<(const string &value)
{
    string tstr = value;
    for (string::iterator iter = tstr.begin();iter!=tstr.end();) {
        if(*iter == '(' || *iter == ')')
            iter = tstr.erase(iter);
        else
            iter++;
    }
    double x = 0,y = 0,z = 0;
    vector<string> allstr = Util::split(tstr," ");
    for (vector<string>::iterator iter = allstr.begin();iter!=allstr.end();) {
        if((*iter).length() == 0)
            iter = allstr.erase(iter);
        else
            iter++;
    }
    if(allstr.size()>0)
        x = Util::strToDouble(allstr[0]);
    if(allstr.size()>1)
        y = Util::strToDouble(allstr[1]);
    if(allstr.size()>2)
        z = Util::strToDouble(allstr[2]);
    setVectorValue(x,y,z);
    return *this;
}

bool Vector::operator==(const Vector &value)
{
    return (getX() == value.getX()) && (getY() == value.getY()) && (getZ() == value.getZ());
}

}
