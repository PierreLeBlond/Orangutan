#ifndef UNIFORM_H
#define UNIFORM_H

#include "asset.h"

template <class T>
class Uniform : public Asset
{
                                    Uniform(const std::string &name);
                                    Uniform(const std::string &name, const T& value);
                                   ~Uniform();

    void                           setValue(const T& value);
    const T&                       getValue() const;

    void                           setMinValue(const T& minValue);
    const T&                       getMinValue() const;

    void                           setMaxValue(const T& maxValue);
    const T&                       getMaxValue() const;


  private:
    T                              _value;
    T                              _minValue;
    T                              _maxValue;
};


#endif //UNIFORM_H
