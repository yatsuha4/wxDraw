#pragma once

#include "wxdraw/component/Component.hpp"

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

  WXDRAW_ACCESSOR(Pens, pens_);
  WXDRAW_ACCESSOR(Brushes, brushes_);
  WXDRAW_ACCESSOR(Gradients, gradients_);
  WXDRAW_ACCESSOR(Colors, colors_);

  size_t getIndex(const PenPtr& pen) const;
  size_t getIndex(const BrushPtr& brush) const;
  size_t getIndex(const GradientPtr& gradient) const;
  size_t getIndex(const ColorPtr& color) const;
  size_t getIndex(const ColorBasePtr& color) const;

  BrushPtr getBrush(size_t index) const;
  ColorBasePtr getColorBase(size_t index) const;
  ColorPtr getColor(size_t index) const;
  GradientPtr getGradient(size_t index) const;
  PenPtr getPen(size_t index) const;

 private:
  PenPtr appendPen(const wxString& name, const ColorPtr& color = nullptr);
  BrushPtr appendBrush(const wxString& name, const ColorPtr& olor = nullptr);
  ColorPtr appendColor(const wxString& name, const wxColour& color);

  GradientPtr clone(const PaletteComponent& palette, const GradientPtr& src) const;

  template<class PenBaseType>
  std::shared_ptr<PenBaseType> clone(const PaletteComponent& palette, 
                                     const std::shared_ptr<PenBaseType>& src) const {
    auto dst = std::make_shared<PenBaseType>(*src);
    dst->setColor(getColor(palette.getIndex(src->getColor())));
    return dst;
  }

  template<class ItemType>
  static std::shared_ptr<ItemType>
  GetItem(size_t index, const std::vector<std::shared_ptr<ItemType>>& items) {
    return (index < items.size()) ? items.at(index) : nullptr;
  }
};
}
