#include "uniformvalue.h"
template<class T>
OpenFOAM::UniformValue<T>::UniformValue()
{

}

template<class T>
OpenFOAM::UniformValue<T>::UniformValue(T t)
{

}

template<class T>
T OpenFOAM::UniformValue<T>::value()
{
    return t;
}

template<class T>
string OpenFOAM::UniformValue<T>::getValue() const
{
    return "uniform " + t.getValue();
}

template<class T>
OpenFOAM::EntryValue &OpenFOAM::UniformValue<T>::operator <<(const string &value)
{

}
