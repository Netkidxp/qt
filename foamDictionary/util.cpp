#include "util.h"
namespace OpenFOAM {
Util::Util()
{

}

bool Util::compareNocase(const string &s1, const string &s2)
{
    string::const_iterator p = s1.begin();
    string::const_iterator p2 = s2.begin();
    while(p!=s1.end() && p2!=s2.end())
      {
         if(toupper(*p)!=toupper(*p2))
             return false;
         ++p;
         ++p2;
      }
     return s2.size() == s1.size();
}
}
