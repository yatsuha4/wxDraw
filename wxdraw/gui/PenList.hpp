#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class PenList
  : public PaletteList<Pen>
{
  using super = PaletteList<Pen>;
  using PaletteList<Pen>::PaletteList;
};
}
