#ifndef SCALAR_H
#define SCALAR_H
#include"entryvalue.h"
namespace OpenFOAM {
class __declspec(dllexport) Scalar : public EntryValue
{
private:
    double scalarValue;
public:
    Scalar();
    Scalar(double value);
    Scalar(const string& value);
    Scalar(const Scalar& value);
    double getScalarValue() const;
    void setScalarValue(double value);
    Scalar& operator<<(const string& value);
    bool operator==(const Scalar& value);
};
}
#endif // SCALAR_H
