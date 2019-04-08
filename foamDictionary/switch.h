#ifndef SWITCH_H
#define SWITCH_H
#include"entryvalue.h"
namespace OpenFOAM {
class __declspec(dllexport) Switch : public EntryValue
{
private:
    bool boolValue;
public:
    Switch();
    Switch(bool value);
    Switch(const string& value);
    Switch(const Switch& value);
    bool on();
    bool yes();
    static Switch On;
    static Switch Off;
    Switch &operator=(bool value);
    bool getBoolValue() const;
    void setBoolValue(bool value);
    Switch& operator<<(const string& value);
    virtual bool operator==(const Switch& value);
};
Switch Switch::On = Switch(true);
Switch Switch::Off = Switch(false);
}
#endif // SWITCH_H
