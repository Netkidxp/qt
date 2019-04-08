#ifndef ENTRY_H
#define ENTRY_H
#include<string>
#include<entryvalue.h>
using namespace std;
namespace OpenFOAM {
template<class T>
class __declspec(dllexport) Entry
{
private:
    string key;
    T value;
public:
    Entry();
    Entry(const string& key);
};
}


#endif // ENTRY_H
