#ifndef UTIL_H
#define UTIL_H

#include<string>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;
namespace OpenFOAM {
class __declspec(dllexport) Util
{
public:
    Util();
    static bool compareNocase(const string& s1, const string& s2);
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter)
    {
        char* save = nullptr;
        char* token = strtok_s(const_cast<char*>(str.c_str()), delimiter.c_str(), &save);
        std::vector<std::string> result;
        while (token != nullptr)
        {
            result.emplace_back(token);
            token = strtok_s(nullptr, delimiter.c_str(), &save);
        }
        return result;
    }
    static double strToDouble(const string & str)
    {
        double d;
        istringstream iss(str);
        iss >> d;
        return d;
    }
};
}
#endif // UTIL_H
