#ifndef ENTRYVALUE_H
#define ENTRYVALUE_H

#include<string>
using namespace std;
namespace OpenFOAM {

class __declspec(dllexport) EntryValue
{
protected:
    string value;
    bool uniform;
public:
    EntryValue();
    virtual ~EntryValue();
    EntryValue(const string &value);
    EntryValue(const string &value, bool uniform);
    virtual string getValue() const;
    virtual void setValue(const string &value);
    virtual EntryValue& operator<<(const string &value);
    virtual bool operator==(const EntryValue& entryValue);
};

}

#endif // ENTRYVALUE_H
