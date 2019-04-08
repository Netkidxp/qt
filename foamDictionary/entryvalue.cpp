#include "entryvalue.h"
namespace OpenFOAM {

string EntryValue::getValue() const
{
    return value;
}

void EntryValue::setValue(const string &value)
{
    this->value = value;
}

EntryValue::EntryValue():value(""),uniform(false)
{

}

EntryValue::~EntryValue()
{

}

EntryValue::EntryValue(const string &value):uniform(false)
{
    this->value = value;
}

bool EntryValue::operator==(const EntryValue &entryValue)
{
    return this->value==entryValue.getValue();
}

EntryValue &EntryValue::operator<<(const string &value)
{
    this->value = value;
    return *this;
}

EntryValue::EntryValue(const string &value, bool uniform)
{
    this->value = value;
    this->uniform = uniform;
}


}
