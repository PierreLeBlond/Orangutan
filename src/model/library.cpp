#include "model/library.h"

#include "object/light.h"
#include "object/renderableobject.h"
#include "camera/camera.h"

#include "object/mesh.h"
#include "core/texture/ddtexture.h"
#include "core/texture/cubetexture.h"
#include "core/shader/shaderwrapper.h"
#include "shader/shaderstrategy.h"

#include "scene/scene.h"

template <class T>
const std::vector<std::shared_ptr<T>>& Library<T>::getItems() const
{
    return _items;
}

template <class T>
const std::vector<std::shared_ptr<T>>& Library<T>::getItemsByName(const std::string& name) const
{
    std::vector<std::shared_ptr<T>> items;
    for(const auto& item : _items)
    {
        if(name == item->getName())
            items.push_back(item);
    }
    return items;
}

template <class T>
bool Library<T>::getItemById(unsigned int index, std::shared_ptr<T>& item) const
{
    bool success = false;
    if((success = (index < _items.size())))
    {
        item = _items[index];
    }

    return success;
}

template <class T>
void Library<T>::addItem(std::shared_ptr<T> item)
{
    _items.push_back(item);
}

template <class T>
std::shared_ptr<T> Library<T>::getCurrentItem() const
{
    return _items.at(_currentItemId);
}

template <class T>
bool Library<T>::setCurrentItemById(unsigned int index)
{
    bool success = false;
    if((success = (index < _items.size())))
        _currentItemId = index;
    return success;
}

template <class T>
bool Library<T>::setCurrentItemByValue(std::shared_ptr<T> item)
{
    bool success = false;
    for(unsigned int id = 0; !success && id < _items.size(); ++id)
        if((success = (item.get() == _items[id].get())))
            _currentItemId = id;
    return success;
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
