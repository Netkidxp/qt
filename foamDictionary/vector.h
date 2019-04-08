#ifndef VECTOR_H
#define VECTOR_H
#include<entryvalue.h>
#include<vector>
using namespace std;
namespace OpenFOAM {
class __declspec(dllexport) Vector : public EntryValue
{
private:
    double x;
    double y;
    double z;
public:
    Vector();
    Vector(double x,double y,double z);
    Vector(const string& value);
    Vector(const Vector& value);
    virtual void setVectorValue(double x,double y,double z);
    double getX() const;
    void setX(double value);
    double getY() const;
    void setY(double value);
    double getZ() const;
    void setZ(double value);
    Vector& operator<<(const string& value);
    bool operator==(const Vector& value);

};
}
#endif // VECTOR_H
