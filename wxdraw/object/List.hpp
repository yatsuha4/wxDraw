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

  std::shared_ptr<T> find(const wxString& key) const {
    auto iter = std::find_if(super::begin(), super::end(), 
                             [&](auto& object) {
                               return (object->getId() == key ||
                                       object->getName() == key);
                             });
    return (iter != super::end()) ? *iter : nullptr;
  }
};
}
