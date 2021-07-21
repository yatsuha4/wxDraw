#pragma once

#include "wxdraw/command/InsertCommand.hpp"
#include "wxdraw/command/RemoveCommand.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/MainFrame.hpp"
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
  class CommandObserver
    : public InsertCommand<T>::Observer
  {
   private:
    PaletteList* list_;

   public:
    CommandObserver(PaletteList* list)
      : list_(list)
    {}

    void doInsert(const std::shared_ptr<T>& item, size_t index) override {
      list_->doInsert(item, index);
    }

    void doRemove(const std::shared_ptr<T>& item, size_t index) override {
      list_->doRemove(item, index);
    }
  };

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
      auto& items = getItems();
      std::shared_ptr<T> item;
      if(index < items.size()) {
        item = T::template Create<T>(*items.at(index++));
      }
      else {
        item = T::template Create<T>(getPaletteComponent());
      }
      submitCommand<InsertCommand<T>>(item, index);
    }
  }

  virtual bool canAppendItem(size_t index) const {
    return true;
  }

  void doInsert(const std::shared_ptr<T>& item, size_t index) {
    unselectItem();
    getItems().insert(index, item);
    getList()->InsertItem(*createListItem(index, item));
    selectItem(index);
  }

  void removeItem(size_t index) override {
    if(auto item = getRemoveItem(index)) {
      submitCommand<RemoveCommand<T>>(item, index);
    }
  }

  virtual std::shared_ptr<T> getRemoveItem(size_t index) const {
    return getItems().at(index);
  }

  void doRemove(const std::shared_ptr<T>& item, size_t index) {
    unselectItem();
    getItems().remove(index);
    getList()->DeleteItem(index);
    selectItem(index);
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

  template<class CommandType, class... Args>
  bool submitCommand(Args&&... args) {
    return getMainFrame()->template submitCommand<CommandType>
      (std::make_shared<CommandObserver>(this), args...);
  }
};
}
