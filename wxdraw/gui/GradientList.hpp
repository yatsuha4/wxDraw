#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class GradientList
  : public PaletteList<Gradient>
{
  using super = PaletteList<Gradient>;

 public:
  GradientList(wxWindow* parent, Palette* palette);
  ~GradientList() override = default;

 protected:
  std::vector<GradientPtr>& getItems() const override;
};
}
