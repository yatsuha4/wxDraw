#pragma once

#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/PaletteListBase.hpp"

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
     リストを更新する
  */
  void refresh() override {
    getList()->Freeze();
    getList()->DeleteAllItems();
    getImageList()->RemoveAll();
    size_t index = 0;
    for(auto& item : getItems()) {
      getList()->InsertItem(*createListItem(index++, item));
    }
    getList()->Thaw();
    unselectItem();
  }

  /**
     リストの内容を更新する
  */
  void update() override {
    getList()->Freeze();
    getImageList()->RemoveAll();
    size_t index = 0;
    for(auto& item : getItems()) {
      getList()->SetItem(*createListItem(index++, item));
    }
    getList()->Thaw();
  }

 protected:
  virtual List<T>& getItems() const {
    static List<T> EMPTY;
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
      unselectItem();
      auto& items = getItems();
      std::shared_ptr<T> item;
      if(index < items.size()) {
        item = items.create(index + 1, *items.at(index));
        index++;
      }
      else {
        item = items.create(index, getPaletteComponent());
      }
      getList()->InsertItem(*createListItem(index, item));
      selectItem(index);
    }
  }

  virtual bool canAppendItem(size_t index) const {
    return true;
  }

  void removeItem(size_t index) override {
    if(canRemoveItem(index)) {
      unselectItem();
      auto& items = getItems();
      items.erase(items.begin() + index);
      getList()->DeleteItem(index);
      selectItem(index);
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
