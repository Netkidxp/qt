#include "switch.h"
#include "util.h"
namespace OpenFOAM {
bool Switch::getBoolValue() const
{
    return boolValue;
}

void Switch::setBoolValue(bool value)
{
    boolValue = value;
    if(value)
        this->setValue("on");
    else {
        this->setValue("off");
    }
}

Switch::Switch()
{
    this->boolValue = false;
}

Switch::Switch(bool value)
{
    setBoolValue(value);
}

Switch::Switch(const string &value)
{
    operator<<(value);
}

bool Switch::on()
{
    return boolValue;
}

bool Switch::yes()
{
    return boolValue;
}

Switch &Switch::operator=(bool value)
{
    setBoolValue(value);
    return *this;
}

Switch::Switch(const Switch& value)
{
    this->setBoolValue(value.getBoolValue());
}

Switch &Switch::operator<<(const string &value)
{
    if(Util::compareNocase(value,"true")||Util::compareNocase(value,"on")||Util::compareNocase(value,"yes"))
        setBoolValue(true);
    else {
        setBoolValue(false);
    }
    return *this;
}

bool Switch::operator==(const Switch &value)
{
    return this->getBoolValue() == value.getBoolValue();
}

}
