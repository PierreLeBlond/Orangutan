#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>

template<class T>
class Library
{
  public:
    const std::vector<std::shared_ptr<T>>&                  getItems() const;

    const std::vector<std::shared_ptr<T>>&                  getItemsByName(const std::string& name) const;

    bool                                                    getItemById(unsigned int index,
                                                                    std::shared_ptr<T>& item) const;

    void                                                    addItem(std::shared_ptr<T> item);

    std::shared_ptr<T>                                      getCurrentItem() const;

    bool                                                    setCurrentItemById(unsigned int index);
    bool                                                    setCurrentItemByValue(std::shared_ptr<T> item);


  private:
    unsigned int                                            _currentItemId;
    std::vector<std::shared_ptr<T>>                         _items;
};

#endif //LIBRARY_H
