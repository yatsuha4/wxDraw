#pragma once

#include "wxdraw/gui/PaletteListBase.hpp"
#include "wxdraw/palette/PaletteItem.hpp"

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
    if(index < items.size()) {
      items.insert(items.begin() + index, 
                   PaletteItem::Create<T>(getPaletteComponent(), *items.at(index)));
    }
    else {
      items.push_back(PaletteItem::Create<T>(getPaletteComponent()));
    }
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
    }
  }

  virtual void onUpdate(const std::shared_ptr<T>& item, wxListItem& listItem) {
    getList()->InsertItem(listItem);
  }
};
}
