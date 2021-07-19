#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class GradientList
  : public PaletteList<Gradient>
{
  using super = PaletteList<Gradient>;
  using super::PaletteList;

 protected:
  void onSelectItem(const PaletteItemPtr& item) override;
};
}
