#ifndef ORANGUTAN_MODEL_LIBRARY_H
#define ORANGUTAN_MODEL_LIBRARY_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace orangutan {

template <class T> class Library {
public:
  std::vector<T *> get_items() const;
  std::vector<std::string> GetNames() const;

  T *GetItemByName(const std::string &name, int index = 0) const;

  T *AddItem(const std::string &name, std::unique_ptr<T> item);

private:
  std::unordered_map<std::string, std::vector<std::unique_ptr<T>>> items_;
};

template <class T> std::vector<T *> Library<T>::get_items() const {
  std::vector<T *> items;
  for (auto &group : items_) {
    for (auto &item : group.second) {
      items.push_back(item.get());
    }
  }
  return items;
}

template <class T> std::vector<std::string> Library<T>::GetNames() const {
  std::vector<std::string> items;
  for (auto &item : items_) {
    items.push_back(item.first);
  }
  return items;
}

template <class T>
T *Library<T>::GetItemByName(const std::string &name, int index) const {
  auto iterator = items_.find(name);
  if (iterator == items_.end()) {
    return nullptr;
  }
  return iterator->second.at(index).get();
}

template <class T>
T *Library<T>::AddItem(const std::string &name, std::unique_ptr<T> item) {
  if (items_.find(name) == items_.end()) {
    items_.insert(std::make_pair(name, std::vector<std::unique_ptr<T>>{}));
  }
  items_.at(name).push_back(std::move(item));
  return items_.at(name).back().get();
}

} // namespace orangutan

#endif // ORANGUTAN_MODEL_LIBRARY_H
