#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
   カラー基底クラス
*/
class ColorBase
  : public PaletteItem
{
  using super = PaletteItem;
  using super::PaletteItem;

 public:
  ColorBase(const ColorBase& src) = default;
  ~ColorBase() override = default;
};
}
