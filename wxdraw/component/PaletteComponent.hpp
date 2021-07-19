#pragma once

#include "wxdraw/component/Component.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/palette/Pen.hpp"

namespace wxdraw::component {
/**
   カラーパレットコンポーネント
*/
class PaletteComponent
  : public Component<PaletteComponent>
{
  using super = Component<PaletteComponent>;

 public:
  static const char* TYPE;

 private:
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

  GradientPtr clone(const PaletteComponent& palette, const GradientPtr& src) const;

  template<class PenBaseType>
  std::shared_ptr<PenBaseType> clone(const PaletteComponent& palette, 
                                     const std::shared_ptr<PenBaseType>& src) const {
    auto dst = std::make_shared<PenBaseType>(*src);
    dst->setColor(getItem<Color>(palette.getIndex(src->getColor())));
    return dst;
  }
};
}
