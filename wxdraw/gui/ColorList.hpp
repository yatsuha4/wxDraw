#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class ColorList
  : public PaletteList
{
  using super = PaletteList;

 private:
  GradientPtr gradient_;

 public:
  ColorList(wxWindow* parent, Palette* palette);
  ~ColorList() override = default;

  void setGradient(const GradientPtr& gradient);

  void update();

 protected:
  void onListItemSelected(wxListEvent& event) override;
};
}
