#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
   グラデーション
*/
class Gradient
  : public PaletteItem
{
  using super = PaletteItem;

 public:
  static const char* TYPE;

 private:
  std::vector<ColorPtr> colors_;

 public:
  Gradient() = default;
  Gradient(const Gradient& src) = default;
  ~Gradient() = default;

  WXDRAW_ACCESSOR(Colors, colors_);

  void sort();

  wxColour getColor() const;
  operator wxGraphicsGradientStops();

  wxImage createImage(const wxSize& size);

  PropertyPtr createProperty(const PaletteComponentPtr& palette) override;
};
}
