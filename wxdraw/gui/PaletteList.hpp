#pragma once

#include "wxdraw/gui/PaletteListBase.hpp"

namespace wxdraw::gui {
/**
 */
template<class T>
class PaletteList
  : public PaletteListBase
{
  using super = PaletteListBase;
  using PaletteListBase::PaletteListBase;

 protected:
  virtual std::vector<std::shared_ptr<T>>& getItems() const = 0;

  PaletteItemPtr getItem(size_t index) const override {
    auto& items = getItems();
    return (index < items.size()) ? items.at(index) : nullptr;
  }

  void appendItem(size_t index) override {
    auto& items = getItems();
    std::shared_ptr<T> item;
    if(index < items.size()) {
      item = std::make_shared<T>(*items.at(index));
      items.insert(items.begin() + index, item);
    }
    else {
      item = std::make_shared<T>();
      items.push_back(item);
    }
    item->onCreate();
    update();
  }

  void removeItem(size_t index) override {
    auto& items = getItems();
    if(index < items.size()) {
      items.erase(items.begin() + index);
      update();
    }
  }

  void onUpdate() override {
    long index = 0;
    for(auto& item : getItems()) {
      wxListItem listItem;
      listItem.SetId(index++);
      onUpdate(item, listItem);
      getList()->InsertItem(listItem);
    }
  }

  virtual void onUpdate(const std::shared_ptr<T>& item, wxListItem& listItem) = 0;
};
}
