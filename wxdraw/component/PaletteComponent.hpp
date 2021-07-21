#pragma once

#include "wxdraw/component/Component.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Font.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/object/List.hpp"

namespace wxdraw::component {
/**
   パレットコンポーネント
*/
class PaletteComponent
  : public Component<PaletteComponent>
{
  using super = Component<PaletteComponent>;

 public:
  static const char* TYPE;

 private:
  List<Font> fonts_;
  List<Pen> pens_;
  List<Brush> brushes_;
  List<Gradient> gradients_;
  List<Color> colors_;

 public:
  PaletteComponent(const NodePtr& node);
  PaletteComponent(const PaletteComponent& src, const NodePtr& node);
  ~PaletteComponent() override = default;

  void onCreate() override;

  template<class T>
  const List<T>& getItems() const {
    const List<T>* items;
    getItems(&items);
    return *items;
  }

  template<class T>
  List<T>& getItems() {
    auto& items = const_cast<const PaletteComponent*>(this)->getItems<T>();
    return const_cast<List<T>&>(items);
  }

  template<class T>
  size_t getIndex(const std::shared_ptr<T>& item) const {
    auto& items = getItems<T>();
    return std::distance(items.begin(), std::find(items.begin(), items.end(), item));
  }

  size_t getIndex(const ColorBasePtr& color) const;

  template<class T>
  std::shared_ptr<T> getItem(size_t index) const {
    std::shared_ptr<T> item;
    getItem(index, item);
    return item;
  }

  template<class T>
  std::shared_ptr<T> findItem(const wxString& key) const {
    std::shared_ptr<T> item;
    findItem(key, item);
    return item;
  }

  template<class T>
  std::shared_ptr<T> getDefaultItem(const wxString& name) const {
    auto& items = getItems<T>();
    if(auto item = items.find(name)) {
      return item;
    }
    return items.empty() ? nullptr : items.back();
  }

 private:
  void getItems(const List<Font>** items) const {
    *items = &fonts_;
  }

  void getItems(const List<Pen>** items) const {
    *items = &pens_;
  }

  void getItems(const List<Brush>** items) const {
    *items = &brushes_;
  }

  void getItems(const List<Gradient>** items) const {
    *items = &gradients_;
  }

  void getItems(const List<GradientStop>** items) const {
    wxLogFatalError("illegal access");
  }

  void getItems(const List<Color>** items) const {
    *items = &colors_;
  }

  template<class T>
  void getItem(size_t index, std::shared_ptr<T>& item) const {
    item = getItems<T>().at(index);
  }

  void getItem(size_t index, ColorBasePtr& item) const;

  template<class T>
  void findItem(const wxString& key, std::shared_ptr<T>& item) const {
    item = getItems<T>().find(key);
  }

  void findItem(const wxString& key, ColorBasePtr& item) const;

  template<class T, class... Args>
  std::shared_ptr<T> createItem(Args&&... args) {
    return getItems<T>().create(getThis(), args...);
  }

  template<class T>
  void cloneItems(const PaletteComponent& src) {
    auto& items = src.getItems<T>();
    std::transform(items.begin(), items.end(), std::back_inserter(getItems<T>()), 
                   [&](auto& item) {
                   return cloneItem(src, item);
                   });
  }

  template<class T1, class T2, class... Rest>
  void cloneItems(const PaletteComponent& src) {
    cloneItems<T1>(src);
    cloneItems<T2, Rest...>(src);
  }

  template<class T>
  std::shared_ptr<T> cloneItem(const PaletteComponent& palette, 
                               const std::shared_ptr<T>& src) const {
    return std::make_shared<T>(*src);
  }

  GradientPtr cloneItem(const PaletteComponent& palette, const GradientPtr& src) const;
  PenPtr cloneItem(const PaletteComponent& palette, const PenPtr& src) const;
  BrushPtr cloneItem(const PaletteComponent& palette, const BrushPtr& src) const;

  PaletteComponentPtr getThis() {
    return std::static_pointer_cast<PaletteComponent>(shared_from_this());
  }
};
}
