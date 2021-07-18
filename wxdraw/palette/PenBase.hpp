#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
   ペン(ブラシ)基底クラス
*/
class PenBase
  : public PaletteItem
{
  using super = PaletteItem;

 private:
  ColorBasePtr color_;

 public:
  PenBase() = default;
  PenBase(const PenBase& src) = default;
  ~PenBase() override = default;

  WXDRAW_ACCESSOR(Color, color_);

  void update() override;

 protected:
  PropertyPtr createProperty(const char* type);
};
}
