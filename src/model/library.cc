#include "model/library.h"

#include "camera/camera.h"
#include "core/shader/shaderwrapper.h"
#include "core/texture/cubetexture.h"
#include "core/texture/ddtexture.h"
#include "object/light.h"
#include "object/mesh.h"
#include "object/renderableobject.h"
#include "scene/scene.h"
#include "shader/shaderstrategy.h"

template <class T>
const std::vector<std::shared_ptr<T>>& Library<T>::get_items() const {
  return items_;
}

template <class T>
const std::vector<std::shared_ptr<T>> Library<T>::GetItemsByName(
    const std::string& name) const {
  std::vector<std::shared_ptr<T>> items;
  for (auto item : items_) {
    if (name == item->getName()) {
      items.push_back(item);
    }
  }
  return items;
}

template <class T>
void Library<T>::GetItemById(unsigned int index,
                             std::shared_ptr<T>& item) const {
  if (index >= items_.size()) {
    std::cerr << "No item available at index " << index << std::endl;
    return;
  }

  item = items_[index];
}

template <class T>
void Library<T>::AddItem(std::shared_ptr<T> item) {
  items_.push_back(std::move(item));
}

template <class T>
std::shared_ptr<T> Library<T>::get_current_item() const {
  return current_item_;
}

template <class T>
void Library<T>::SetCurrentItemById(unsigned int index) {
  if (index >= items_.size()) {
    std::cerr << "No item available at index " << index << std::endl;
    return;
  }
  current_item_ = items_[index];
}

template <class T>
void Library<T>::SetCurrentItemByValue(std::shared_ptr<T> item) {
  current_item_ = std::move(item);
}

template class Library<Mesh>;
template class Library<DDTexture>;
template class Library<CubeTexture>;
template class Library<ShaderWrapper>;
template class Library<ShaderStrategy>;
template class Library<Light>;
template class Library<Camera>;
template class Library<RenderableObject>;
template class Library<Scene>;
template class Library<ObjectNode>;
