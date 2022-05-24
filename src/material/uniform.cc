#include "material/uniform.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"

namespace orangutan {

template <class T>
Uniform<T>::Uniform(const std::string& name) : Asset(name) {}

template <class T>
Uniform<T>::Uniform(const std::string& name, const T& value)
    : Asset(name), _value(value), _minValue(value), _maxValue(value) {}

template <class T>
Uniform<T>::Uniform(const std::string& name, const T& value, const T& minValue,
                    const T& maxValue)
    : Asset(name), _value(value), _minValue(minValue), _maxValue(maxValue) {}

template <class T>
const T& Uniform<T>::getValue() const {
  return _value;
}

template <class T>
void Uniform<T>::setValue(const T& value) {
  _value = value;
}

template <class T>
const T& Uniform<T>::getMinValue() const {
  return _minValue;
}

template <class T>
void Uniform<T>::setMinValue(const T& minValue) {
  _minValue = minValue;
}

template <class T>
const T& Uniform<T>::getMaxValue() const {
  return _maxValue;
}

template <class T>
void Uniform<T>::setMaxValue(const T& maxValue) {
  _maxValue = maxValue;
}

template class Uniform<float>;
template class Uniform<int>;
template class Uniform<unsigned int>;
template class Uniform<bool>;
template class Uniform<glm::vec3>;
template class Uniform<glm::vec4>;
template class Uniform<glm::mat3>;
template class Uniform<glm::mat4>;

}  // namespace orangutan
