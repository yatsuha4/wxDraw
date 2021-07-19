#pragma once

#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/PaletteListBase.hpp"
#include "wxdraw/palette/GradientStop.hpp"

namespace wxdraw::gui {
/**
 */
template<class T>
class PaletteList
  : public PaletteListBase
{
  using super = PaletteListBase;

 public:
  PaletteList(wxWindow* window, Palette* palette)
    : super(window, palette)
  {
    getList()->AppendColumn(T::TYPE);
  }

  /**
   */
  void refresh() {
    getList()->Freeze();
    getList()->DeleteAllItems();
    getImageList()->RemoveAll();
    size_t index = 0;
    for(auto& item : getItems()) {
      getList()->InsertItem(*createListItem(index++, item));
    }
    getList()->Thaw();
  }

  /**
     リストを更新する
  */
  void update() {
    getList()->Freeze();
    getImageList()->RemoveAll();
    size_t index = 0;
    for(auto& item : getItems()) {
      getList()->SetItem(*createListItem(index++, item));
    }
    getList()->Thaw();
  }

 protected:
  virtual std::vector<std::shared_ptr<T>>& getItems() const {
    static std::vector<std::shared_ptr<T>> EMPTY;
    if(auto palette = getPaletteComponent()) {
      return palette->template getItems<T>();
    }
    return EMPTY;
  }

  PaletteItemPtr getItem(size_t index) const override {
    auto& items = getItems();
    return (index < items.size()) ? items.at(index) : nullptr;
  }

  void appendItem(size_t index) override {
    if(canAppendItem(index)) {
      auto& items = getItems();
      std::shared_ptr<T> item;
      if(index < items.size()) {
        item = PaletteItem::Create<T>(getPaletteComponent(), *items.at(index));
        items.insert(items.begin() + index, item);
      }
      else {
        item = PaletteItem::Create<T>(getPaletteComponent());
        items.push_back(item);
      }
      getList()->InsertItem(*createListItem(index, item));
    }
  }

  virtual bool canAppendItem(size_t index) const {
    return true;
  }

  void removeItem(size_t index) override {
    if(canRemoveItem(index)) {
      auto& items = getItems();
      items.erase(items.begin() + index);
      getList()->DeleteItem(index);
    }
  }

  virtual bool canRemoveItem(size_t index) const {
    return index < getItems().size();
  }

 private:
  std::unique_ptr<wxListItem> createListItem(size_t index, const PaletteItemPtr& item) {
    item->update();
    std::unique_ptr<wxListItem> listItem(new wxListItem());
    listItem->SetId(index);
    listItem->SetText(item->getName());
    listItem->SetImage(appendImage(item->getBitmap()));
    return listItem;
  }
};
}
