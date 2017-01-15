#include "object/uniform.h"

Uniform::Uniform(const std::string &name) : Asset(name)
{}

template <class T>
Uniform<T>::Uniform(const std::string &name, const T& value) : Asset(name), 
    _value(value), _minValue(value), _maxValue(value)
{}

template <class T>
const T& Uniform<T>::getValue() const
{
    return _value;
}

template <class T>
void Uniform<T>::setValue(const T &value)
{
    _value = value;
}

template <class T>
const T& Uniform<T>::getMinValue() const
{
    return _minValue;
}

template <class T>
void Uniform<T>::setMinValue(const T &minValue)
{
    _minValue = minValue;
}

template <class T>
const T& Uniform<T>::getMaxValue() const
{
    return _maxValue;
}

template <class T>
void Uniform<T>::setMaxValue(const T &maxValue)
{
    _maxValue = maxValue;
}
