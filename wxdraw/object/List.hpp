#pragma once

#include "wxdraw/object/Object.hpp"

namespace wxdraw::object {
/**
 */
template<class T>
class List
  : public std::vector<std::shared_ptr<T>>
{
  using super = std::vector<std::shared_ptr<T>>;

 public:
  List() = default;
  ~List() = default;

  std::shared_ptr<T> at(size_t index) const {
    return (index < super::size()) ? super::at(index) : nullptr;
  }

  void insert(size_t index, const std::shared_ptr<T>& object) {
    super::insert(super::begin() + index, object);
  }

  void remove(size_t index) {
    super::erase(super::begin() + index);
  }

  std::shared_ptr<T> find(const wxString& key) const {
    auto iter = std::find_if(super::begin(), super::end(), 
                             [&](auto& object) {
                               return (object->getId() == key ||
                                       object->getName() == key);
                             });
    return (iter != super::end()) ? *iter : nullptr;
  }

  template<class... Args>
  std::shared_ptr<T> create(Args&&... args) {
    auto object = T::template Create<T>(args...);
    super::push_back(object);
    return object;
  }

  template<class... Args>
  std::shared_ptr<T> create(size_t index, Args&&... args) {
    auto object = T::template Create<T>(args...);
    super::insert(((index < super::size())
                   ? super::begin() + index
                   : super::end()), object);
    return object;
  }
};
}
