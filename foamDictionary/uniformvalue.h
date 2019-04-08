#ifndef UNIFORMVALUE_H
#define UNIFORMVALUE_H
#include "entryvalue.h"
namespace OpenFOAM {
template<class T>
class UniformValue : public EntryValue
{
private:
    T t;

public:
    UniformValue();
    UniformValue(T t);
    T value();

    // EntryValue interface
public:
    string getValue() const;
    EntryValue &operator <<(const string &value);
    bool operator ==(const EntryValue &entryValue);
};
}



#endif // UNIFORMVALUE_H
