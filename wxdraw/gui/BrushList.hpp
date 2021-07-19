#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class BrushList
  : public PaletteList<Brush>
{
  using super = PaletteList<Brush>;
  using super::PaletteList;
};
}
