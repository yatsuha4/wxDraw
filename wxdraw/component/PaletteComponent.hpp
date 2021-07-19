#pragma once

#include "wxdraw/component/Component.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Font.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/palette/Pen.hpp"

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
  std::vector<FontPtr> fonts_;
  std::vector<PenPtr> pens_;
  std::vector<BrushPtr> brushes_;
  std::vector<GradientPtr> gradients_;
  std::vector<ColorPtr> colors_;

 public:
  PaletteComponent(const NodePtr& node);
  PaletteComponent(const PaletteComponent& src, const NodePtr& node);
  ~PaletteComponent() override = default;

  void onCreate() override;

  template<class T>
  const std::vector<std::shared_ptr<T>>& getItems() const {
    const std::vector<std::shared_ptr<T>>* items;
    getItems(&items);
    return *items;
  }

  template<class T>
  std::vector<std::shared_ptr<T>>& getItems() {
    auto& items = const_cast<const PaletteComponent*>(this)->getItems<T>();
    return const_cast<std::vector<std::shared_ptr<T>>&>(items);
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

 private:
  void getItems(const std::vector<FontPtr>** items) const {
    *items = &fonts_;
  }

  void getItems(const std::vector<PenPtr>** items) const {
    *items = &pens_;
  }

  void getItems(const std::vector<BrushPtr>** items) const {
    *items = &brushes_;
  }

  void getItems(const std::vector<GradientPtr>** items) const {
    *items = &gradients_;
  }

  void getItems(const std::vector<GradientStopPtr>** items) const {
    wxLogFatalError("illegal access");
  }

  void getItems(const std::vector<ColorPtr>** items) const {
    *items = &colors_;
  }

  template<class T>
  void getItem(size_t index, std::shared_ptr<T>& item) const {
    auto& items = getItems<T>();
    item = (index < items.size()) ? items.at(index) : nullptr;
  }

  void getItem(size_t index, ColorBasePtr& item) const;

  PenPtr appendPen(const wxString& name, const ColorPtr& color = nullptr);
  BrushPtr appendBrush(const wxString& name, const ColorPtr& olor = nullptr);
  ColorPtr appendColor(const wxString& name, const wxColour& color);

  template<class T, class... Args>
  std::shared_ptr<T> appendItem(Args&&... args) {
    auto item = std::make_shared<T>(args...);
    getItems<T>().push_back(item);
    return item;
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
};
}
