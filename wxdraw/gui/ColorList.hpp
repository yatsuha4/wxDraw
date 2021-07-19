#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class ColorList
  : public PaletteList<Color>
{
  using super = PaletteList<Color>;
  using super::PaletteList;
};
}
