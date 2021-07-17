#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
 */
class Brush
  : public PaletteItem
{
  using super = PaletteItem;

 public:
  static const char* TYPE;

 private:
  GradientPtr gradient_;

 public:
  Brush();
  Brush(const Brush& src) = default;
  ~Brush() override = default;

  WXDRAW_GETTER(Gradient, gradient_);

  PropertyPtr createProperty(const PaletteComponentPtr& palette) override;
};
}
