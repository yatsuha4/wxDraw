#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class ColorList
  : public PaletteList<Color>
{
  using super = PaletteList<Color>;

 public:
  ColorList(wxWindow* parent, Palette* palette);
  ~ColorList() override = default;

 protected:
  std::vector<ColorPtr>& getItems() const override;
};
}
