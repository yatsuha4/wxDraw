#pragma once

#include "wxdraw/palette/PenBase.hpp"

namespace wxdraw::palette {
/**
 */
class Brush
  : public PenBase
{
  using super = PenBase;

 public:
  static const char* TYPE;

 private:
  double direction_;

 public:
  Brush(const PaletteComponentPtr& palette);
  Brush(const Brush& src) = default;
  ~Brush() override = default;

  WXDRAW_ACCESSOR(Direction, direction_);

  PropertyPtr createProperty() override;
};
}
