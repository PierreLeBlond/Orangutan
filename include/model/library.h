#ifndef LIBRARY_H
#define LIBRARY_H

#include <memory>
#include <vector>

template <class T>
class Library {
 public:
  const std::vector<std::shared_ptr<T>>& get_items() const;

  const std::vector<std::shared_ptr<T>> GetItemsByName(
      const std::string& name) const;

  void GetItemById(unsigned int index, std::shared_ptr<T>& item) const;

  void AddItem(std::shared_ptr<T> item);

  std::shared_ptr<T> get_current_item() const;

  void SetCurrentItemById(unsigned int index);
  void SetCurrentItemByValue(std::shared_ptr<T> item);

 private:
  std::shared_ptr<T> current_item_;
  std::vector<std::shared_ptr<T>> items_;
};

#endif  // LIBRARY_H
