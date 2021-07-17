#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
   ペン
*/
class Pen
  : public PaletteItem
{
  using super = PaletteItem;

 public:
  static const char* TYPE;

 private:
  GradientPtr gradient_;
  double width_;

 public:
  Pen();
  Pen(const Pen& src) = default;
  ~Pen() override = default;

  WXDRAW_GETTER(Gradient, gradient_);
  WXDRAW_GETTER(Width, width_);

  PropertyPtr createProperty(const PaletteComponentPtr& palette) override;
};
}
