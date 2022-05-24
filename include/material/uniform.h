#ifndef ORANGUTAN_MATERIAL_UNIFORM_H
#define ORANGUTAN_MATERIAL_UNIFORM_H

#include "object/asset.h"

namespace orangutan {

template <class T>
class Uniform : public Asset {
 public:
  Uniform(const std::string& name);
  Uniform(const std::string& name, const T& value);
  Uniform(const std::string& name, const T& value, const T& minValue,
          const T& maxValue);

  void setValue(const T& value);
  const T& getValue() const;

  void setMinValue(const T& minValue);
  const T& getMinValue() const;

  void setMaxValue(const T& maxValue);
  const T& getMaxValue() const;

 private:
  T _value;
  T _minValue;
  T _maxValue;
};

}  // namespace orangutan

#endif  // ORANGUTAN_MATERIAL_UNIFORM_H
