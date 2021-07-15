#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class ColorList
  : public PaletteList
{
  using super = PaletteList;

 public:
  ColorList(wxWindow* parent, Palette* palette);
  ~ColorList() override = default;
};
}
