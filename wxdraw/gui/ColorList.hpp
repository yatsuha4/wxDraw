#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class ColorList
  : public PaletteList
{
  using super = PaletteList;

 private:
  GradientPtr gradient_;

 public:
  ColorList(wxWindow* parent, Palette* palette);
  ~ColorList() override = default;

  void setGradient(const GradientPtr& gradient);

  void update();

 protected:
  PaletteItemPtr getItem(size_t index) const override;
  void appendItem(size_t index) override;
  void removeItem(size_t index) override;

 private:
  void updateImageList();

  static wxBitmap CreateBitmap(const Color& color);
};
}
