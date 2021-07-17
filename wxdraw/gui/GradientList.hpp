#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class GradientList
  : public PaletteList
{
  using super = PaletteList;

 public:
  GradientList(wxWindow* parent, Palette* palette);
  ~GradientList() override = default;

 protected:
  PaletteItemPtr getItem(size_t index) const override;
};
}
