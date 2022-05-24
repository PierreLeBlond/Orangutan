#ifndef ORANGUTAN_MODEL_LIBRARY_H
#define ORANGUTAN_MODEL_LIBRARY_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace orangutan {

template <class T>
class Library {
 public:
  std::vector<T*> get_items() const;
  std::vector<std::string> GetNames() const;

  T* GetItemByName(const std::string& name) const;

  void AddItem(const std::string& name, std::unique_ptr<T> item);

 private:
  std::unordered_map<std::string, std::unique_ptr<T>> items_;
};

template <class T>
std::vector<T*> Library<T>::get_items() const {
  std::vector<T*> items;
  for (auto& item : items_) {
    items.push_back(item.second.get());
  }
  return items;
}

template <class T>
std::vector<std::string> Library<T>::GetNames() const {
  std::vector<std::string> items;
  for (auto& item : items_) {
    items.push_back(item.first);
  }
  return items;
}

template <class T>
T* Library<T>::GetItemByName(const std::string& name) const {
  auto iterator = items_.find(name);
  if (iterator == items_.end()) {
    std::cerr << "Library::GetItemByName : Item with name " << name
              << " does not exists" << std::endl;
    exit(0);
  }
  return iterator->second.get();
}

template <class T>
void Library<T>::AddItem(const std::string& name, std::unique_ptr<T> item) {
  if (items_.count(name) > 0) {
    std::cerr << "Library::AddItem : Item with name " << name
              << " already exists" << std::endl;
  }
  items_.insert(std::make_pair(name, std::move(item)));
}

}  // namespace orangutan

#endif  // ORANGUTAN_MODEL_LIBRARY_H
