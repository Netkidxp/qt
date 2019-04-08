#include "scalar.h"
#include <sstream>
namespace OpenFOAM {
double Scalar::getScalarValue() const
{
    return scalarValue;
}

void Scalar::setScalarValue(double value)
{
    scalarValue = value;
    this->setValue(to_string(value));
}

Scalar::Scalar()
{
    setScalarValue(0.0);
}

Scalar::Scalar(double value)
{
    setScalarValue(value);
}

Scalar::Scalar(const string &value)
{
    operator<<(value);
}

Scalar::Scalar(const Scalar &value)
{
    setScalarValue(value.getScalarValue());
}

Scalar &Scalar::operator<<(const string &value)
{
    double d;
    istringstream iss(value);
    iss >> d;
    setScalarValue(d);
    return *this;
}

bool Scalar::operator==(const Scalar &value)
{
    return getScalarValue() == value.getScalarValue();
}

}
